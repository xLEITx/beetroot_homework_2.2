#include <Arduino.h>
constexpr uint8_t CNTRL_PIN = 6;
constexpr uint8_t READ_PIN = 18;
constexpr uint32_t DEBOUNCE_TIME = 5000; 

volatile uint64_t lastStateChange = 0;
volatile uint32_t switchingDelay = 0;
volatile uint32_t lastInterruptTime = 0;


class Relay{
  private:
    bool isOn = 0;
  public:
    bool getState(){
      return isOn;
    }
    void changeState(){
      isOn = !isOn;
    }
};

Relay relay;

void IRAM_ATTR relay_isr(){
  if (micros()-lastInterruptTime > DEBOUNCE_TIME)
  {
    switchingDelay = micros() - lastStateChange;
    lastInterruptTime = micros();
  }
  
}


void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(CNTRL_PIN, OUTPUT);
  pinMode(READ_PIN, INPUT_PULLDOWN);
  lastStateChange = micros();
  attachInterrupt(READ_PIN, relay_isr, CHANGE);
}

void loop() {
  if (micros() - lastStateChange > 1000000)
  { lastStateChange = micros();
    relay.changeState();
    Serial.println(switchingDelay);
  }
  digitalWrite(CNTRL_PIN, relay.getState());

  

}

