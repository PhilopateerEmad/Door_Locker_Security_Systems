/********************************************************************************
 * MODULE : TIMER
 * File Name: timer1.h
 * Description:Header file for TIMER
 * Created on: Oct 23, 2021
 * Author: Philo
 *
 ********************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
/************************************************************************
                               definitions
************************************************************************/
typedef enum{
	TIMER0_ID,TIMER1_ID,TIMER2_ID
}Timer_Id;

typedef enum{
	TIMER0_NO_CLOCK,TIMER0_F_CPU_CLOCK,TIMER0_F_CPU_8,TIMER0_F_CPU_64,TIMER0_F_CPU_256,TIMER0_F_CPU_1024,TIMER0_EXTERNAL_FALLING,TIMER0_EXTERNAL_RISING
}Timer0_prescaler;

typedef enum{
	TIMER1_NO_CLOCK,TIMER1_F_CPU_CLOCK,TIMER1_F_CPU_8,TIMER1_F_CPU_64,TIMER1_F_CPU_256,TIMER1_F_CPU_1024,TIMER1_EXTERNAL_FALLING,TIMER1_EXTERNAL_RISING
}Timer1_prescaler;

typedef enum{
	TIMER2_NO_CLOCK,TIMER2_F_CPU_CLOCK,TIMER2_F_CPU_8,TIMER2_F_CPU_32,TIMER2_F_CPU_64,TIMER2_F_CPU_128,TIMER2_F_CPU_256,TIMER2_F_CPU_1024

}Timer2_prescaler;



typedef enum{
	NORMAL,COMPARE
}Timer_mode;


typedef struct
{
	Timer_Id timer_id;
	Timer_mode mode;
	uint8 clock;
	uint8 initial_value;
	uint8 compare_value;
}Timer_ConfigType;

/******************************************************************************************
                                   functions prototype
******************************************************************************************/

/*@description: function to initialize the timer driver
 * param1: Configuration pointer
 * -set which timer to operate
 * -set initial value of timer
 * -set the mode of the timer overflow or compare
 * -set the clock source clock and prescaler
 * -if in compare mode set compare value
 * return: none
 * */
void Timer_init(const Timer_ConfigType * Config_Ptr);


/*@description: function to set the call back function address of timer0
 * param1:address of the call back function
 * return: none
 * */
void Timer0_setCallBack(void(*a_ptr)(void));

/*@description: function to set the call back function address of timer1
 * param1:address of the call back function
 * return: none
 * */
void Timer1_setCallBack(void(*a_ptr)(void));

/*@description: function to set the call back function address of timer2
 * param1:address of the call back function
 * return: none
 * */
void Timer2_setCallBack(void(*a_ptr)(void));

/*@description: function to disable the timer
 * param1: Timer_Id to specify which timer to stop
 * return: none
 * */
void Timer_DeInit(Timer_Id timer_id);


#endif /* TIMER_H_ */
