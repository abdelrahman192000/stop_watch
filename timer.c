/*
 * timer.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdelrahman Adel Mahmoud
 */


#include "timer.h"
#include "avr/io.h"
#include <avr/interrupt.h>
#include <util/delay.h>


void timer_int (timer_config_t *timer_config)
{



	TCNT0 |= START_FROM_ZERO ;

	switch (timer_config->timer_num)
	{
	case TIMER_0:

		TIMSK |= timer_config->timer_enable_interrupt;

		if (timer_config->timer_mode==NORMAL_MODE)
		{
			//TCCR0 |= 128; //F0C0 BIT = 1
		}
		else if (timer_config->timer_mode == CTC_MODE)
		{
			//TCCR0 |= 128; //F0C0 BIT = 1
			TCCR0 |= CTC_MODE;
			OCR0 = timer_config->top;
			switch (timer_config->timer_0_ctc_non_pwm_mode)
			{
			case NORMAL_PORT_OC0_CTC_DISCONNECT :
				TCCR0 |= NORMAL_PORT_OC0_CTC_DISCONNECT;
				break;
			case TOGGLE_OC0 :
				DDRB |= (1<<3) ; // OC0 OUTPUT
				TCCR0 |= TOGGLE_OC0;
				break;
			case CLEAR_OC0 :
				DDRB |= (1<<3) ; // OC0 OUTPUT
				TCCR0 |= CLEAR_OC0;
				break;
			case SET_OC0 :
				DDRB |= (1<<3) ; // OC0 OUTPUT
				TCCR0 |= SET_OC0;
				break;

			}
			TCCR0 |= timer_config->timer_prescaler;





		}

		else if (timer_config->timer_mode == FAST_PWM_MODE)
		{
			OCR0  |= timer_config->set_duty_cycle;
			DDRB  |= (1<<PB3); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC
			TCCR0 |= FAST_PWM_MODE;
			TCCR0 |= timer_config->timer_0_fast_pwm_mode;
			TCCR0 |= timer_config->timer_prescaler;


		}
		else
		{
			// DO NO THING
		}

		TCCR0 |=timer_config->timer_prescaler;


/*
		break;
	case TIMER_1:

		break;
	case TIMER_2:

		break;
		*/

	}


}

void timer_active (timer_config_t *timer_config)
{
	TIMSK |= timer_config->timer_enable_interrupt;



}
void timer_disavtive (timer_config_t *timer_config)
{
	TIMSK &= 0XF2;




}
