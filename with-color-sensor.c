#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "trik_studio_utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

U32 __interpretation_started_timestamp__ = 0;
static const float pi = 3.141592653589793;

static float a;

static float i;

static float u;

static int x;

static int * y;



/* OSEK declarations */
DeclareTask(TASK_ad7e9e6b9441ee834b9c62e288aa60);

void ecrobot_device_initialize(void)
{
	srand(systick_get_ms());
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	ecrobot_init_nxtcolorsensor(NXT_PORT_S1, NXT_COLORSENSOR);
}

void ecrobot_device_terminate(void)
{
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	ecrobot_term_nxtcolorsensor(NXT_PORT_S1);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{ 
	ts_dispatch_timers();
	ecrobot_process_bg_nxtcolorsensor();
}

/* Tasks */
TASK(TASK_ad7e9e6b9441ee834b9c62e288aa60)
{
	while (true) {
		if (x == x>3 && x<1) {
			while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_BLUE) {
				wait(4);
			}
			ecrobot_sound_tone(1000, 100, 50);
			
			wait(1000);
			
		} else if (x == x>3 && x<5) {
			while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_YELLOW) {
				wait(4);
			}
			display_goto_xy(1, 1);
			display_string("y");
			display_update();
		} else if (x == x>2 && x<4) {
			while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_GREEN) {
				wait(4);
			}
			while (!(nxt_motor_get_count(NXT_PORT_B) > 500)) {
				wait(3);
			}
			nxt_motor_set_speed(NXT_PORT_B, (int)(50 + i), 0);
			nxt_motor_set_speed(NXT_PORT_C, (int)(50 + i), 0);
			
		} else if (x == x<6 && x>4) {
			while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_RED) {
				wait(4);
			}
			nxt_motor_set_speed(NXT_PORT_B, 0, 1);
			nxt_motor_set_speed(NXT_PORT_C, 0, 1);
			
			wait(2000);
			
		} else {
			while (true) {
				nxt_motor_set_speed(NXT_PORT_B, (int)(60 + i), 0);
				nxt_motor_set_speed(NXT_PORT_C, (int)(60 + i), 0);
				
				while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_BLACK) {
					wait(4);
				}
				
			}
			ecrobot_sound_tone(1000, 100, 50);
			
			nxt_motor_set_count(NXT_PORT_B, 0);
			nxt_motor_set_count(NXT_PORT_C, 0);
			
			a = u + 1;
			while (true) {
				a = 0 + rand() / (15 - 0 + 1);
				
				if (a > 16) {
					display_goto_xy(10, 10);
					display_string("empty");
					display_update();
					wait(5000);
					
					display_clear(1);
					
				}
			}
			break;
		}
		
		
	}
}

/* Main task */
TASK(TASK_MAIN)
{
	__interpretation_started_timestamp__ = systick_get_ms();
	
	x = ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1);
	y = ;
	u = 20 / pi;
	i = u - 40;
	ActivateTask(TASK_ad7e9e6b9441ee834b9c62e288aa60);
	while (true) {
		nxt_motor_set_speed(NXT_PORT_B, (int)(60 + i), 0);
		nxt_motor_set_speed(NXT_PORT_C, (int)(60 + i), 0);
		
		while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_BLACK) {
			wait(4);
		}
		
		while (x < 2 && x > 0) {
			ecrobot_sound_tone(1000, 100, 50);
			
			nxt_motor_set_count(NXT_PORT_B, 0);
			nxt_motor_set_count(NXT_PORT_C, 0);
			
			a = u + 1;
			while (true) {
				a = 0 + rand() / (15 - 0 + 1);
				
				if (a > 16) {
					display_goto_xy(10, 10);
					display_string("empty");
					display_update();
					wait(5000);
					
					display_clear(1);
					
					for (int __iter__1 = 0; __iter__1 < 16; ++__iter__1) {
						TerminateTask();
						
						break;
					}
				}
			}
			break;
		}
	}
}
