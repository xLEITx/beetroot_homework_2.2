#include <Arduino.h>
constexpr uint8_t CNTRL_PIN = 6;
constexpr uint8_t READ_PIN = 18;

uint32_t lastStateChange = 0;

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


void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(CNTRL_PIN, OUTPUT);
  pinMode(READ_PIN, INPUT_PULLDOWN);
  lastStateChange = millis();
}

void loop() {
  if (millis() - lastStateChange > 1000)
  {
    relay.changeState();
    lastStateChange = millis();
  }
  digitalWrite(CNTRL_PIN, relay.getState());

}

