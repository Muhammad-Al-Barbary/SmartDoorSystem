/******************************************************************************
 *
 * File Name: MC1.c
 *
 * Description: Source file for micro controller 1
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/

#include "uart.h"
#include "external_eeprom.h"
#include "motor.h"
#include "timer.h"
#include<util/delay.h>
#include <avr/io.h>
#include "buzzer.h"
uint8 timer_counter=0;
uint8 g_password[10];


uint8 CheckReceivedPassword();
void SetPassword();
void Motor(void);
void WrongPass();

uint8 g_password[10];

int main(void){
	SREG |= (1<<7);
	uint8 password_flag;
	uint8 key;
	DcMotor_Init();
	TIMER_ConfigType TimerConfig={TIMER1,COMPARE,F_CPU_1024,OCN_DISCONNECTED,COMPARE_A,0,4000};
	UART_Config uartConfig = {SIZE_8,DISABLED,BIT_1,9600};
	UART_init(&uartConfig);
	BUZZER_init();

	SetPassword();

	EEPROM_readString(0x0008,g_password);

	while(1){
		UART_sendByte(55);
		key=UART_receiveByte();
		password_flag=CheckReceivedPassword();
		while(UART_receiveByte()!=20);
		UART_sendByte(password_flag);

		switch(key){
		case 1:
			if (password_flag){
				TIMER_setCallBackT1(&Motor);
				timer_counter=0;
				TIMER_init(&TimerConfig);
				while(timer_counter<34);
			}
			else{
				WrongPass();
			}
			break;
		case 2:
			if (password_flag){
				SetPassword();
				EEPROM_readString(0x0008,g_password);
			}
			else{
				WrongPass();
			}
			break;
		}
	}
}

void SetPassword(){
	UART_sendByte(10);
	UART_receiveString(g_password);
	EEPROM_writeString(0x0008,g_password);
}

uint8 CheckReceivedPassword(){
	uint8 i;
	uint8 password_try[10];
	uint8 password_flag=1;

	UART_sendByte(111);
	UART_receiveString(password_try);
	for (i=0;i<5;i++){
		if (password_try[i] != g_password[i])
			password_flag=0;
	}

	return password_flag;
}

void WrongPass(){
	BUZZER_on();
	_delay_ms(2000);
	BUZZER_off();
}

void Motor(void){
	timer_counter++;
	if (timer_counter==1){
		DcMotor_Rotate(CW);
		UART_sendByte(timer_counter);
	}
	else if (timer_counter==6){
		DcMotor_Rotate(stop);
		UART_sendByte(timer_counter);
	}
	else if (timer_counter==29){
		DcMotor_Rotate(A_CW);
		UART_sendByte(timer_counter);
	}
	else if(timer_counter==34)
	{
		DcMotor_Rotate(stop);
		UART_sendByte(timer_counter);
		TIMER_DeInit(TIMER1);
	}
}
