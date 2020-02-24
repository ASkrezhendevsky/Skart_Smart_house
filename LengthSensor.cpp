#include "LendthSensor.h"

#include <Arduino.h>

LendthSensor::~LendthSensor() {
}

int LendthSensor::getLenght(){
	return analogRead(pin);
}

int LendthSensor::getLenght(){
	return analogRead(pin);
}


LendthSensor::setPin(int newPin){
	pin = newPin;
}

int LendthSensor::getPin(){
	return pin;
}

