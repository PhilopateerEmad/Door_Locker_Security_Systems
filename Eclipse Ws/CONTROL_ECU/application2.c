/********************************************************************************
 * MODULE : APPLICATION2
 * File Name: application2.c
 * Description:source file for application2
 * Created on: Oct 26, 2021
 * Author: Philo
 *
 ********************************************************************************/

#include"application2.h"
#include "uart.h"
#include "util/delay.h"
#include "dc_motor.h"
#include "twi.h"
#include "external_eeprom.h"
#include "buzzer.h"
/*****************************************************************************************
                                       global variables
*****************************************************************************************/
uint32 sec = 0;
uint32 ticks = 0;

/*****************************************************************************************
                                     functions Definitions
*****************************************************************************************/
/*@description: this function to sync communication between
 * the two UART devices this function asks the other device if it is ready
 * when the other device is ready it sends he is
 * param1: none
 * return: none
 * */
void static waitOtherAvailability(void){
	UART_sendByte(ARE_YOU_READY);
	while(UART_recieveByte()!=IS_READY);
}

/*@description: this function to sync communication between
 * the two UART devices this function responds to question of the other UART
 * device and doesn't respond till it is available*/
void static answeringAvailability(void){
	while(UART_recieveByte() != ARE_YOU_READY);
	UART_sendByte(IS_READY);
}

/*@description: this function to store password in temporarily array to use it when compare
 * param1: pointer to char array that password will be stored temporarily in it
 * return: none*/
void storePassword(uint8 *password){
	uint8 i;
	answeringAvailability();
	for(i = 0;i<PASSWORD_SIZE;i++){
		*(password+i) = UART_recieveByte();
		_delay_ms(10);
	}
}

/*@description: this function compare between two passwords
 * param1: first password
 * param2: second password
 * return if matched or not*/
uint8 comparePasswords(uint8 *password,uint8 *re_password){
	uint8 i;
	uint8 match_flag;
	for(i = 0;i<PASSWORD_SIZE;i++){
		if(*(password+i) != *(re_password+i)){
			match_flag = 0;
			return match_flag;
		}
	}
	match_flag = 1;
	return match_flag;
}

/*@description: this function is to store the password inside the EEPROM
 * to be permanently stored
 * param1: array of char contains the passwords to be stored in EEPROM
 * return: none */
void storeInEeprom(uint8 *password){
	uint8 i ;
	for(i = 0; i <PASSWORD_SIZE;i++){
		EEPROM_writeByte(START_STORE_ADDRESS_EEPROM+i, *(password+i));
		_delay_ms(10);
	}
	/*this consider as a flag if previously stored pass*/
	EEPROM_writeByte(FLAG_ADDRESS_IF_ALREADY_STORED_PASSWORD, 'P');
}

/*@description: this function compare the value of given password to that stored in EEPROM
 * param1: array of char contains the passwords to be compared with that stored in EEPROM
 * return: if the given password match with stored in EEPROM or not*/
uint8 static compareWithEeprom(uint8 *password){
	uint8 i;
	uint8 match_flag;
	uint8 eeprom_password[PASSWORD_SIZE];
	for(i = 0;i<PASSWORD_SIZE;i++){
		EEPROM_readByte(START_STORE_ADDRESS_EEPROM+i,&eeprom_password[i]);
		if(*(password+i) != *(eeprom_password+i)){
			match_flag = 0;
			return match_flag;
		}
	}
	match_flag = 1;
	return match_flag;
}

/*@description: this function is to specify to ALLOW access of the user or not
 * according to entered the right password or not
 * param1: password to check for
 * return: if the user allowed to access or not*/
