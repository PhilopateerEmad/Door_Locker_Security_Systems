 /******************************************************************************
 * File Name: mapping2.h
 * Description: messeges defined between the two UART devices
 * Created on: Oct 26, 2021
 * Author: Philo
 *******************************************************************************/
#ifndef MAPPING2_H_
#define MAPPING2_H_

#define START_STORE_ADDRESS_EEPROM                  0x300
#define FLAG_ADDRESS_IF_ALREADY_STORED_PASSWORD     0x200

#define ARE_YOU_READY         0x0A
#define IS_READY              0x0B
#define OPEN_DOOR           '+'
#define CHANGE_PASSWORD     '-'
#define PASSWORD_SIZE        5
#define ENTER               '='
#define MATCHED_PASSWORDS    1

#define YOU_ARE_ALLOWED        0x0C
#define PLEASE_REPEAT_PASS     0x0D
#define YOU_ARE_BANNED         0x0E
#define YES_SAVED_PASSWORD_FOUND  0x1A
#define NO_SAVED_PASSWORD_NOT_FOUND  0x2A
#define ALLOW_ACCESS           0x0F
#define RESTRICT_ACCESS        0x10
#define TRY_AGAIN              0x11

#endif /* MAPPING2_H_ */
