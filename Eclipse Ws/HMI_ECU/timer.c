/********************************************************************************
 * MODULE : TIMER
 * File Name: timer.c
 * Description:source file for TIMER
 * Created on: Oct 23, 2021
 * Author: Philo
 *
 ********************************************************************************/

#include "timer.h"

#include "common_macros.h"
#include "avr/io.h"
#include "avr/interrupt.h"

/*****************************************************************************************
                                      global variables
*******************************************************************************************/
static volatile void (*g_Timer0CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1CallBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2CallBackPtr)(void) = NULL_PTR;
static uint8 timer0_ovf_initial_value = 0;
static uint16 timer1_ovf_initial_value = 0;
static uint8 timer2_ovf_initial_value = 0;

/*****************************************************************************************
                                Interrupt service routines
*****************************************************************************************/


/*****************************************************************************************
                                      timer0 ISRs
*****************************************************************************************/
ISR(TIMER0_OVF_vect){

	if(g_Timer0CallBackPtr != NULL_PTR)
	{
		TCNT0 = timer0_ovf_initial_value; /*in case of overflow mode initialize the timer with value specified from user each time*/
		(*g_Timer0CallBackPtr)();
	}
}

ISR(TIMER0_COMP_vect){
	if(g_Timer0CallBackPtr != NULL_PTR)
	{

		(*g_Timer0CallBackPtr)();
	}
}


