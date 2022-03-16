/********************************************************************************
 * MODULE : GPIO
 * File Name: gpio.h
 * Description:Header file for the AVR GPIO driver
 * Created on: Sep 30, 2021
 * Author: Philo
 ********************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"

/*******************************************************************************
                               Definitions
 *******************************************************************************/
#define NUM_OF_PORTS                                   4
#define NUM_OF_PINS_PER_PORT                           8

#define PORTA_ID                                       0
#define PORTB_ID                                       1
#define PORTC_ID                                       2
#define PORTD_ID                                       3

#define PIN0_ID                                        0
#define PIN1_ID                                        1
#define PIN2_ID                                        2
#define PIN3_ID                                        3
#define PIN4_ID                                        4
#define PIN5_ID                                        5
#define PIN6_ID                                        6
#define PIN7_ID                                        7


/*******************************************************************************
                            Types Declaration
 *******************************************************************************/

typedef enum {
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum{
	PORT_INPUT,PORT_OUTPUT =0XFF
}GPIO_PortDirectionType;


/*******************************************************************************
                            Functions Prototypes
 *******************************************************************************/

/*@description: setup weather the function is input or output*/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*@description: write the value of specific pin weather LOGIC high or LOGIC low
if pin is input this function will control to turn on or turn off the Pull-up resistor
*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*@description: read the value of specific pin in a certain port */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*@description: set a port as input or output*/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*@description: write a value in the full port if the port is assigned as input
this function act to activate pull-up resistor for all pins
*/
void GPIO_writePort(uint8 port_num,uint8 value);

/*@description: returns the value of the specified port*/
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
