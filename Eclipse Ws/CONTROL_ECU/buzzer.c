/********************************************************************************
 * MODULE : BUZZER
 * File Name: buzzer.c
 * Description:Source file for BUZZER
 * Created on: Oct 30, 2021
 * Author: Philo
 ********************************************************************************/
#include "buzzer.h"
#include "gpio.h"
#include "common_macros.h"
/*@description: this function to initialize the pin connected to buzzer as output
 * param1: none
 * return: none
 * */
void BUZZER_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
}
/*@description: this function turn buzzer on
 * param1: none
 * return: none*/
void BUZZER_ON(void){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}
/*@description: this function turn buzzer off
 * param1: none
 * return: none*/
void BUZZER_OFF(void){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
