//Biblioteca de Abstração de Hardware para ATmega328P - Serial Peripheral Interface MASTER
//Author: Marcus V M Oliveira

#include "../SPI.h"
#include <avr/io.h>

void SPI::waitBusTaskFinished(){
    while(!(SPSR & (1<<SPIF)));
}

unsigned char SPI::transmitt(unsigned char data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return (SPDR);
}

void SPI::setMode(spi_mode_t spi_mode){
    switch (spi_mode){
    case SPI_MODE_0:
        SPCR &= ~(1<<CPOL);
        SPCR &= ~(1<<CPHA);
        break;

    case SPI_MODE_1:
        SPCR &= ~(1<<CPOL);
        SPCR |= (1<<CPHA);

        break;

    case SPI_MODE_2:
        SPCR |= (1<<CPOL);
        SPCR &= ~(1<<CPHA);
        break;

    case SPI_MODE_3:
        SPCR |= (1<<CPOL);
        SPCR |= (1<<CPHA);
        break;  
    
    }
}

void SPI::setSckFrequency(spi_prescale_t spi_freq){
    SPCR &= ~((1<<SPEN) | (1<<SPR0));
    SPSR &= ~(1<<SPI2X);

    switch (spi_freq){
    case SPI_SCK_FREQ_FOSC_OVER_4:
        SPCR = (1<<SPEN);
        break;

    case SPI_SCK_FREQ_FOSC_OVER_16:
        SPCR = (1<<SPEN) | (1<<SPR0);
        break;
    
    case SPI_SCK_FREQ_FOSC_OVER_64:
        SPCR = (1<<SPEN) | (1<<SPR1);
        break;
    
    case SPI_SCK_FREQ_FOSC_OVER_128:
        SPCR = (1<<SPEN) | (1<<SPR0) | (1<<SPR1);
        break;
    
    case SPI_SCK_FREQ_FOSC_OVER_2:
        SPCR = (1<<SPEN);
        SPSR = (1<<SPI2X);
        break;
    
    case SPI_SCK_FREQ_FOSC_OVER_8:
        SPCR = (1<<SPEN) | (1<<SPR0);
        SPSR = (1<<SPI2X);
        break;

    case SPI_SCK_FREQ_FOSC_OVER_32:
        SPCR = (1<<SPEN) | (1<<SPR1);
        SPSR = (1<<SPI2X);
        break;
    
    case SPI_SCK_FREQ_FOSC_OVER_64:
        SPCR = (1<<SPEN) | (1<<SPR0) | (1<<SPR1);
        SPSR = (1<<SPI2X);
        break;
        
    }
}