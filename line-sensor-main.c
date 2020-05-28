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

static int x;



void ecrobot_device_initialize(void)
{
	srand(systick_get_ms());
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	ecrobot_init_sonar_sensor(NXT_PORT_S1);
	/* Enables fetching data from sonar */
	ecrobot_get_sonar_sensor(NXT_PORT_S1);
}

void ecrobot_device_terminate(void)
{
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	ecrobot_term_sonar_sensor(NXT_PORT_S1);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{ 
	ts_dispatch_timers();

}

/* Main task */
TASK(TASK_MAIN)
{
	__interpretation_started_timestamp__ = systick_get_ms();
	
	label_d7facc28308486f9f6fd44bb7bed118:
	x = ecrobot_get_sonar_sensor(NXT_PORT_S1);
	label_e571d27f94d4d2b9f768d0b21c29b11:
	while (x < 5) {
		goto label_c74f363c8e274042880acc1dcc2cc52d;
	}
	goto label_edb0f436999244d0a1745537a356e6e9;
	label_c74f363c8e274042880acc1dcc2cc52d:
	ecrobot_sound_tone(1000, 100, 50);
	
	label_c03f869cf4a09b8d3a1a439b5f485:
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	
	label_e2f5599b12344e0cac453c3ff2cd6963:
	wait(1000);
	
	label_d1a2171f667041cb8441efbfac8b5dec:
	if ((bool)(x = 6)) {
		goto label_e571d27f94d4d2b9f768d0b21c29b11;
	} else {
		goto label_e3815d2cabe4175875558b5aa1751d2;
	}
	label_edb0f436999244d0a1745537a356e6e9:
	nxt_motor_set_speed(NXT_PORT_B, 50, 0);
	nxt_motor_set_speed(NXT_PORT_C, 50, 0);
	
	label_ca03bc7b6e4969bf066cd70982b4e1:
	wait(1000);
	
	goto label_d7facc28308486f9f6fd44bb7bed118;
	label_e3815d2cabe4175875558b5aa1751d2:
	nxt_motor_set_speed(NXT_PORT_B, -(100), 0);
	nxt_motor_set_speed(NXT_PORT_C, -(100), 0);
	
	label_d64be63c2b5347eabeb41b3da6ba9430:
	wait(1000);
	
	label_c3415f9d03f405587457e67462fe66b:
	nxt_motor_set_speed(NXT_PORT_B, -(100), 0);
	
	label_a993d2972ed4b1aa24c9e5b9c4c2ae6:
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	
	label_e50a233bb04457a7083fa0accb2828:
	wait(1500);
	
	goto label_d7facc28308486f9f6fd44bb7bed118;
}
