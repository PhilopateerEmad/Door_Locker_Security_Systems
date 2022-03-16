/********************************************************************************
 * MODULE : APPLICATION1
 * File Name: application1.c
 * Description:source file for application1
 * Created on: Oct 26, 2021
 * Author: Philo
 *
 ********************************************************************************/

#include"application1.h"
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "util/delay.h"

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
	while(UART_recieveByte() != IS_READY);
}


/*@description: this function to sync communication between
 * the two UART devices this function responds to question of the other UART
 * device and doesn't respond till it is available*/
void static answeringAvailability(void){
	while(UART_recieveByte() != ARE_YOU_READY);
	UART_sendByte(IS_READY);
}

/*@description: this function check if it is first time to set password
 * as our system have the ability to take user from user first time only to set it
 * but if it is not the first time the system will asks the user to enter stored password to do any operation
 * param1: none
 * return: respond from the other UART device if it is first time or not*/
uint8 isFirstTime(void){
	answeringAvailability();
	return UART_recieveByte();
}


/*@description: this function is responsible to take the password from the user
 * param1: pointer to the array of char to store the password inside it
 * return: none*/
void getPassword(uint8 *password){
	uint8 i = 0; /*variable used for looping*/
	uint8 key;
	waitOtherAvailability();

	while(i<PASSWORD_SIZE){
		key = KEYPAD_getPressedKey();
		/*only numbers password is allowed*/
		if(key>=0 && key<=9){
			*(password+i) = key; /**/
			LCD_displayCharacter('*');
			_delay_ms(450);
			i++;
		}
	}
	/*wait until the user select enter */
	while(KEYPAD_getPressedKey()!= ENTER);
	_delay_ms(450);
}

/*@description:this function ask the other UART if the entered passwords are matched
 * param1: none
 * return: if matched or not*/
uint8 isMatchedPassword(void){
	answeringAvailability();
	return UART_recieveByte();
}

/*@description:this function ask the other device to give access or not
 * param1: none
 * return: access or not*/
uint8 getAccessOptions(void){
	answeringAvailability();
	return UART_recieveByte();
}

/*@description: this function send to the other UART device what option does the
 * user need
 * param1: the main option we want to excute
 * return: none*/
void sendMainOption(uint8 main_option){
	waitOtherAvailability();
	UART_sendByte(main_option);
}

/*@description: this function send password entered by user to the other UART device
 * param1: pointer to the password array
 * return: none*/
void sendPassword(const uint8 *password){
	uint8 i;
	/*looping and send byte byte*/
	for(i = 0;i<PASSWORD_SIZE;i++){
		UART_sendByte(*(password+i));
		_delay_ms(50);
	}
}

/*@description: this function is responsible to display on the screen the main options
 * and wait the user to select the option
 * param1: none
 * return: the chosen option  */
uint8 displayMainOptions(void){
	uint8 main_option;
	displayOnLCD(MAIN_OPTIONS);
	do{
		main_option = KEYPAD_getPressedKey();
	}while(!((main_option == OPEN_DOOR) || (main_option== CHANGE_PASSWORD)));/*take only the two options as input*/
	_delay_ms(450);
	return main_option;
}

/*@description: this function calling LCD displaying methods
 * param1: the message to be printed
 * return: none
 * */
void displayOnLCD(uint16 message){
	LCD_clearScreen();
	switch (message) {

		case WELCOMING:
			LCD_displayString("    Welcome!   ");
			_delay_ms(700);
			break;

		case ENTER_PASSWORD:
			LCD_displayStringRowColumn(0, 0, "Enter Pass");
			LCD_moveCursor(1, 0);
			break;

		case CONFIRM_PASSWORD:
			LCD_displayStringRowColumn(0, 0, "ReEnter Pass");
			LCD_moveCursor(1, 0);
			break;

		case NOT_MATCHED_PASSWORD:
			LCD_displayStringRowColumn(0, 0, "Mismatched Pass!");
			_delay_ms(1300);
			break;

		case WRONG_PASSWORD:
			LCD_displayStringRowColumn(0, 0, "Wrong Pass!!!");
			_delay_ms(900);
			break;
		case MAIN_OPTIONS:
			LCD_displayStringRowColumn(0, 0, "+ Open Door");
			LCD_displayStringRowColumn(1, 0, "- Change Pass");
			break;
		case ALERT:
			LCD_displayString("Alert!!!!!!");
			break;
		case DOOR_UNLOCKING:
			LCD_displayString("Door unlocking");
			break;
		case PROCESSING:
			LCD_displayString("Please hold");
			break;
		case DOOR_LOCKING:

			LCD_displayString("Door locking");
			break;
		case ENTER_NEW_PASSWORD:
			LCD_displayStringRowColumn(0, 0, "Enter new Pass");
			LCD_moveCursor(1, 0);
			break;
		case CONFIRM_NEW_PASSWORD:
			LCD_displayStringRowColumn(0, 0, "Confirm new Pass");
			LCD_moveCursor(1, 0);
			break;
		case SUCCESS_CHANGED:
			LCD_displayStringRowColumn(0, 0, "  Pass changed");
			LCD_displayStringRowColumn(1, 0, " Successfully!!");
			_delay_ms(900);
			break;
		default:
			break;
	}

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


