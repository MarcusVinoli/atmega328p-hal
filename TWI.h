//Libary for Hardware Abstraction for ATMEGA328P - Two-Wire Interface (I2C) as Master
//Author: Marcus V M Oliveira
//Creation: 28.07.2020

#define ATMEGA328P

#ifdef ATMEGA328P
#define ATMEGA328P_SCL_PORT PORTC
#define ATMEGA328P_SDA_PORT PORTC
#define ATMEGA328P_SCL_BIT 5
#define ATMEGA328P_SDA_BIT 6
#endif

#pragma once

enum twi_status_t{
    TWI_FAULT,
    TWI_SUCCESSFUL,
};

enum twi_ack_t{
    TWI_NACK,
    TWI_ACK,
};

enum twi_mode_t{
	TWI_WRITE_MODE,
	TWI_READ_MODE,
};

class TWI{
	public:
	TWI() { }
	void initialization();
	unsigned char start();
	unsigned char repStart();
	void stop();
	void recover();
	unsigned char transmitt(unsigned char data);
	unsigned char transmitt(unsigned char data, twi_mode_t mode);
	unsigned char receive(bool ack);
	unsigned char receive(twi_ack_t ack);
	void waitBusTaskCompleted();
	unsigned char getBusStatus();
	twi_status_t write(unsigned char slave_address, unsigned char register_address, unsigned char data);
	twi_status_t write(unsigned char slave_address, unsigned char register_address, unsigned char *data, int size_of_data);
	twi_status_t read(unsigned char slave_address, unsigned char register_address, unsigned char *data);
	twi_status_t read(unsigned char slave_address, unsigned char register_address, unsigned char *data, int size_of_data);
	
};
