/******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.h
 *
 * Description: header file for the Motor driver
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/

#ifndef MOTOR_C_
#define MOTOR_C_

#include "std_types.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	stop,CW,A_CW
}DcMotor_State;
/*******************************************************************************
 *                               Functions Prototypes                          *
 *******************************************************************************/
/*Description:
 *The Function responsible for setup the direction for the two
 *motor pins through the GPIO driver.
 *Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);

/*Description:
 *The function responsible for rotate the DC Motor CW/ or A-CW or
 *stop the motor based on the state input state value.
 *Send the required duty cycle to the PWM driver based on the
 *required speed value.
 */
void DcMotor_Rotate(DcMotor_State state);


#endif /* MOTOR_C_ */
