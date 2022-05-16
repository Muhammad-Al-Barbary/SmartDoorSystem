/************************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C driver
 *
 * Author: Muhammad Al-Barbary
 *
 ***********************************************************************************/

#include "i2c.h"
#include "common_macros.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/*
 * Description:
 * 1- Enable I2C
 * 2- Setup the bit rate
 * 3- Setup the address
 */
void TWI_init(const TWI_ConfigType * Config_Ptr){
	/*configure the bit rate and the pre-scaler */
	TWBR = Config_Ptr->bit_rate;
	TWSR = Config_Ptr->pre_scaler&0x03;

	/* Passing the address of the slave
	   General Call Recognition: Off */
	TWAR = (Config_Ptr->address<<1);

	TWCR = (1<<TWEN); /* enable TWI */
}

/*
 * Description:
 * send the start bit
 * Enable TWI Module
 */
void TWI_start(void){
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*
 * Description:
 * send the stop bit
 * Enable TWI Module
 */
void TWI_stop(void){
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/*
 * Description:
 * send the data to the data register
 */
void TWI_writeByte(uint8 data){
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*
 * Description:
 * reading the data with ACK
 */
uint8 TWI_readByteWithACK(void){
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

/*
 * Description:
 * reading the data with NACK
 */
uint8 TWI_readByteWithNACK(void){
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_getStatus(void){
	uint8 status;
	    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	    status = TWSR & 0xF8;
	    return status;
}
