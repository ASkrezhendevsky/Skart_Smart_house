#include "Alarm.h"
#include <Arduino.h>

bool alarmState = 0;
int stateTime = 0;
int period = 800;
byte F = 0;
bool alarm = false;


int alarmPin = A0;

void alarmProcess(){
    //tone(alarmPin,800);
    //return;
    if(alarm)
    {
        if(stateTime + period < millis())
        {
            stateTime = millis();
            alarmState = !alarmState;
            Serial.println("State");
            if(alarmState)
            {
                Serial.println("Beep");
                tone(alarmPin,(F++%4+4)*100);
            }
            else
            {
                Serial.println("no beep");
                noTone(alarmPin);
                pinMode(alarmPin,INPUT);
            }
        }   
    }
    else
    {
        noTone(alarmPin);
    }
}


void setAlarmPin(int newPin){
    alarmPin = newPin;
}
int getAlarmPin(){
    return alarmPin;
}

void setAlarm(bool newAlarm)
{
    alarm = newAlarm;
}

bool getAlarm()
{
    return alarm;
}
