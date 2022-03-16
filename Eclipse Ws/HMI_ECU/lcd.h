/********************************************************************************
 * MODULE : LCD
 * File Name: lcd.h
 * Description:Header file for LCD
 * Created on: Oct 5, 2021
 * Author: Philo
 *
 ********************************************************************************/
#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"

/*******************************************************************
                         Definitions
********************************************************************/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#if (LCD_DATA_BITS_MODE == 4)

/* if LCD_LAST_PORT_PINS is defined in the code, the LCD driver will use the last 4 pins in the gpio port for for data.
 * To use the first four pins in the gpio port for data just remove LCD_LAST_PORT_PINS */
#define LCD_LAST_PORT_PINS
#ifdef  LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID         PIN4_ID
#else
#define LCD_FIRST_DATA_PIN_ID         PIN0_ID
#endif
#endif



/*Register select definitions*/
#define LCD_RS_PORT_ID              PORTC_ID
#define LCD_RS_PIN_ID               PIN0_ID

/*read write definitions*/
#define LCD_RW_PORT_ID              PORTC_ID
#define LCD_RW_PIN_ID               PIN1_ID

/*Enable data definitions*/
#define LCD_E_PORT_ID               PORTC_ID
#define LCD_E_PIN_ID                PIN2_ID

/*PORT data definitions*/
#define LCD_DATA_PORT_ID            PORTA_ID



/*LCD Commands*/

#define LCD_CLEAR_COMMAND                          0x01
#define LCD_GO_TO_HOME                             0x02
#define LCD_CURSOR_SHIFT_TO_LEFT                   0X04
#define LCD_DISPLAY_SHIFT_TO_RIGHT                 0x05
#define LCD_CURSOR_SHIFT_TO_RIGHT                  0X06
#define LCD_DISPLAY_SHIFT_TO_LEFT                  0x07
#define LCD_DISPLAY_OFF_CURSOR_OFF                 0x08
#define LCD_DISPLAY_OFF_CURSOR_ON                  0x0A
#define LCD_DISPLAY_ON_CURSOR_OFF                  0x0C
#define LCD_DISPLAY_ON_CURSOR_ON                   0x0E
#define LCD_DISPLAY_ON_CURSOR_BLINKING             0x0F
#define LCD_SHIFT_CURSOR_POSITION_TO_LEFT          0x10
#define LCD_SHIFT_CURSOR_POSITION_TO_RIGHT         0x14
#define LCD_SHIFT_ENTIRE_DISPLAY_TO_LEFT           0x18
#define LCD_SHIFT_ENTIRE_DISPLAY_TO_RIGHT          0x1C
#define LCD_SET_CURSOR_LOCATION                    0x80
#define LCD_SET_CURSOR_LOCATION_SECOND_LINE        0xC0
#define LCD_TWO_LINES_FOUR_BITS_MODE               0x28
#define LCD_TWO_LINES_EIGHT_BITS_MODE              0x38



/*******************************************************************************
                             Functions Prototypes
 *******************************************************************************/

/*@description: this function is responsible for initialization of the LCD
 * param1: none
 * return: none*/
void LCD_init(void);

/*@description: send the required command to LCD
 * param1: command is the value of the corresponding command
 * return: none*/
void LCD_sendCommand(uint8 command);

/*@description: this function is required to display a character to the screen
 * param1: data is the char we want to display
 * return: none*/
void LCD_displayCharacter(uint8 data);

/*@description: this function is required to display a string to the screen
 * param1: *str is pointer to the first location of the string(array of char)
 * return: none*/
void LCD_displayString(const char *str);

/*@description: move the cursor to a specified row and specified column
 * param1: row is the specified row
 * param2: col is the specified column
 * return: none*/
void LCD_moveCursor(uint8 row, uint8 col);

/*@description: display string starting from specified row and certain column
 * param1: row is the specified row
 * param2: col is the specified column
 * param3: *str is pointer to first element in the string(array of char)
 * return: none*/
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str);

/*@description: convert an integer to a string to display the integer
 * param1: data is the value of the integer we want to display
 * return: none*/
void LCD_integerToString(short data);

/*@description: clear the screen and return the cursor to the first row and column
 * param1: none
 * return: none*/
void LCD_clearScreen(void);

#endif /* LCD_H_ */
