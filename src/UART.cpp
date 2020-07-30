//Biblioteca de Abstração de Hardware para ATmega328P - Serial Peripheral Interface MASTER
//Author: Marcus V M Oliveira

#include "../UART.h"
#include "../DigitalInput.h"
#include "../DigitalOutput.h"
#include <string.h>

void UART::initialization(){
    DigitalOutput RxPin(&RXD_GPIO_PORT, RXD_GPIO_BIT);
    DigitalInput TxPin(&TXD_GPIO_PORT, TXD_GPIO_BIT);

};

void UART::setBaudrate(long baudrate, long freq_osc){
    if(baudrate > 0 && baudrate < DEFAULT_UART_MAX_BAUDRATE){
        long _ubrr = freq_osc/16/baudrate-1;
        UBRR0H = (unsigned char) _ubrr;
        UBRR0L = (unsigned char);
    } else {
        setBaudrate(DEFAULT_UART_BAUDRATE);
    }
}

void UART::setFrameFormat(uart_frame_size_t bits){
    switch (expression){
    UCSRC &= ~((1<<UCSZ00)|(1<<UCSZ01));

    case UART_FRAME_5_BITS:
        break;
    case UART_FRAME_6_BITS:
        UCSRC |= (1<<UCSZ00);
        break;
    case UART_FRAME_7_BITS:
        UCSRC |= (1<<UCSZ01);
        break;
    case UART_FRAME_8_BITS:
        UCSRC |= (1<<UCSZ00) | (1<<UCSZ01);
        break;
    case UART_FRAME_9_BITS:
        UCSRC |= (1<<UCSZ00) | (1<<UCSZ01);
        UCSR
        break;
    }
}

void UART::setParity(uart_parity_t parity){
    switch(parity){
        case UART_PARITY_NONE:
            UCSR0C &= ~((1<<UMP01)|(1<<UMP00))
            break;

        case UART_PARITY_ODD:
            UCSR0C |= (1<<UMP01) | (1<<UMP00);
            break;
            
        case UART_PARITY_EVEN:
            UCSR0C |= (1<<UMP01);
            UCSR0C &= ~(1<<UMP00);
            break;
    }
}

void UART::setStopBits(uart_stop_bits_t stop_bits){
    switch(stop_bits){
        case UART_1_STOP_BITS:
            UCSR0C &=~(1<<USBS0);
            break;

        case UART_2_STOP_BITS:
            UCSR0C |=(1<<USBS0);
            break;
    }
}

bool isBufferEmpty(){
    return(UCSRnA & (1<<UDREn));
}

void waitForBufferEmpty(){
    while(!isBufferEmpty());
}

void UART::transmitt(unsigned char data){
    waitForBufferEmpty();
    UDR0 = data;
}

bool UART::isDataReceived(){
    return(UCSR0A & (1<<RXC0));
}

void UART::waitDataReceived(){
    while(!isDataReceived());
}

unsigned char receive(){
    waitDataReceived();
    return UDR0;
}

void UART::write(char data){
    transmitt(data);
}

void UART::write(char *string){
    int _str_length = strlen(string);
    for(int i=0; i < _str_length; i++){
        transmitt(string[i]);
    }
}

void UART::write(char *data, int data_size){
    for(int i=0; i < data_size; i++){
        transmitt(data[i]);
    }
}

void UART::write(unsigned char data){
   transmitt(data);
}

void UART::write(unsigned char *string){
    int _str_length = strlen(string);
    for(int i=0; i < _str_length; i++){
        transmitt(string[i]);
    }
}

void UART::write(unsigned char *data, int data_size){
    for(int i=0; i < data_size; i++){
        transmitt(data[i]);
    }
}

void UART::write(int data){
    unsigned char buffer[10];
    sprintf(buffer,"%d",data);
    write(buffer);
}

void UART::write(int *vector, int vector_size){
    for(int i=0; i< vector_size; i++){
        write(vector[i]);
        write(NEW_LINE);
    }
}

void UART::write(float real_num){
    unsigned char buffer[10];
    sprintf(buffer,"%f",real_num);
    write(buffer);
}

void UART::write(float *real_vect, int vector_size){
    for(int i=0; i< vector_size; i++){
        write(real_vect[i]);
        write(NEW_LINE);
    }
}

unsigned char UART::read(){
    return(receive());
}