/*****************************************************************************************
                                      timer1 ISRs
*****************************************************************************************/
ISR(TIMER1_OVF_vect){

	if(g_Timer1CallBackPtr != NULL_PTR)
	{
		TCNT1 = timer1_ovf_initial_value; /*in case of overflow mode initialize the timer with value specified from user each time*/
		(*g_Timer1CallBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_Timer1CallBackPtr != NULL_PTR)
	{
		(*g_Timer1CallBackPtr)();
	}
}

/*****************************************************************************************
                                      timer2 ISRs
*****************************************************************************************/
ISR(TIMER2_OVF_vect){

	if(g_Timer2CallBackPtr != NULL_PTR)
	{
		TCNT2 = timer2_ovf_initial_value; /*in case of overflow mode initialize the timer with value specified from user each time*/
		(*g_Timer2CallBackPtr)();
	}
}

ISR(TIMER2_COMP_vect){
	if(g_Timer2CallBackPtr!= NULL_PTR)
	{
		(*g_Timer2CallBackPtr)();
	}
}

/*****************************************************************************************
                                     functions Definitions
*****************************************************************************************/

/*@description: function to initialize the timer driver
 * param1: Configuration pointer
 * -set which timer to operate
 * -set initial value of timer
 * -set the mode of the timer overflow or compare
 * -set the clock source clock and prescaler
 * -if in compare mode set compare value
 * return: none
 * */
void Timer_init(const Timer_ConfigType * Config_Ptr){
	/*initialize timer0*/
	if(Config_Ptr ->timer_id == TIMER0_ID){
		SET_BIT(TCCR0,FOC0); /*this bit is set when we operate in non-PWM*/
		/*save initial value in case of overflow mode to start count from it*/
		timer0_ovf_initial_value = Config_Ptr->initial_value;
		TCNT0 = Config_Ptr->initial_value; /*set timer initial value*/
		TCCR0 = (TCCR0 & 0xB7) | (((Config_Ptr->mode)<<3)&0x08); /*set timer mode compare or overflow*/
		TCCR0 = (TCCR0 & 0xF8) | ((Config_Ptr->clock)&0x07); /*set timer source clock and prescaler*/
		OCR0 = Config_Ptr->compare_value; /*set compare value*/

		if(Config_Ptr->mode == NORMAL){
			SET_BIT(TIMSK,TOIE0); /*enable interrupt for timer0 in overflow mode*/
		}
		else if(Config_Ptr->mode == COMPARE){
			SET_BIT(TIMSK,OCIE0); /*enable interrupt for timer0 in compare mode*/
		}
	}

	/*initialize timer1*/
	else if(Config_Ptr->timer_id == TIMER1_ID){
		SET_BIT(TCCR1A,FOC1A);/*this bit is set when we operate in non-PWM*/
		/*save initial value in case of overflow mode to start count from it*/
		timer1_ovf_initial_value = Config_Ptr->initial_value;
		TCNT1 = Config_Ptr->initial_value;/*set timer initial value*/
		TCCR1B = (TCCR1B & 0xE7) | (((Config_Ptr->mode)<<3)&0x08);/*set timer mode compare or overflow*/
		TCCR1B = (TCCR1B & 0xF8) | ((Config_Ptr->clock)&0x07);/*set timer source clock and prescaler*/
		OCR1A = Config_Ptr->compare_value;/*set compare value*/

		if(Config_Ptr->mode == NORMAL){
			SET_BIT(TIMSK,TOIE1); /*enable interrupt for timer1 in overflow mode*/
		}
		else if(Config_Ptr->mode == COMPARE){
			SET_BIT(TIMSK,OCIE1A); /*enable interrupt for timer1 in compare mode*/
		}
	}
	/*initialize timer2*/
	else if(Config_Ptr ->timer_id == TIMER2_ID){

		SET_BIT(TCCR2,FOC2);/*this bit is set when we operate in non-PWM*/
		/*save initial value in case of overflow mode to start count from it*/
		timer2_ovf_initial_value = Config_Ptr->initial_value;
		TCNT2 = Config_Ptr->initial_value;/*set timer initial value*/
		TCCR2 = (TCCR2 & 0xB7) | (((Config_Ptr->mode)<<3)&0x08);/*set timer mode compare or overflow*/
		TCCR2 = (TCCR2 & 0xF8) | ((Config_Ptr->clock)&0x07);/*set timer source clock and prescaler*/
		OCR2 = Config_Ptr->compare_value;/*set compare value*/

		if(Config_Ptr->mode == NORMAL){
			SET_BIT(TIMSK,TOIE2); /*enable interrupt for timer2 in overflow mode*/
		}
		else if(Config_Ptr->mode == COMPARE){
			SET_BIT(TIMSK,OCIE2);/*enable interrupt for timer2 in compare mode*/
		}
	}

	else{
		/*do nothing*/
	}

}

/*@description: function to set the call back function address of timer0
 * param1:address of the call back function
 * return: none
 * */
void Timer0_setCallBack(void(*a_ptr)(void)){
	g_Timer0CallBackPtr = a_ptr;
}

/*@description: function to set the call back function address of timer1
 * param1:address of the call back function
 * return: none
 * */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_Timer1CallBackPtr = a_ptr;
}

/*@description: function to set the call back function address of timer2
 * param1:address of the call back function
 * return: none
 * */
void Timer2_setCallBack(void(*a_ptr)(void)){
	g_Timer2CallBackPtr = a_ptr;
}

/*@description: function to disable the timer
 * param1: Timer_Id to specify which timer to stop
 * return: none
 * */
void Timer_DeInit(Timer_Id timer_id){
	/*disable timer0*/
	if(timer_id == TIMER0_ID){
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		CLEAR_BIT(TIMSK,OCIE0);
		CLEAR_BIT(TIMSK,TOIE0);
	}
	/*disable timer1*/
	else if(timer_id == TIMER1_ID){
		TCCR1A = 0;
		TCCR1B = 0;
		OCR1A = 0;
		TCNT1 = 0;
		CLEAR_BIT(TIMSK,TOIE2);
		CLEAR_BIT(TIMSK,OCIE2);

	}
	/*disable timer2*/
	else if(timer_id == TIMER2_ID){
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		CLEAR_BIT(TIMSK,OCIE2);
		CLEAR_BIT(TIMSK,TOIE2);
	}
	else{
		/*do nothing*/
	}
}


