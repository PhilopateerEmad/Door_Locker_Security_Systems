/********************************************************************************
 * MODULE : LCD
 * File Name: lcd.c
 * Description:Source file for LCD
 * Created on: Oct 5, 2021
 * Author: Philo
 ********************************************************************************/
#include <util/delay.h>
#include <stdlib.h>
#include "gpio.h"
#include "common_macros.h"
#include "lcd.h"


/*******************************************************************************
                             Functions Prototypes
 *******************************************************************************/

/*@description: this function is responsible for initialization of the LCD
 * param1: none
 * return: none*/
void LCD_init(void){
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);  /*set pin as output to RS of LCD*/
	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);  /*set pin as output to RW of LCD*/
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);      /*set pin as output to E of LCD */


#if (LCD_DATA_BITS_MODE == 4)

	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+1,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+2,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+3,PIN_OUTPUT);

	LCD_sendCommand(LCD_GO_TO_HOME);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);   /*set a port as output to DATA of the LCD*/
	/*in case of 8 Data bits mode send command of two lines8 bits mode 5*7 dot display Mode*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif
	LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_OFF); /*off cursor*/
	LCD_sendCommand(LCD_CLEAR_COMMAND);  /*clear the LCD at the beginning (display nothing at the beginning)*/
}


/*@description: send the required command to LCD
 * param1: command is the value of the corresponding command
 * return: none*/
void LCD_sendCommand(uint8 command){
#if (LCD_DATA_BITS_MODE == 4)
	uint8 lcd_port_value = 0;
#endif
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID,LOGIC_LOW); /*RS = 0 -> select command register*/
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);  /*RW = 0 -> select write*/
	_delay_ms(1);  /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /*E = 1 -> enable LCD display*/
	_delay_ms(1);/* delay for processing Tpw - Tdws = 190ns */

#if (LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required command to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (command & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((command & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the first 4 bits of the required command to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((command & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (command & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8) /*in case of 8-bit DATA mode*/
	GPIO_writePort(LCD_DATA_PORT_ID,command); /* send the command to data bus from D0 ----> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Enable = 0 -> disable LCD */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif


}

/*@description: this function is required to display a character to the screen
 * param1: data is the char we want to display
 * return: none*/
void LCD_displayCharacter(uint8 data){
#if (LCD_DATA_BITS_MODE == 4)
	uint8 lcd_port_value = 0;
#endif
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH); /*RS = 1 -> data option is selected*/
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);  /*RW = 0 -> write option is selected*/
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);   /*Enable = 1 -> enable LCD*/
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */


#if (LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required data to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (data & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((data & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the first 4 bits of the required data to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((data & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (data & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8) /*in case of 8-bit DATA mode*/
	GPIO_writePort(LCD_DATA_PORT_ID,data); /*write the data to bus D0 -> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Enable = 0 ->   Disable LCD*/
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

/*@description: this function is required to display a string to the screen
 * param1: *str is pointer to the first location of the string(array of char)
 * and const as this function is prohibited to modify the value of the string
 * return: none*/
void LCD_displayString(const char *str){
	/*loop across the String(array of char) and wait for null when null detected escape looping*/
	while((*str) != '\0'){
		LCD_displayCharacter(*str); /*calling displayCharacter function and send asterisk of the pointer (the current char) */
		str++;  /*increment the pointer position*/
	}
}

/*@description: move the cursor to a specified row and specified column
 * param1: row is the specified row
 * param2: col is the specified column
 * return: none*/
void LCD_moveCursor(uint8 row ,uint8 col){
	uint8 lcd_memory_address;
	/*select the required address in the LCD DDRAM*/
	switch(row){

	case 0: lcd_memory_address = col;
	break;

	case 1: lcd_memory_address = col+0x40;
	break;

	case 2: lcd_memory_address = col+0x10;
	break;

	case 3: lcd_memory_address = col +0x50;
	break;
	}
	/*send the mapped address to set the location of the cursor */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*@description: display string starting from specified row and certain column
 * param1: row is the specified row
 * param2: col is the specified column
 * param3: *str is pointer to first element in the string(array of char)
 * return: none*/
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str){
	LCD_moveCursor(row, col);  /*jump to cursor position*/
	LCD_displayString(str);   /*pass the address of the string to the displayString function*/
}


/*@description: convert an integer to a string to display the integer
 * param1: data is the value of the integer we want to display
 * return: none*/
void LCD_integerToString(short data){
	char buffer[16]; /*16 as the size of the short */
	 /*itoa is integer to array std function
	  * param1: integer data
	  * param2: the array of char(string) that will have the value of the integer
	  * param3: integer conversion base*/
	itoa(data,buffer,10);
	LCD_displayString(buffer);/*display the string(integer after conversion)*/
}

/*@description: clear the screen and return the cursor to the first row and column
 * param1: none
 * return: none*/
void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);/*clear the display and set cursor to first row and first col*/
}



