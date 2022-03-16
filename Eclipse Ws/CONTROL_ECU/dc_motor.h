/********************************************************************************
 * MODULE : DC MOTOR
 * File Name: dc_motor.h
 * Description:Header file for DC motor
 * Created on: Oct 6, 2021
 * Author: Philo
 ********************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include"std_types.h"
#include"gpio.h"
/*********************************************************************************
                             Definitions
 *********************************************************************************/
#define DCMOTOR_ENABLE_PORT             PORTD_ID
#define DCMOTOR_ENABLE_PIN              PIN6_ID

#define DCMOTOR_INPUTS_PORT             PORTD_ID
#define DCMOTOR_IN_A_PORT               PORTD_ID
#define DCMOTOR_IN_A_PIN                PIN4_ID

#define DCMOTOR_IN_B_PORT               PORTD_ID
#define DCMOTOR_IN_B_PIN                PIN5_ID



typedef enum{
	OFF,ON
}DcMotor_State;

typedef enum{
	STOP = 0x00,CLOCKWISE = (1<<DCMOTOR_IN_A_PIN),ANTI_CLOCKWISE=(1<<DCMOTOR_IN_B_PIN)
}DcMotor_Mode;


/**********************************************************************************
                              functions prototype
*************************************************************************************/
/*@description: this function to initialize the DC motor*/
void DcMotor_Init(void);

/*@description: this function is to control the state of the DC motor and specify its speed*/
void DcMotor_Rotate(DcMotor_Mode mode);


#endif /* DC_MOTOR_H_ */
