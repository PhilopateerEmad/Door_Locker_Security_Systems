/*
 * MODULE : UART
 * File Name: uart.h
 * Description:Header file for the AVR UART
 * Created on: Oct 28, 2021
 * Author: Philo
 */

#include "uart.h"
#include "avr/io.h"
#include "common_macros.h"

/******************************************************************************************
                                   functions definitions
******************************************************************************************/

/*@description: this function initialize UART by:
 * -Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * -enable UART
 * -set baud rate
 * param1: pointer to configuration structure
 * return: none
 * */

void UART_init(const Uart_ConfigType *Config_Ptr){
	uint16 ubrr_value = 0;
	UCSRA = (1<<U2X);/*double transmission speed*/
	/*enable transmitter and receiver */
	UCSRB = (1<<RXEN)|(1<<TXEN)|(0x04 & Config_Ptr->char_size);
	/*select type of parity, select how many stop bit,select size of data*/
	UCSRC = (1<<URSEL) |(0x30 & Config_Ptr->parity_mode)|(0x08&Config_Ptr->stop_bit_select)|(0x06&Config_Ptr->char_size);
	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}



/*@description: function to send byte to the other UART device
 * param1: data the byte to be sent
 * return: none*/
void UART_sendByte(const uint8 data){
	/*UDRE flag is set when the Tx buffer (UDR) is empty and ready for
     transmitting a new byte so wait until this flag is set to one*/
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now*/
	UDR = data;
}

/*@description: function to receive byte from the other UART device
 * param1: none
 * return: received byte from the other UART device */
uint8 UART_recieveByte(void){
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC));

	/* Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data*/
	return UDR;
}

/*@description: function to send string to the other UART device
 * param1: the string to be sent
 * return: none */
void UART_sendString(const uint8 *Str){
	uint8 i = 0;
	/*loop to send all the string except the null we send byte by byte*/
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}


/*@description: function to receive string from the other UART device
 * param1: address of array of current to store the string inside it
 * return: none*/
void UART_receiveString(uint8 *Str){
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
