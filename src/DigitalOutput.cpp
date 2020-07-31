//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module for Digital Output
//Author: Marcus V M Oliveira

#include "../DigitalOutput.h"

void DigitalOutput::setHigh(){
    gpio.writeHigh();
}

void DigitalOutput::setLow(){
    gpio.writeLow();
}

bool DigitalOutput::isOn(){
    return(gpio.getPortRegisterValue());
}

bool DigitalOutput::isOff(){
    return(!gpio.getPortRegisterValue());
}
