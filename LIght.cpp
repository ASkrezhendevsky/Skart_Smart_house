#include "Light.h"
#include <Arduino.h>

int st_cp = 0;//защёлка
int sh_cp = 0;//такт
int ds_cp = 0;//данные
byte lightState = 0;

void shiftByte(byte v)
{
    int i;
    digitalWrite(st_cp, LOW); 
   
    for(i = 0; i < 8; i++)
    {
        digitalWrite(sh_cp,LOW);
        digitalWrite(ds_cp,v &(1<<i));
        digitalWrite(sh_cp,HIGH);
      
    }
    digitalWrite(st_cp, HIGH);
}

void setRelay(int relayNum, bool state){ //Numbering of relay starts from 0
    byte mask = (1<<relayNum);
    lightState = state?(lightState | mask):(lightState & ~mask);
    shiftByte(lightState);
}

byte bytePow(byte a, int n)
{
    if(n == 0)
    {
      return 1;
    }
    int i;
    byte olda = a;
    for(i = 1; i < n; i++)
    {
        a *= olda;
    }
    return a;
}

void relayOff(){
    lightState = 0;
    shiftByte(lightState);
}

void relayOn(){
    lightState = 0bFF;
    shiftByte(lightState);
}

void setStCpPin(int newPin){
    st_cp = newPin;
}

int getStCpPin(){
    return st_cp;
}

void setShCpPin(int newPin){
    sh_cp = newPin;
}

int getShCpPin(){
    return sh_cp;
}

void setDsCpPin(int newPin){
    ds_cp = newPin;
}

int getDsCpPin(){
    return ds_cp;
}
