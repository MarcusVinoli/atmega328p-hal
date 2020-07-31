//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module for Digital Input/Output
//Author: Marcus V M Oliveira
//Creation: 28.07.2020

#include "GPIO.h"
#pragma once

#define DEFAULT_MODE IO_INPUT_WITH_NO_PULL_UP

enum io_mode_t{
    IO_INPUT_WITH_NO_PULL_UP,
    IO_INPUT_WITH_PULL_UP,
    IO_OUTPUT_HIGH,
    IO_OUTPUT_LOW,
};

#define HIGH true
#define LOW false

class DigitalInputOutput
{
    private:
        GPIO gpio;
        io_mode_t _current_mode;

    public:
        DigitalInputOutput(volatile unsigned char *port, const unsigned char bit) :  gpio(GPIO(port, bit)) { 
            setMode(DEFAULT_MODE);
        }

        DigitalInputOutput(volatile unsigned char *port, const unsigned char bit, io_mode_t io_mode) :  gpio(GPIO(port, bit)) { 
            setMode(io_mode);
        }

        void setMode(io_mode_t io_mode);
        io_mode_t getCurrentMode();
        bool read();
        void write(bool st);
        
};
