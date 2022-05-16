/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the TIMER driver
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "common_macros.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtrT0)(void) = NULL_PTR;
static volatile void (*g_callBackPtrT1)(void) = NULL_PTR;
static volatile void (*g_callBackPtrT2)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/*
 * ISR for the over flow mode
 */
ISR(TIMER0_OVF_vect){
	if(g_callBackPtrT0 != NULL_PTR)
	{

		(*g_callBackPtrT0)();
	}
}

ISR(TIMER1_OVF_vect){
	if(g_callBackPtrT1 != NULL_PTR)
	{

		(*g_callBackPtrT1)();
	}
}

ISR(TIMER2_OVF_vect){
	if(g_callBackPtrT2 != NULL_PTR)
	{

		(*g_callBackPtrT2)();
	}
}
/*
 * ISR for the compare mode
 */
ISR(TIMER0_COMP_vect){
	if(g_callBackPtrT0 != NULL_PTR)
	{

		(*g_callBackPtrT0)();
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtrT1 != NULL_PTR)
	{

		(*g_callBackPtrT1)();
	}
}
ISR(TIMER1_COMPB_vect){
	if(g_callBackPtrT1 != NULL_PTR)
	{

		(*g_callBackPtrT1)();
	}
}
ISR(TIMER2_COMP_vect){
	if(g_callBackPtrT2 != NULL_PTR)
	{

		(*g_callBackPtrT2)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description:
 * configure the timer
 * set the timer mode
 * set the pre-scaler
 * set the initial value
 * set the compare value if the timer is in compare mode
 */
void TIMER_init(const TIMER_ConfigType * Config_Ptr){
	switch(Config_Ptr->timer)
	{
	case TIMER0:{
		switch(Config_Ptr->mode)
		{
		case NORMAL:{
			TCCR0 = (1<<FOC0) | ((Config_Ptr->pre_scaler)&0x07);
			TCNT0= (uint8)(Config_Ptr->initial_value);
			TIMSK = (1<<TOIE0);
		}break;
		case COMPARE:{
			TCCR0 = (1<<FOC0) | (1<<WGM01) | ((Config_Ptr->pre_scaler)&0x07) | ((Config_Ptr->cmp_pin)<<COM00);
			TCNT0= (uint8)(Config_Ptr->initial_value);
			OCR0= (uint8)(Config_Ptr->compare_value);
			TIMSK = (1<<OCIE0);

		}break;
		}
	}break;
	case TIMER1:{
		switch(Config_Ptr->mode)
		{
		case NORMAL:{
			TCCR1A = (1<<FOC1A) | (1<<FOC1B);
			TCCR1B = (Config_Ptr->pre_scaler)&0x07;
			TIMSK = (1<<TOIE1);
			TCNT1 = Config_Ptr->initial_value;
		}break;
		case COMPARE:{
			TCCR1B = ((Config_Ptr->pre_scaler)&0x07 ) | (1<<WGM12);
			TCNT1 = Config_Ptr->initial_value;
			switch(Config_Ptr->com_output){
			case COMPARE_A:
				TCCR1A = (1<<FOC1A) | (1<<FOC1B) | ((Config_Ptr->cmp_pin)<<COM1A0);
				OCR1A = Config_Ptr->compare_value;
				TIMSK = (1<< OCIE1A);
				break;
			case COMPARE_B:
				TCCR1A = (1<<FOC1A) | (1<<FOC1B) | ((Config_Ptr->cmp_pin)<<COM1B0);
				OCR1B = Config_Ptr->compare_value;
				TIMSK = (1<< OCIE1B);
				break;
			default:
				break;
			}
		}break;
		}
	}break;
	case TIMER2:{
		switch(Config_Ptr->mode)
		{
		case NORMAL:{
			TCCR2 = (1<<FOC2);
			TCNT2 = (uint8)(Config_Ptr->initial_value);
			OCR2 = (uint8)(Config_Ptr->compare_value);
			TIMSK = (1<<TOIE2);
			switch(Config_Ptr->pre_scaler)
			{
			case NO_CLOCK:
				break;
			case F_CPU_CLOCK: TCCR2 |= (1<<CS20);
			break;
			case F_CPU_8: TCCR2 |= (1<<CS21);
			break;
			case F_CPU_T2_32: TCCR2 |= (1<<CS21) | (1<<CS20);
			break;
			case F_CPU_64: TCCR2 |= (1<<CS22);
			break;
			case F_CPU_T2_128: TCCR2 |= (1<<CS22) | (1<<CS20);
			break;
			case F_CPU_256: TCCR2 |= (1<<CS22) | (1<<CS21);
			break;
			case F_CPU_1024:TCCR2 |= (1<<CS22) | (1<<CS21) | (1<<CS20);
			break;
			}
		}break;
		case COMPARE:{
			TCCR2 = (1<<FOC2) | (1<<WGM21) | ((Config_Ptr->cmp_pin)<<COM20);
			TCNT2 = (uint8)(Config_Ptr->initial_value);
			OCR2 = (uint8)(Config_Ptr->compare_value);
			TIMSK = (1<<OCIE2);
			switch(Config_Ptr->pre_scaler)
			{
			case NO_CLOCK:
				break;
			case F_CPU_CLOCK: TCCR2 |= (1<<CS20);
			break;
			case F_CPU_8: TCCR2 |= (1<<CS21);
			break;
			case F_CPU_T2_32: TCCR2 |= (1<<CS21) | (1<<CS20);
			break;
			case F_CPU_64: TCCR2 |= (1<<CS22);
			break;
			case F_CPU_T2_128: TCCR2 |= (1<<CS22) | (1<<CS20);
			break;
			case F_CPU_256: TCCR2 |= (1<<CS22) | (1<<CS21);
			break;
			case F_CPU_1024:TCCR2 |= (1<<CS22) | (1<<CS21) | (1<<CS20);
			break;
			}
		}break;
		}
	}
	}

}
/*
 * Description: Function to set the Call Back function address to timer 0.
 */
void TIMER_setCallBackT0(void(*a_ptr)(void)){
	g_callBackPtrT0 = a_ptr;
}
/*
 * Description: Function to set the Call Back function address to timer 1.
 */
void TIMER_setCallBackT1(void(*a_ptr)(void)){
	g_callBackPtrT1 = a_ptr;
}
/*
 * Description: Function to set the Call Back function address to timer 2.
 */
void TIMER_setCallBackT2(void(*a_ptr)(void)){
	g_callBackPtrT2 = a_ptr;
}
/*
 * Description: Function to disable the Timer
 */
void TIMER_DeInit(TIMER_number timer){
	switch(timer){
	case TIMER0: /*disable all timer 0 registers*/
		TCNT0 = 0;
		TCCR0 = 0;
		OCR0 = 0;
		TIMSK &= 0xFC;
		break;
	case TIMER1:/*disable all timer 1 registers*/
		TCNT1 = 0;
		OCR1A = 0;
		OCR1B = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		TIMSK &= 0xC3;
		break;
	case TIMER2:/*disable all timer 2 registers*/
		TCNT2 = 0;
		TCCR2 = 0;
		OCR2 = 0;
		TIMSK &=0x3F;
		break;

	}
}