uint8 isAllowedToAccess(uint8 *password){
	/*this counter to specify number of wrong passwords*/
	static uint8 counter = 0;
	uint8 is_matched_pass = 0;
	uint8 answer = YOU_ARE_BANNED;

	is_matched_pass = compareWithEeprom(password);
	waitOtherAvailability();
	if(is_matched_pass == MATCHED_PASSWORDS){
		counter = 0;
		answer = YOU_ARE_ALLOWED;
	}
	else if((is_matched_pass != MATCHED_PASSWORDS) && (counter<2)){
		counter++;
		answer = PLEASE_REPEAT_PASS;
	}
	else if((is_matched_pass != MATCHED_PASSWORDS) && (counter=2)){
		counter = 0;
		answer = YOU_ARE_BANNED;
	}

	UART_sendByte(answer);

	return answer;
}

/*@description: this function to check if two passwords sent are matched
 * param1: first password
 * param2: second password
 * return: if the matched or not */
uint8 isMatchedPassword(uint8 *password,uint8 *re_password){
	uint8 is_matched;
	is_matched = comparePasswords(password, re_password);
	waitOtherAvailability();
	UART_sendByte(is_matched);
	return is_matched;
}

/*@description: this functionto check if there is previously stored password in EEPROM
 * param1: address to read from in EEPROM
 * return: if there is previously stored or not*/
uint8 isFirstTime(uint16 u16addr){
	uint8 is_passoword_set_before;
	uint8 state;
	EEPROM_readByte(u16addr, &is_passoword_set_before);
	waitOtherAvailability();
	if(is_passoword_set_before != 'P'){
		UART_sendByte(NO_SAVED_PASSWORD_NOT_FOUND);
		state = NO_SAVED_PASSWORD_NOT_FOUND;
	}
	else{
		UART_sendByte(YES_SAVED_PASSWORD_FOUND);
		state = YES_SAVED_PASSWORD_FOUND;
	}

	return state;
}

/*@description: this function to receive from first micro controller
 * what option does the user need
 * param1: none;
 * return: the option sent from first device */
uint8 recieveMainOption(void){
	answeringAvailability();
	return UART_recieveByte();
}


/*@description: this is the call back function called by timer driver
 * and this function count 3 seconds
 * param1: none
 * return: none*/

void threeSecondsDelayTimer(void){
	ticks++;
	if(ticks==93){    /*31 = second*/
		sec =3;
		ticks = 0;
	}
}

/*@description: this is the call back function called by timer driver
 * and this function count 15 seconds
 * param1: none
 * return: none*/
void fifteenSecondsDelayTimer(void){
	ticks++;
	if(ticks == 465){
		sec =15;
		ticks = 0;
	}
}

/*@description: this is the call back function called by timer driver
 * and this function count one minute
 * param1: none
 * return: none*/
void oneMinuteDelayTimer(void){
	static uint8 count = 0;
	ticks++;
	if(ticks == 465){
		count++;
		ticks = 0;
		if(count == 4){
			sec = 60;
			count = 0;

		}
	}
}

/*@description: this function is to make delay for 15 seconds
 * param1: pointer to configuration structure to get timer id
 * return: none*/
void waitFifteenSeconds(const Timer_ConfigType * Config_Ptr){
	Timer0_setCallBack(fifteenSecondsDelayTimer);
	Timer_init(Config_Ptr);
	while(sec!=15);
	Timer_DeInit(Config_Ptr->timer_id);
	sec = 0;
}

/*@description: this function is to make delay for 3 seconds
 * param1: pointer to configuration structure to get timer id
 * return: none*/
void waitThreeSeconds(const Timer_ConfigType *Config_Ptr){
	Timer0_setCallBack(threeSecondsDelayTimer);
	Timer_init(Config_Ptr);
	while(sec!=3);
	Timer_DeInit(Config_Ptr->timer_id);
	sec = 0;
}

/*@description: this function is to make delay for one minute
 * param1: pointer to configuration structure to get timer id
 * return: none*/
void waitOneMinute(const Timer_ConfigType * Config_Ptr){
	Timer0_setCallBack(oneMinuteDelayTimer);
	Timer_init(Config_Ptr);
	while(sec!=60);
	Timer_DeInit(Config_Ptr->timer_id);
	sec = 0;
}
