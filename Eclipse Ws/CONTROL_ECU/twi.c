/********************************************************************************
 * MODULE : TWI
 * File Name: twi.c
 * Description:Source file for TWI
 * Created on: Oct 24, 2021
 * Author: Philo
 ********************************************************************************/


#include "twi.h"
#include "avr/io.h"
#include "common_macros.h"

/*@description: this function to initialize I2C driver
 * param1: pointer to configuration structure
 * to select bit rate and prescaler and address and enable enable TWI
 * return: none*/
void TWI_init(const Twi_ConfigType *Config_Ptr){

	TWBR = Config_Ptr->bit_rate;
	TWSR = 0x03&(Config_Ptr->prescaler);
	TWAR = Config_Ptr->my_address;
	TWCR = (1<<TWEN);
}


void TWI_start(void){
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void){
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWI_writeByte(uint8 data){
	TWDR = data;  /* Put data On TWI data Register */
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void){
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) |(1<<TWEN) |(1<<TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 TWI_readByteWithNACK(void){
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1<<TWINT) |(1<<TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}


uint8 TWI_getStatus(void){
	uint8 status;
	 /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}

