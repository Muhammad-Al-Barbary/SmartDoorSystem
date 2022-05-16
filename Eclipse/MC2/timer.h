/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the TIMER driver
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	TIMER0,TIMER1,TIMER2

}TIMER_number;

typedef enum
{
	NORMAL,COMPARE

}TIMER_mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,F_CPU_T2_32,F_CPU_T2_128
}TIMER_preScaler;

typedef enum
{
	OCN_DISCONNECTED,OCN_TOGGLE,OCN_CLEAR,OCN_SET
}TIMER_cmpPin;

typedef enum
{
	COMPARE_A,COMPARE_B,DONT_CARE
}TIMER_cmpOutput;

typedef struct
{
	TIMER_number timer;
	TIMER_mode mode;
	TIMER_preScaler pre_scaler;
	TIMER_cmpPin cmp_pin;
	TIMER_cmpOutput com_output;
	uint16 initial_value;
	uint16 compare_value;
}TIMER_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * configure the timer
 * set the timer mode
 * set the pre-scaler
 * set the initial value
 * set the compare value if the timer is in compare mode
 */
void TIMER_init(const TIMER_ConfigType * Config_Ptr);
/*
 * Description: Function to set the Call Back function address to timer 0.
 */
void TIMER_setCallBackT0(void(*a_ptr)(void));
/*
 * Description: Function to set the Call Back function address to timer 1.
 */
void TIMER_setCallBackT1(void(*a_ptr)(void));
/*
 * Description: Function to set the Call Back function address to timer 2.
 */
void TIMER_setCallBackT2(void(*a_ptr)(void));
/*
 * Description: Function to disable the Timer
 */
void TIMER_DeInit(TIMER_number timer);

#endif /* TIMER_H_ */
