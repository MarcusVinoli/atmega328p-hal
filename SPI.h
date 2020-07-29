//Biblioteca de Abstração de Hardware para ATmega328P - Serial Peripheral Interface MASTER
//Author: Marcus V M Oliveira

#pragma once

#define SPI_DEFAULT_MODE SPI_MODE_0
#define SPI_DEFAULT_SCK_FREQ SPI_SCK_FREQ_FOSC_OVER_4

enum spi_mode_t{
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,
};

enum spi_prescale_t{
    SPI_SCK_FREQ_FOSC_OVER_4,
    SPI_SCK_FREQ_FOSC_OVER_16,
    SPI_SCK_FREQ_FOSC_OVER_64,
    SPI_SCK_FREQ_FOSC_OVER_128,
    SPI_SCK_FREQ_FOSC_OVER_2,
    SPI_SCK_FREQ_FOSC_OVER_8,
    SPI_SCK_FREQ_FOSC_OVER_32,
};

class SPI
{
private:
    void waitBusTaskFinished();

public:
    SPI() { 
        setMode(SPI_DEFAULT_MODE);
        setSckFrequency(SPI_DEFAULT_SCK_FREQ);
    }
    
    SPI(spi_mode_t spi_mode, spi_prescale_t spi_freq){
        setMode(spi_mode);
        setSckFrequency(spi_freq);
    }

    unsigned char transmitt(unsigned char data);
    void setMode(spi_mode_t spi_mode);
    void setSckFrequency(spi_prescale_t spi_freq);


};
