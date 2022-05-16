/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/


#include <avr/io.h>
#include "common_macros.h"
#include "gpio.h"

/*
 * Description:
 * configure the pin direction input/output
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction){
	if(port_num>=NUM_OF_PORTS || pin_num>=NUM_OF_PINS)
	{
		/* Do nothing*/
	}
	else{
		if(direction)
		{
			switch(port_num)
			{
			case PORTA_ID: SET_BIT(DDRA,pin_num);
			break;
			case PORTB_ID: SET_BIT(DDRB,pin_num);
			break;
			case PORTC_ID: SET_BIT(DDRC,pin_num);
			break;
			case PORTD_ID: SET_BIT(DDRD,pin_num);
			break;
			}
		}
		else{
			switch(port_num)
			{
			case PORTA_ID: CLEAR_BIT(DDRA,pin_num);
			break;
			case PORTB_ID: CLEAR_BIT(DDRB,pin_num);
			break;
			case PORTC_ID: CLEAR_BIT(DDRC,pin_num);
			break;
			case PORTD_ID: CLEAR_BIT(DDRD,pin_num);
			break;
			}
		}
	}
}

/*
 * Description:
 * if the pin is output it will write logic high or logic low
 * if the pin is input it will enable the pull up resistor if it write logic high
 */

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value){
	if(port_num>=NUM_OF_PORTS || pin_num>=NUM_OF_PINS)
	{
		/* Do nothing*/
	}
	else
	{
		if(value == LOGIC_HIGH)
		{
			switch(port_num)
			{
			case PORTA_ID: SET_BIT(PORTA,pin_num);
			break;
			case PORTB_ID: SET_BIT(PORTB,pin_num);
			break;
			case PORTC_ID: SET_BIT(PORTC,pin_num);
			break;
			case PORTD_ID: SET_BIT(PORTD,pin_num);
			break;
			}
		}
		else{
			switch(port_num)
			{
			case PORTA_ID: CLEAR_BIT(PORTA,pin_num);
			break;
			case PORTB_ID: CLEAR_BIT(PORTB,pin_num);
			break;
			case PORTC_ID: CLEAR_BIT(PORTC,pin_num);
			break;
			case PORTD_ID: CLEAR_BIT(PORTD,pin_num);
			break;
			}
		}
	}
}

/*
 * Description:
 * read the value on the required pin
 * if the port number or pin number is incorrect the function returns zero
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num){
	uint8 pin_value = LOGIC_LOW;
	if(port_num>=NUM_OF_PORTS || pin_num>=NUM_OF_PINS)
	{
		/*Do nothing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID: if(BIT_IS_SET(PINA,pin_num))
		{
			pin_value = LOGIC_HIGH;
		}
		else
		{
			pin_value = LOGIC_LOW;
		}
		break;
		case PORTB_ID: if(BIT_IS_SET(PINB,pin_num))
		{
			pin_value = LOGIC_HIGH;
		}
		else
		{
			pin_value = LOGIC_LOW;
		}
		break;
		case PORTC_ID: if(BIT_IS_SET(PINC,pin_num))
		{
			pin_value = LOGIC_HIGH;
		}
		else
		{
			pin_value = LOGIC_LOW;
		}
		break;
		case PORTD_ID: if(BIT_IS_SET(PIND,pin_num))
		{
			pin_value = LOGIC_HIGH;
		}
		else
		{
			pin_value = LOGIC_LOW;
		}
		break;
		}
	}
	return pin_value;
}

/*
 * Description:
 * configure the port direction input/output
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction){
	if(port_num>= NUM_OF_PORTS)
	{
		/* Do nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID: DDRA = direction;
		break;
		case PORTB_ID: DDRB = direction;
		break;
		case PORTC_ID: DDRC = direction;
		break;
		case PORTD_ID: DDRD = direction;
		break;
		}
	}
}

/*
 * Description:
 * if the port is output it will write logic high or logic low
 * if the port is input it will enable the pull up resistor if it write logic high
 */

void GPIO_writePort(uint8 port_num, uint8 value){
	if(port_num>= NUM_OF_PORTS)
	{
		/* Do nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num){

	uint8 value = LOGIC_LOW;
	if(port_num>= NUM_OF_PORTS)
	{
		/* Do nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}
	return value;
}
