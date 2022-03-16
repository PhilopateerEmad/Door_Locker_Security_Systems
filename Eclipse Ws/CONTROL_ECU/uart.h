/*
 * MODULE : UART
 * File Name: uart.h
 * Description:Header file for the AVR UART
 * Created on: Oct 28, 2021
 * Author: Philo
 */

#ifndef UART_H_
#define UART_H_

#include"std_types.h"

/************************************************************************
                               definitions
************************************************************************/
typedef enum{
	CHAR_SIZE_5_BITS,CHAR_SIZE_6_BITS,CHAR_SIZE_7_BITS,CHAR_SIZE_8_BITS,CHAR_SIZE_9_BITS=0x07
}Uart_CharacterSize;

typedef enum{
	NO_PARITY,EVEN_PARITY = 0x02,ODD_PARITY
}Uart_ParityMode;

typedef enum{
	STOP_1,STOP_2
}Uart_StopBitSelect;

typedef struct{
	Uart_CharacterSize char_size;
	Uart_ParityMode parity_mode;
	Uart_StopBitSelect stop_bit_select;
	uint32 baud_rate;

}Uart_ConfigType;

/******************************************************************************************
                                   functions prototype
******************************************************************************************/

/*@description: this function initialize UART by:
 * -Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * -enable UART
 * -set baud rate
 * param1: pointer to configuration structure
 * return: none
 * */
void UART_init(const Uart_ConfigType *Config_Ptr);

/*@description: function to send byte to the other UART device
 * param1: data the byte to be sent
 * return: none*/
void UART_sendByte(const uint8 data);

/*@description: function to receive byte from the other UART device
 * param1: none
 * return: received byte from the other UART device */
uint8 UART_recieveByte(void);

/*@description: function to send string to the other UART device
 * param1: the string to be sent
 * return: none */
void UART_sendString(const uint8 *Str);

/*@description: function to receive string from the other UART device
 * param1: address of array of current to store the string inside it
 * return: none*/
void UART_receiveString(uint8 *Str);



#endif /* UART_H_ */
