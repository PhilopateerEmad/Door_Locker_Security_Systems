/********************************************************************************
 * MODULE : APPLICATION1
 * File Name: application1.h
 * Description:Header file for application1
 * Created on: Oct 26, 2021
 * Author: Philo
 *
 ********************************************************************************/

#ifndef APPLICATION1_H_
#define APPLICATION1_H_
#include "std_types.h"

#include "mapping1.h"
#include "timer.h"

/************************************************************************
                               definitions
************************************************************************/
#define WELCOMING                   0x0100
#define ENTER_PASSWORD              0x0200
#define CONFIRM_PASSWORD            0x0300
#define WRONG_PASSWORD              0x0400
#define ALERT                       0x0500
#define DOOR_UNLOCKING              0x0600
#define PROCESSING                  0x0700
#define DOOR_LOCKING                0x0800
#define ENTER_NEW_PASSWORD          0x00AA
#define CONFIRM_NEW_PASSWORD        0x00AB
#define NOT_MATCHED_PASSWORD        0x0B00
#define MAIN_OPTIONS                0x01AC
#define SUCCESS_CHANGED             0x01BB

/*****************************************************************************************
                                     functions Definitions
*****************************************************************************************/
/*@description: this function check if it is first time to set password
 * as our system have the ability to take user from user first time only to set it
 * but if it is not the first time the system will asks the user to enter stored password to do any operation
 * param1: none
 * return: respond from the other UART device if it is first time or not*/
uint8 isFirstTime(void);

/*@description:this function ask the other UART if the entered passwords are matched
 * param1: none
 * return: if matched or not*/
uint8 isMatchedPassword(void);

/*@description:this function ask the other device to give access or not
 * param1: none
 * return: access or not*/
uint8 getAccessOptions(void);

/*@description: this function send to the other UART device what option does the
 * user need
 * param1: the main option we want to excute
 * return: none*/
void sendMainOption(uint8 option);

/*@description: this function is responsible to take the password from the user
 * param1: pointer to the array of char to store the password inside it
 * return: none*/
void getPassword(uint8 *password);

/*@description: this function send password entered by user to the other UART device
 * param1: pointer to the password array
 * return: none*/
void sendPassword(const uint8 *password);

/*@description: this function calling LCD displaying methods
 * param1: the message to be printed
 * return: none
 * */
void displayOnLCD(uint16 message);

/*@description: this function is responsible to display on the screen the main options
 * and wait the user to select the option
 * param1: none
 * return: the chosen option  */
uint8 displayMainOptions(void);

/*@description: this is the call back function called by timer driver
 * and this function count 3 seconds
 * param1: none
 * return: none*/
void threeSecondsDelayTimer(void);

/*@description: this is the call back function called by timer driver
 * and this function count 15 seconds
 * param1: none
 * return: none*/
void fifteenSecondsDelayTimer(void);

/*@description: this is the call back function called by timer driver
 * and this function count one minute
 * param1: none
 * return: none*/
void oneMinuteDelayTimer(void);

/*@description: this function is to make delay for 15 seconds
 * param1: pointer to configuration structure to get timer id
 * return: none*/
void waitFifteenSeconds(const Timer_ConfigType * Config_Ptr);

/*@description: this function is to make delay for 3 seconds
 * param1: pointer to configuration structure to get timer id
 * return: none*/
void waitThreeSeconds(const Timer_ConfigType *Config_Ptr);

/*@description: this function is to make delay for one minute
 * param1: pointer to configuration structure to get timer id
 * return: none*/
void waitOneMinute(const Timer_ConfigType * Config_Ptr);

#endif /* APPLICATION1_H_ */
