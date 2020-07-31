//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module
//Author: Marcus V M Oliveira
//Creation: 28.07.2020

#define ATMEGA328P
#pragma once

#include "GPIO.h"

//MACROS
#define DDR_OF_(PORT_PTR) (*(PORT_PTR-1))
#define PIN_OF_(PORT_PTR) (*(PORT_PTR-2))
#define PORT_OF_(PORT_PTR) (*(PORT_PTR))

enum output_mode_t{
    OUTPUT_START_LOW,
	OUTPUT_START_HIGH,
};

class DigitalOutput
{
    private:
		GPIO gpio;

        /* data */
    public:
        DigitalOutput(volatile unsigned char *gpio_port, unsigned char port_bit) { gpio.initialize(gpio_port,port_bit); }
        DigitalOutput(volatile unsigned char *gpio_port, unsigned char port_bit, output_mode_t mode) { 
			gpio.initialize(gpio_port,port_bit);
			setMode(mode); }
               
        void setMode(output_mode_t mode);
		void setLow();
		void setHigh();
		bool isLow();
		bool isHigh();
		bool isOff();
		bool isOn();
        void writeHigh();
        void writeLow();
        void write(bool pin_level);
		void toggle();
        bool read();
        void enablePullUp();
        void disablePullUp();
        unsigned char getPinRegisterValue();
        unsigned char getPortRegisterValue();
        unsigned char getDataDirectionRegisterValeu();
};
