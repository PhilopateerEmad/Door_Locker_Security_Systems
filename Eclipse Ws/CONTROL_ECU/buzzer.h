/********************************************************************************
 * MODULE : BUZZER
 * File Name: buzzer.h
 * Description:Header file for BUZZER
 * Created on: Oct 30, 2021
 * Author: Philo
 ********************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include"std_types.h"
/**********************************************************************************
 *                             Definitions
 * *******************************************************************************/
#define BUZZER_PORT_ID       PORTB_ID
#define BUZZER_PIN_ID        PIN0_ID

/**********************************************************************************
 *                             functions prototype
 * *******************************************************************************/


void BUZZER_init(void);

void BUZZER_ON(void);

void BUZZER_OFF(void);

#endif /* BUZZER_H_ */
