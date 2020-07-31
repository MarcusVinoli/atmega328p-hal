//Biblioteca de Abstração de Hardware para ATmega328P - Serial Peripheral Interface MASTER
//Author: Marcus V M Oliveira

#pragma once

#include "GPIO.h"

#define ATMEGA328P 

#ifdef ATMEGA328P 
#define RXD_GPIO_PORT  PORTB
#define RXD_GPIO_BIT  0
#define TXD_GPIO_PORT  PORTB
#define TXD_GPIO_BIT 1

#endif

#define DEFAULT_UART_FRAME_FORMAT UART_FRAME_8_BITS
#define DEFAULT_UART_PARITY_MODE UART_PARITY_NONE
#define DEFAULT_UART_STOP_BITS UART_1_STOP_BITS
#define DEFAULT_UART_BAUDRATE 115200
#define DEFAULT_UART_MAX_BAUDRATE 2000000

#define NEW_LINE "\r\n"

enum uart_frame_size_t{
    UART_FRAME_5_BITS,
    UART_FRAME_6_BITS,
    UART_FRAME_7_BITS,
    UART_FRAME_8_BITS,
    UART_FRAME_9_BITS,
};

enum uart_stop_bits_t{
    UART_1_STOP_BITS,
    UART_2_STOP_BITS,
};

enum uart_parity_t{
    UART_PARITY_NONE,
    UART_PARITY_ODD,
    UART_PARITY_EVEN,
};

class UART
{
private:
    unsigned char *_destination();

public:
    UART() { 
        initialization();
    }
    void initialization();
    void setBaudrate(long baudrate, long freq_osc);
    void setFrameFormat(uart_frame_size_t bits);
    void setParity(uart_parity_t parity);
    void setStopBits(uart_stop_bits_t stop_bits);

    bool isBufferEmpty();
    void waitForBufferEmpty();
    void transmitt(unsigned char data);
    bool isDataReceived();
    void waitDataReceived();
    unsigned char receive();

    void write(char data);
    void write(char *string);
    void write(char *data, int data_size);

    void write(unsigned char data);
    void write(unsigned char *data, int data_size);

    void write(int data);
    void write(int *vector, int vector_size);

    void write(float real_num);
    void write(float *real_vect, int vector_size);
    
    unsigned char read();


};
