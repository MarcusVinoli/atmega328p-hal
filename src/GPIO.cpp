//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module
//Author: Marcus V M Oliveira

#include "../GPIO.h"

void GPIO::writeHigh(){
    PORT_OF_(_port) |= _bitmask;
}

void GPIO::writeLow(){
    PORT_OF_(_port) &= ~_bitmask;
}

void GPIO::write(bool pin_level){
    if(pin_level){
        writeHigh();
    } else {
        writeLow();
    }
}

bool GPIO::read(){
    return((PIN_OF_(_port) & (_bitmask) != 0));
}

void GPIO::enablePullUp(){
    writeHigh();
}

void GPIO::disablePullUp(){
    writeLow();
}

unsigned char  GPIO::getPinRegisterValue(){
    return(PIN_OF_(_port));
}

unsigned char  GPIO::getPortRegisterValue(){
    return(PORT_OF_(_port));
}

unsigned char  GPIO::getDataDirectionRegisterValeu(){
    return(DDR_OF_(_port));
}

void GPIO::initialize(volatile unsigned char *gpio_port, unsigned char port_bit){
	_port = gpio_port;
	_bitmask = (1<<port_bit);
	
}