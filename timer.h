/*
 * timer.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Abdelrahman Adel Mahmoud
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

#define START_FROM_ZERO 0


typedef enum
{
	TIMER_0,
	TIMER_1,
	TIMER_2

}timer_num_t;

/*typedef enum
{
	COMPARE_MODE,
	OVERFLOW_MODE

}timer_mode;*/

typedef enum
{
	NORMAL_MODE,
	PWM_PHASE_CORRECT_MODE=64,
	CTC_MODE=8,
	FAST_PWM_MODE=72

}timer_mode_t;

typedef enum
{
	NO_CLOCK_SOURCE ,
	NO_PRESCALER,
	CLK_8_PRESCALER,
	CLK_64_PRESCALER,
	CLK_256_PRESCALER,
	CLK_1024_PRESCALER

}timer_prescaler_t;

typedef enum
{
	TIMER_0_COMPARE_INTERRUPT=2,
	TIMER_0_OVERFLOW_INTERRUPT=1

}timer_enable_interrupt_t;
typedef enum
{
	NORMAL_PORT_OC0_CTC_DISCONNECT,
	TOGGLE_OC0=16,
	CLEAR_OC0=32,
	SET_OC0=48

}timer_0_ctc_non_pwm_mode_t;

typedef enum
{
	NORMAL_PORT_OC0_FPWM_DISCONNECT,
	CLEAR_OC0_NON_INVERTING_MODE =32,
	SET_OC0_INVERTED_MODE =48

}timer_0_fast_pwm_mode_t;

typedef enum
{
	DUTY_CYCLE_0=0,
	DUTY_CYCLE_25=64,
	DUTY_CYCLE_50=128,
	DUTY_CYCLE_75=192,
	DUTY_CYCLE_100=256
}set_duty_cycle_t;

typedef struct
{
	timer_num_t timer_num;
	timer_mode_t timer_mode;
	timer_prescaler_t timer_prescaler;
	timer_enable_interrupt_t timer_enable_interrupt;
	timer_0_ctc_non_pwm_mode_t timer_0_ctc_non_pwm_mode;
	set_duty_cycle_t set_duty_cycle;
	timer_0_fast_pwm_mode_t timer_0_fast_pwm_mode;
	uint8 top;

}timer_config_t;

void timer_int (timer_config_t *timer_config);
void timer_active (timer_config_t *timer_config);
void timer_disavtive (timer_config_t *timer_config);






#endif /* TIMER_H_ */
