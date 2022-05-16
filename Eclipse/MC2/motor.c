/******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.c
 *
 * Description: source file for the Motor driver
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/

#include "motor.h"
#include "gpio.h"
#include "common_macros.h"

/*******************************************************************************
 *                               Functions Definition                          *
 *******************************************************************************/
/*Description:
 *The Function responsible for setup the direction for the two
 *motor pins through the GPIO driver.
 *Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{/* configure pin PB0 and PB1 as output pins */
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN2_ID,PIN_OUTPUT);
	/* Motor is stop at the beginning */
	GPIO_writePin(PORTB_ID,PIN0_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN2_ID, LOGIC_LOW);
}

/*Description:
 *The function responsible for rotate the DC Motor CW/ or A-CW or
 *stop the motor based on the state input state value.
 *Send the required duty cycle to the PWM driver based on the
 *required speed value.
 */
void DcMotor_Rotate(DcMotor_State state)
{
	switch(state)
	{
	case stop:
		GPIO_writePin(PORTB_ID,PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID, LOGIC_LOW);
		break;
	case CW:
		GPIO_writePin(PORTB_ID,PIN0_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID,PIN1_ID, LOGIC_LOW);
		break;
	case A_CW:
		GPIO_writePin(PORTB_ID,PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID, LOGIC_HIGH);
		break;
	}
	GPIO_writePin(PORTB_ID,PIN2_ID, LOGIC_HIGH);

}
