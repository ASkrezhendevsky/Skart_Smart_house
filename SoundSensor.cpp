#include "SoundSensor.h"
#include <Arduino.h>

int SoundPin = A0;

void SoundProcess(){
   
}


void setSoundPin(int newPin){
    SoundPin = newPin;
}
int getSoundPin(){
    return SoundPin;
}

