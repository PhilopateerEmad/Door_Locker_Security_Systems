/********************************************************************************
 * MODULE : DC MOTOR
 * File Name: dc_motor.c
 * Description:source file for DC motor
 * Created on: Oct 6, 2021
 * Author: Philo
 ********************************************************************************/


#include "dc_motor.h"
#include "gpio.h"


/**********************************************************************************
                              functions definitions
*************************************************************************************/

/*@description: this function to initialize the DC motor
 * param1: none
 * return: none*/
void DcMotor_Init(void){
	/*set the directions of the the pin of specified ports as output*/
	GPIO_setupPinDirection(DCMOTOR_IN_A_PORT, DCMOTOR_IN_A_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_IN_B_PORT, DCMOTOR_IN_B_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_ENABLE_PORT, DCMOTOR_ENABLE_PIN, PIN_OUTPUT);
	/*initialize the state of the motor in stop mode by writing 0x00 to the two pins
	 of the output pins  */
	GPIO_writePin(DCMOTOR_ENABLE_PORT, DCMOTOR_ENABLE_PIN, LOGIC_HIGH);
	GPIO_writePort(DCMOTOR_INPUTS_PORT,(DCMOTOR_INPUTS_PORT & 0x8F)|STOP);


}


/*@description: this function is to control the state of the DC motor and specify its speed
 param1: mode is the mode of the motor whether stop or clock-wise or anti-clock-wise direction
 return: none*/
void DcMotor_Rotate(DcMotor_Mode mode){
	GPIO_writePort(DCMOTOR_INPUTS_PORT,(DCMOTOR_INPUTS_PORT & 0x8F)|mode);
	GPIO_writePin(DCMOTOR_ENABLE_PORT, DCMOTOR_ENABLE_PIN, LOGIC_HIGH);
}
