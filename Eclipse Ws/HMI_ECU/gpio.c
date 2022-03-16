/*
 * MODULE : GPIO
 * File Name: gpio.c
 * Description:Source file for the AVR GPIO driver
 * Created on: Sep 30, 2021
 * Author: Philo
 */

#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the I/O Ports Registers */


/*@description: setup weather the function is input or output
 *  param1: port_num is the specified port number
 *  param2: pin_num is specified pin number
 *  param3: the direction of certain pin in certain port
 *  return: none*/
void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction){
	/*check if the input port number is greater than number of ports
	 * or if the number of the input pin is greater than number of pins per port
	 * in this case if it happened it will do nothing */

	if((port_num>=NUM_OF_PORTS)||(pin_num>=NUM_OF_PINS_PER_PORT)){
		/*do nothing*/
	}
	else{
		/*set pin direction according to given parameters */
		switch(port_num){
		case PORTA_ID :
			if(direction==PIN_OUTPUT){
				SET_BIT(DDRA,pin_num);
			}
			else{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID :
			if(direction ==PIN_OUTPUT){
				SET_BIT(DDRB,pin_num);
			}
			else{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;

		case PORTC_ID :
			if(direction==PIN_OUTPUT){
				SET_BIT(DDRC,pin_num);
			}
			else{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID :
			if(direction==PIN_OUTPUT){
				SET_BIT(DDRD,pin_num);
			}
			else{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}


/*@description: write the value of specific pin weather LOGIC high or LOGIC low
                if pin is input this function will control to turn on or turn off the Pull-up resistor
 *  param1: port_num is the specified port number
 *  param2: pin_num is specified pin number
 *  param3: value is the value of certain pin in certain port
 *  return: none*/
void GPIO_writePin(uint8 port_num,uint8 pin_num, uint8 value){
	/*check if the input port number is greater than number of ports
	 * or if the number of the input pin is greater than number of pins per port
	 * in this case if it happened it will do nothing */
	if((port_num >= NUM_OF_PORTS)||(pin_num>=NUM_OF_PINS_PER_PORT)){
		/*do nothing*/
	}
	else{
		/*write in a certain pin according to given parameters */
		switch(port_num){
		case PORTA_ID:
			if(value==LOGIC_HIGH){
				SET_BIT(PORTA,pin_num);
			}
			else{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value==LOGIC_HIGH){
				SET_BIT(PORTB,pin_num);
			}
			else{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;

		case PORTC_ID:
			if(value==LOGIC_HIGH){
				SET_BIT(PORTC,pin_num);
			}
			else{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;

		case PORTD_ID:
			if(value==LOGIC_HIGH){
				SET_BIT(PORTD,pin_num);
			}
			else{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}


/*@description: read the value of specific pin in a certain port
 * param1: port_num is the specified port number
 * param2: pin_num is specified pin number
 * return: the value of the specified pin (LOGIC_LOW or LOGIC_HIGH)  */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num){
	uint8 result = LOGIC_LOW; /*default value is LOGIC_LOW*/
	/*check if the input port number is greater than number of ports
	 * or if the number of the input pin is greater than number of pins per port
	 * in this case if it happened it will do nothing */
	if((port_num>=NUM_OF_PORTS)||(pin_num>=NUM_OF_PINS_PER_PORT)){
		/*do nothing*/
	}
	else{
		/*read a certain pin according to given parameters */
		switch (port_num) {
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pin_num)){
				result = LOGIC_HIGH;
			}
			else{
				result = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num)){
				result = LOGIC_HIGH;
			}
			else{
				result = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num)){
				result = LOGIC_HIGH;
			}
			else{
				result = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num)){
				result = LOGIC_HIGH;
			}
			else{
				result = LOGIC_LOW;
			}
			break;
		}
	}
	return result;
}


/*@description: set a port as input or output
 * param1: port_num is the specified port number
 * param2: direction is direction of specified port as input or output
 * return: none */
void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction)
{
	/*check if the input port number is greater than number of ports
	 * in this case if it happened it will do nothing */
	if(port_num >= NUM_OF_PORTS)
	{
	/*do nothing*/
	}
	else
	{
		/*set the direction of a port according to given parameters */
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}



/*@description: write a value in the full port if the port is assigned as input
 *              this function act to activate pull-up resistor for all pins
 *param1: port_num is the specified port number
 *param2: value is the value to be written in the port
 *return: none */
void GPIO_writePort(uint8 port_num,uint8 value){
	/*check if the input port number is greater than number of ports
	 * in this case if it happened it will do nothing */
	if(port_num>=NUM_OF_PORTS){
		/*do nothing*/
	}
	else{
		/*select certain port to write in*/
		switch(port_num){
		case PORTA_ID:
			PORTA=value;
			break;
		case PORTB_ID:
			PORTB=value;
			break;
		case PORTC_ID:
			PORTC=value;
			break;
		case PORTD_ID:
			PORTD=value;
			break;
		}
	}
}


/*@description: returns the value of the specified port
 *param1: port_num is the specified port number
 *return: value specified in certain port  */
uint8 GPIO_readPort(uint8 port_num){
	uint8 result = 0;
	if(port_num>=NUM_OF_PORTS){

	}
	else{
		switch(port_num){
		case PORTA_ID:
			result =PINA;
			break;
		case PORTB_ID:
			result =PINB;
			break;
		case PORTC_ID:
			result =PINC;
			break;
		case PORTD_ID:
			result =PIND;
			break;
		}
	}
	return result;
}





