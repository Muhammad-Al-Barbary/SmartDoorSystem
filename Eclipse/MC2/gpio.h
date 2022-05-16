/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_


#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS 4
#define NUM_OF_PINS 8

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                               Functions Prototypes                          *
 *******************************************************************************/

/*
 * Description:
 * configure the pin direction input/output
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description:
 * if the pin is output it will write logic high or logic low
 * if the pin is input it will enable the pull up resistor if it write logic high
 */

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description:
 * read the value on the required pin
 * if the port number or pin number is incorrect the function returns zero
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Description:
 * configure the port direction input/output
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
 * Description:
 * if the port is output it will write logic high or logic low
 * if the port is input it will enable the pull up resistor if it write logic high
 */

void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
