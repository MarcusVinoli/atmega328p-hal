//Libary for Hardware Abstraction for ATMEGA328P - GPIO Module
//Author: Marcus V M Oliveira
//Creation: 28.07.2020

#define ATMEGA328P
#pragma once

//MACROS
#define DDR_OF_(PORT_PTR) (*(PORT_PTR-1))
#define PIN_OF_(PORT_PTR) (*(PORT_PTR-2))
#define PORT_OF_(PORT_PTR) (*(PORT_PTR))

enum gpio_mode_t{
    OUTPUT,
    INPUT,
    INPUT_WITH_PULLUP
};

class GPIO
{
    private:
        volatile unsigned char *_port;
        const unsigned char _bitmask;

        /* data */
    public:
        GPIO(volatile unsigned char *gpio_port, const unsigned char port_bit) : _port(gpio_port), _bitmask(1<<port_bit) { }
        GPIO(volatile unsigned char *gpio_port, const unsigned char port_bit, gpio_mode_t mode) : _port(gpio_port), _bitmask(1<<port_bit) { setMode(mode); }
               
        void setMode(gpio_mode_t mode);

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
