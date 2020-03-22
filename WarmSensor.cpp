#include "WarmSensor.h"
#include <Arduino.h>

int warmSensorPin = A0;

int getWarm(){
  return analogRead(warmSensorPin);
}

void setWarmSensorPin(int newPin){
    warmSensorPin = newPin;
}

int getWarmSensorPin(){
    return warmSensorPin;
}
