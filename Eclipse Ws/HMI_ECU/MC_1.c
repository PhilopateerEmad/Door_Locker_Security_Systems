/********************************************************************************
 * File Name: MC_1.c
 * Description:source file for main app
 * Created on: Oct 26, 2021
 * Author: Philo
 *
 ********************************************************************************/
#include "application1.h"
#include "uart.h"
#include "lcd.h"
#include "avr/io.h"  /*to use SREG register*/

int main(){
	Timer_ConfigType timer_config_ptr = {TIMER0_ID,COMPARE,TIMER0_F_CPU_1024,0,252};   /*ovf init = 4*/
	uint8 password[PASSWORD_SIZE];
	uint8 access_options;
	uint8 main_options;
	uint8 escape_loop = 0;
	Uart_ConfigType uart_config_ptr ={CHAR_SIZE_8_BITS,NO_PARITY,STOP_1,9600};
	UART_init(&uart_config_ptr);
	LCD_init();
	SREG = (1<<7);
	displayOnLCD(WELCOMING);


	if(isFirstTime() == NO_SAVED_PASSWORD_NOT_FOUND){ /*check if there is stored previous password*/
		while(1){ /*will not escape loop till user enterd two matched passwords*/
			displayOnLCD(ENTER_PASSWORD);
			getPassword(password);
			sendPassword(password);
			displayOnLCD(CONFIRM_PASSWORD);
			getPassword(password);
			sendPassword(password);
			if(isMatchedPassword() == MATCHED_PASSWORDS){
				break;
			}
			displayOnLCD(NOT_MATCHED_PASSWORD);
		}
	}

	while(1){
		escape_loop =0;
		main_options = displayMainOptions();
		while(1){
			displayOnLCD(ENTER_PASSWORD);
			getPassword(password);
			sendPassword(password);
			access_options =getAccessOptions();

			if(access_options == YOU_ARE_BANNED){/*this condition happens if the other device restric access*/
				displayOnLCD(ALERT);
				waitOneMinute(&timer_config_ptr);
				escape_loop = 1;
			}
			else if(access_options == YOU_ARE_ALLOWED){
				sendMainOption(main_options);

				switch(main_options){ /*display on screen according to main option*/
				case OPEN_DOOR:

					displayOnLCD(DOOR_UNLOCKING);
					waitFifteenSeconds(&timer_config_ptr);

					displayOnLCD(PROCESSING);
					waitThreeSeconds(&timer_config_ptr);

					displayOnLCD(DOOR_LOCKING);
					waitFifteenSeconds(&timer_config_ptr);

					displayOnLCD(PROCESSING);
					waitThreeSeconds(&timer_config_ptr);

					escape_loop = 1;
					break;
				case CHANGE_PASSWORD:
					while(1){
						/*get first pass*/
						displayOnLCD(ENTER_NEW_PASSWORD);
						getPassword(password);
						sendPassword(password);
						/*confirm pass*/
						displayOnLCD(CONFIRM_NEW_PASSWORD);
						getPassword(password);
						sendPassword(password);

						if(isMatchedPassword()== MATCHED_PASSWORDS){
							displayOnLCD(SUCCESS_CHANGED);
							escape_loop = 1;
							break;
						}
						displayOnLCD(NOT_MATCHED_PASSWORD);

					}
					break;
				default:
					break;

				}

			}

			if(escape_loop){
				break;
			}
			displayOnLCD(WRONG_PASSWORD);/*if user entered wrong pass*/

		}

	}


}





