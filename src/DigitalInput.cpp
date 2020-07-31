//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module for Digital Input
//Author: Marcus V M Oliveira

#include "../DigitalInput.h"

bool DigitalInput::read(){
    return(gpio.read());
}

bool DigitalInput::isHigh(){
    return(gpio.read());
}

bool DigitalInput::isLow(){
    return(!gpio.read());
}
