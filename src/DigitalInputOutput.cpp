//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module for Digital Input/Output
//Author: Marcus V M Oliveira

#include "../DigitalInputOutput.h"

void DigitalInputOutput::setMode(io_mode_t io_mode){
    _current_mode = io_mode;
    switch (io_mode){
    case IO_INPUT_WITH_NO_PULL_UP:
        gpio.setMode(INPUT);
        break;
    
    case IO_INPUT_WITH_PULL_UP:
        gpio.setMode(INPUT_WITH_PULLUP);
        break;

    case IO_OUTPUT_HIGH:
        gpio.setMode(OUTPUT);
        gpio.writeHigh();
        break;

    case IO_OUTPUT_LOW:
        gpio.setMode(OUTPUT);
        gpio.writeLow();
        break;
    }
}

io_mode_t DigitalInputOutput::getCurrentMode(){
    return(_current_mode);
}

bool DigitalInputOutput::read(){
    return(gpio.read());
}

void DigitalInputOutput::write(bool st){
    gpio.write(st);
}