/************************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the BUZZER driver
 *
 * Author: Muhammad Al-Barbary
 *
 ***********************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad port configuration */
#define BUZZER_PORT_ID					PORTA_ID
#define BUZZER_PIN_ID					PIN0_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * setup the buzzer pin direction
 */
void BUZZER_init(void);
/*
 * Description:
 * turn on the buzzer
 */
void BUZZER_on(void);

/*
 * Description:
 * turn off the buzzer
 */
void BUZZER_off(void);

#endif /* BUZZER_H_ */
