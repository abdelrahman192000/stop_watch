/*
 * main.c
 *
 *  Created on: Jul 31, 2023
 *      Author: Abdelrahman Adel Mahmoud
 */



#include "application.h"

uint8 g_tick=0,g_num=0,number=0,flag=0;

uint8 seconds1=0,seconds2=0,min1=0,min2=0,hour1=0,hour2=0;


#define NUMBER_OF_OVERFLOWS_PER_SECOND 64 // every one second

timer_config_t timer_0 =
{
		.timer_num = TIMER_0,
		.timer_mode = NORMAL_MODE,
		.timer_enable_interrupt =TIMER_0_OVERFLOW_INTERRUPT,
		.timer_prescaler = CLK_1024_PRESCALER

};

interrupt_config_t interrupt_0 =
{
		.interrupts_num = INT_0,
		._0_1_interrupt_sense_control = _0_RISING_EDGE
};

interrupt_config_t interrupt_1 =
{
		.interrupts_num = INT_1,
		._0_1_interrupt_sense_control = _1_RISING_EDGE
};

pin_config_t timer_status_led_activate  =
{
		.port = PORTD_INDEX,
		.pin = PIN0,
		.direction = PIN_OUTPUT_,
		.logic =  GPIO_LOW // start value is zero  led is off

};



ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		// check if overflow occurs at the 7-segment as its maximum count is 9
		PORTD = PORTD ^ (1<<0);
		flag = 1;
		g_tick=0; // reset the ticks counter
	}
}
ISR(INT0_vect)
{
	GPIO_writePin(PORTD_INDEX,PIN7,GPIO_HIGH);
	timer_disavtive(&timer_0);

}
ISR(INT1_vect)
{
	// SET TIMER TO ZEROS
	timer_active(&timer_0);
	//seconds1=0,seconds2=0,min1=0,min2=0,hour1=0,hour2=0;
}
int main (void)
{
	TCCR0 |= (1<<7);
	timer_int(&timer_0);
	Interrupt_Initialize(&interrupt_0);
	Interrupt_Initialize(&interrupt_1);

	GPIO_Configuration_Init(&timer_status_led_activate);

	GPIO_setupPinDirection(PORTD_INDEX,PIN7,PIN_OUTPUT_);
	GPIO_writePin(PORTD_INDEX,PIN7,GPIO_LOW);

	GPIO_setupPinDirection(PORTD_INDEX,PIN6,PIN_OUTPUT_);
	GPIO_writePin(PORTD_INDEX,PIN6,GPIO_LOW);

	GPIO_setupPinDirection(PORTB_INDEX,PIN7,PIN_INPUT_);

	GPIO_setupPinDirection(PORTD_INDEX,PIN1,PIN_OUTPUT_);

	DDRA = 0XFF;
	DDRB = (DDRB & 0XF0) | (0X0F);// 7 SEGMENT ACTIVE


	while (1)
	{
		if  (PINB & (1<<7) )
		{
			seconds1=0,seconds2=0,min1=0,min2=0,hour1=0,hour2=0;
		}

			if (flag ==1 )
			{

				seconds1++;
				if (seconds1==10)
				{
					seconds2++;
					seconds1=0;
				}
				if (seconds1==0 && seconds2==6)
				{
					seconds2=0;
					min1++;
				}


				if (min1==10 )
				{
					min2++;
					min1=0;

				}

				if(min1==0 &&min2==6)
				{
					min2=0;
					hour1++;

				}
				if (hour1==10)
				{

					hour2++;
					hour1=0;
				}
				flag=0;


			}
		PORTA =(1<<0);

		PORTB=(PORTB & 0xF0)|(hour2);
		_delay_ms(2);


		PORTA =(1<<1);
		PORTB =(PORTB & 0xF0)|(hour1);
		_delay_ms(2);


		PORTA =(1<<2);
		PORTB = (PORTB & 0xF0)|(min2);
		_delay_ms(2);


		PORTA =(1<<3);
		PORTB = (PORTB & 0xF0)|(min1);
		_delay_ms(2);


		PORTA =(1<<4);
		PORTB = (PORTB & 0xF0)|(seconds2);
		_delay_ms(2);


		PORTA =(1<<5);
		PORTB = (PORTB & 0xF0)|(seconds1);
		_delay_ms(2);




	}


}
