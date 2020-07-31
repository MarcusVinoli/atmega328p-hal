//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module for Digital Input
//Author: Marcus V M Oliveira

#include "GPIO.h"
#pragma once

enum pull_up_mode_t{
    PULL_UP_DISABLED,
    PULL_UP_ENABLED,
};

class DigitalInput
{
    private:
        GPIO gpio;
        
    public:
        DigitalInput(volatile unsigned char *port, const unsigned char bit) :  gpio(GPIO(port, bit)) { 
            gpio.setMode(INPUT);
        }

        DigitalInput(volatile unsigned char *port, const unsigned char bit, pull_up_mode_t pullup) :  gpio(GPIO(port, bit)) { 
            if(pullup == PULL_UP_ENABLED){
                gpio.setMode(INPUT_WITH_PULLUP);
            } else {
                gpio.setMode(INPUT);
            }
        }
        
        bool read();
        bool isHigh();
        bool isLow();
        
};
