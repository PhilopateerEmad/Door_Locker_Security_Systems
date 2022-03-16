/********************************************************************************
 * MODULE : APPLICATION2
 * File Name: application2.h
 * Description:Header file for application2
 * Created on: Oct 26, 2021
 * Author: Philo
 ********************************************************************************/
#ifndef APPLICATION2_H_
#define APPLICATION2_H_
#include "std_types.h"
#include "mapping2.h"
#include "timer.h"
/*****************************************************************************************
                                     functions prototypes
*****************************************************************************************/

/*@description: this function to store password in temporarily array to use it when compare
 * param1: pointer to char array that password will be stored temporarily in it
 * return: none*/
void storePassword(uint8 *password);


/*@description: this function compare between two passwords
 * param1: first password
 * param2: second password
 * return if matched or not*/
uint8 comparePasswords(uint8 *password,uint8 *re_password);

/*@description: this function is to store the password inside the EEPROM
 * to be permanently stored
 * param1: array of char contains the passwords to be stored in EEPROM
 * return: none */
void storeInEeprom(uint8 *password);

/*@description: this function is to specify to ALLOW access of the user or not
 * according to entered the right password or not
 * param1: password to check for
 * return: if the user allowed to access or not*/
uint8 isAllowedToAccess(uint8 *password);

/*@description: this function to check if two passwords sent are matched
 * param1: first password
 * param2: second password
 * return: if the matched or not */
uint8 isMatchedPassword(uint8 *password,uint8 *re_password);

/*@description: this functiont check if there is previously stored password in EEPROM
 * param1: address to read from in EEPROM
 * return: if there is previously stored or not*/
uint8 isFirstTime(uint16 u16addr);

/*@description: this function to receive from first micro controller
 * what option does the user need
 * param1: none;
 * return: the option sent from first device */
uint8 recieveMainOption(void);


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

#endif /* APPLICATION2_H_ */
