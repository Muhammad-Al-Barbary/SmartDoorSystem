 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	SIZE_5,SIZE_6,SIZE_7,SIZE_8,SIZE_9=7

}UART_Frame_Size;
/*enum to store no of bit in uart frame*/

typedef enum{
DISABLED,EVEN=2,ODD
}UART_Parity_Mode;
/*enum to chose type of parity check*/


typedef enum{
BIT_1,BIT_2

}UART_Stop_Bits_Num;
/*enum to chose number of stop bits*/

typedef struct{
	UART_Frame_Size frame_size;
	UART_Parity_Mode parity_mode;
	UART_Stop_Bits_Num stop_bits;
	uint32 baud_rate;

}UART_Config;
/*configurations structure*/




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_Config*Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
