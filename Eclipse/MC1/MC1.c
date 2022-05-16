/******************************************************************************
 *
 * File Name: MC1.c
 *
 * Description: Source file for micro controller 1
 *
 * Author: Muhammad Al-Barbary
 *
 *******************************************************************************/
#include "std_types.h"
#include"lcd.h"
#include"keypad.h"
#include<util/delay.h>
#include "uart.h"

void SetPassword(void);
void Menu();
void CheckPassword();
void WrongPass();


int main(void){
	UART_Config uartConfig ={SIZE_8,DISABLED,BIT_1,9600};
	UART_init(&uartConfig);
	LCD_init();
	SetPassword();

	while(1){
		Menu();
	}
}


void Menu(){
	uint8 key;
	uint8 password_flag;
	uint8 timer_counter;
	LCD_clearScreen();
	LCD_displayString("1: Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("2: Change Pass");

	do{
		key=KEYPAD_getPressedKey();
	}while( key != 1  && key != 2);

	while(UART_receiveByte() != 55);
	UART_sendByte(key);
	_delay_ms(500);
	CheckPassword();
	UART_sendByte(20);
	password_flag=UART_receiveByte();

	LCD_clearScreen();

	switch(key){
	case 1:
		if (password_flag)
		{
			do{
				timer_counter=UART_receiveByte();
				if (timer_counter==1){
					LCD_clearScreen();
					LCD_displayString("Opening");
				}
				else if (timer_counter==6){
					LCD_clearScreen();
					LCD_displayString("Door Open");
				}
				else if (timer_counter==29){
					LCD_clearScreen();
					LCD_displayString("Closing");
				}
				else if (timer_counter==34)
				{
					LCD_clearScreen();
				}
			}while (timer_counter != 34);
		}
		else{
			WrongPass();
		}
		break;
	case 2:
		if (password_flag)
		{
			SetPassword();
		}
		else{
			WrongPass();
		}
		break;
	}
}
void WrongPass(){
	LCD_clearScreen();
	LCD_displayString("Wrong Password!");
	_delay_ms(2000);
}

void CheckPassword(){
	uint8 i;
	uint8 password_try[10];
	LCD_clearScreen();
	LCD_displayString("Enter Password:");
	for (i=0;i<5;i++){
		password_try[i]=KEYPAD_getPressedKey();
		LCD_displayStringRowColumn(1,i,"*");
		_delay_ms(50);
	}
	password_try[i]='#';
	password_try[++i]='\0';
	while(UART_receiveByte()!=111);
	UART_sendString(password_try);
}

void SetPassword(){
	uint8 i;
	uint8 password_flag = 0;
	uint8 password_try1[10];
	uint8 password_try2[10];

	while(password_flag ==0){
		LCD_clearScreen();
		LCD_displayString("New Password:");

		for (i=0;i<5;i++){
			password_try1[i]=KEYPAD_getPressedKey();
			LCD_displayStringRowColumn(1,i,"*");
			_delay_ms(50);
		}

		LCD_clearScreen();
		LCD_displayString("Confirm:");

		for (i=0;i<5;i++){
			password_try2[i]=KEYPAD_getPressedKey();
			LCD_displayStringRowColumn(1,i,"*");
			_delay_ms(50);
		}

		password_flag=1;
		for (i=0;i<5;i++){
			if (password_try1[i] != password_try2[i])
				password_flag=0;
		}

		if (password_flag)
		{
			password_try1[i]='#';
			password_try1[++i]='\0';
			while(UART_receiveByte() != 10);
			LCD_clearScreen();
			UART_sendString(password_try1);
		}
		else{
			LCD_clearScreen();
			LCD_displayString("Mismatch!");
			_delay_ms(1000);
		}
	}
}
