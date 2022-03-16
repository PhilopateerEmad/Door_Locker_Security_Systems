/********************************************************************************
 * File Name: MC_2.c
 * Description:source file for MC_2.c
 * Created on: Oct 26, 2021
 * Author: Philo
 *
 ********************************************************************************/

#include"application2.h"
#include "uart.h"
#include "twi.h"
#include "avr/io.h"
#include "dc_motor.h"
#include "buzzer.h"

int main(){
	Timer_ConfigType timer_config_ptr = {TIMER0_ID,COMPARE,TIMER0_F_CPU_1024,0,252};
	uint8 password[PASSWORD_SIZE];
	uint8 re_password[PASSWORD_SIZE];
	uint8 respondAccess;
	Uart_ConfigType uart_config_ptr ={CHAR_SIZE_8_BITS,NO_PARITY,STOP_1,9600};
	UART_init(&uart_config_ptr);
	DcMotor_Init();
	Twi_ConfigType twi_config_ptr = {0x02,PRESCALER_1,MY_ADDRESS};
	TWI_init(&twi_config_ptr);
	BUZZER_init();
	SREG = (1<<7);

	if(isFirstTime(FLAG_ADDRESS_IF_ALREADY_STORED_PASSWORD)==NO_SAVED_PASSWORD_NOT_FOUND){

		while(1){
			storePassword(password);

			storePassword(re_password);

			if(isMatchedPassword(password,re_password)==MATCHED_PASSWORDS){
					break;
			}
		}

		storeInEeprom(password);
	}


	while(1){
		storePassword(password);

		respondAccess=isAllowedToAccess(password);

		if(respondAccess==YOU_ARE_BANNED){

			BUZZER_ON();

			waitOneMinute(&timer_config_ptr);
			BUZZER_OFF();
		}

		else if(respondAccess==YOU_ARE_ALLOWED){
			switch (recieveMainOption()) {
			case OPEN_DOOR:
				DcMotor_Rotate(CLOCKWISE);

				waitFifteenSeconds(&timer_config_ptr);

				DcMotor_Rotate(STOP);


				waitThreeSeconds(&timer_config_ptr);
				DcMotor_Rotate(ANTI_CLOCKWISE);

				waitFifteenSeconds(&timer_config_ptr);
				DcMotor_Rotate(STOP);

				waitThreeSeconds(&timer_config_ptr);
				break;
			case CHANGE_PASSWORD:
				while(1){

					storePassword(password);


					storePassword(re_password);

					if(isMatchedPassword(password,re_password)==MATCHED_PASSWORDS){
							break;
					}
				}

				storeInEeprom(password);


				break;
			default:
				break;
			}
		}

		else{
			DcMotor_Rotate(STOP);
		}

	}
}
