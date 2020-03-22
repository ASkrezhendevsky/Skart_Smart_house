#include "ClapButton.h"
#include <Arduino.h>
int state = 0;
bool info = 0;
int pin = 0;

int getClapButtonInfo(){
    bool curInfo = info;
    switch(state)
    {
        case SIMPLE_BUTTON:
            info = false;
        break;
    }
    return curInfo;
}

void setClapButtonState(int newState){
    state = newState;  
}

void сlapButtonProsess(){
    if(digitalRead(pin))
    {
        switch(state)
        {
            case SIMPLE_BUTTON:
                info = true;
            break;
            case SWITCH:
                info = !info;
            break;
        }
    }
}

void setClapPin(int newPin){
    pin = newPin;
}

int getClapPin(){
    return pin;
}
