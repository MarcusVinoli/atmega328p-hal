//Libary for Hardware Abstraction for ATMEGA328P - Two-Wire Interface (I2C) as Master
//Author: Marcus V M Oliveira
//#define __AVR_ATmega328P__
#include "../TWI.h"
#include "../GPIO.h"
#include <avr/io.h>
#include <util/twi.h>

#define DEFAULT_SCL_FREQ  400000

void TWI::initialization(){
    GPIO PinScl(&ATMEGA328P_SCL_PORT, ATMEGA328P_SCL_BIT, OUTPUT);
    GPIO PinSda(&ATMEGA328P_SDA_PORT, ATMEGA328P_SDA_BIT, OUTPUT);
}

unsigned char TWI::start(){
    TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);

    waitBusTaskCompleted();

    return (getBusStatus());
}

unsigned char TWI::repStart(){
    TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);

    waitBusTaskCompleted();

    return(getBusStatus()); 
}

void TWI::stop(){
    TWCR = (1<<TWINT)|(1<<TWSTO)| (1<<TWEN);
}

unsigned char TWI::transmitt(unsigned char data){
    TWDR = data;
    waitBusTaskCompleted();
}

unsigned char TWI::transmitt(unsigned char data, twi_mode_t mode){
    TWDR = (data | mode);
    waitBusTaskCompleted();
}

unsigned char TWI::receive(twi_ack_t ack){
    if(ack == TWI_ACK){
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    } else {
        TWCR = (1<<TWINT)|(1<<TWEN);
    }
    waitBusTaskCompleted();
    return TWDR;
}

unsigned char TWI::receive(bool ack){
    if(ack){
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    } else {
        TWCR = (1<<TWINT)|(1<<TWEN);
    }
    waitBusTaskCompleted();
    return TWDR;
}

void TWI::recover(){
    
}

unsigned char TWI::getBusStatus(){
    return(TW_STATUS_MASK & TWSR);
}

void TWI::waitBusTaskCompleted(){
    while(!(TWCR & (1<<TWINT)));
}

twi_status_t TWI::write(unsigned char slave_address, unsigned char register_address, unsigned char data){
    if(start() == TW_START){
        if(transmitt(slave_address, TWI_WRITE_MODE) == TW_MT_SLA_ACK){
            if(transmitt(register_address) == TW_MT_DATA_ACK){
                if(transmitt(data) == TW_MT_DATA_ACK){
                    stop();
                    return(TWI_SUCCESSFUL);
                }
            }
        }
        stop();
    }
    return(TWI_FAULT);
}

twi_status_t TWI::write(unsigned char slave_address, unsigned char first_register_address, unsigned char *data, int size){
    twi_status_t _return_status = TWI_SUCCESSFUL;
    if(start() == TW_START){
        if(transmitt(slave_address, TWI_WRITE_MODE) == TW_MT_SLA_ACK){
            if(transmitt(first_register_address) == TW_MT_DATA_ACK){
                for(int i=0; i<size; i++){
                    if(transmitt(data[i]) == TW_MT_DATA_ACK){
                        continue;
                    } else {
                        _return_status = TWI_FAULT;
                        break;                        
                    }
                }  
            }
        }
        stop();
    }
    return(_return_status);
}

twi_status_t TWI::read(unsigned char slave_address, unsigned char register_address, unsigned char *data){
    twi_status_t _return_status = TWI_FAULT;
    if(start() == TW_START){
        if(transmitt(slave_address, TWI_WRITE_MODE) == TW_MT_SLA_ACK){
            if(transmitt(register_address) == TW_MT_DATA_ACK){
                if(repStart() == TW_REP_START){
                    if(transmitt(slave_address, TWI_READ_MODE) == TW_MR_SLA_ACK){
                        *data = receive(TWI_NACK);
                        _return_status = TWI_SUCCESSFUL;
                    }
                }
            }
        }
        stop();
    }
    return(_return_status);
}

twi_status_t TWI::read(unsigned char slave_address, unsigned char register_address, unsigned char *data, int size){
    twi_status_t _return_status = TWI_FAULT;
    if(start() == TW_START){
        if(transmitt(slave_address, TWI_WRITE_MODE) == TW_MT_SLA_ACK){
            if(transmitt(register_address) == TW_MT_DATA_ACK){
                if(repStart() == TW_REP_START){
                    if(transmitt(slave_address, TWI_READ_MODE) == TW_MR_SLA_ACK){
                        for(int i=0; i<size; i++){
                            data[i] = receive((i<size));
                        }
                        _return_status = TWI_SUCCESSFUL;
                    }
                }
            }
        }
        stop();
    }
    return(_return_status);
}
