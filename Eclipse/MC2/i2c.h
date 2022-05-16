/************************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C driver
 *
 * Author: Muhammad Al-Barbary
 *
 ***********************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
preScaler_1,preScaler_4,preScaler_16,preScaler_64
}I2C_preScalerValue;
typedef struct
{
	uint8 bit_rate;
	I2C_preScalerValue pre_scaler;
	uint8 address;

}TWI_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * 1- Enable I2C
 * 2- Setup the bit rate
 * 3- Setup the address
 */
void TWI_init(const TWI_ConfigType * Config_Ptr);

/*
 * Description:
 * send the start bit
 * Enable TWI Module
 */
void TWI_start(void);
/*
 * Description:
 * send the stop bit
 * Enable TWI Module
 */
void TWI_stop(void);
/*
 * Description:
 * send the data to the data register
 */
void TWI_writeByte(uint8 data);
/*
 * Description:
 * reading the data with ACK
 */
uint8 TWI_readByteWithACK(void);

/*
 * Description:
 * reading the data with NACK
 */
uint8 TWI_readByteWithNACK(void);

uint8 TWI_getStatus(void);
#endif /* I2C_H_ */
