/**
 * Main File for RFC Cambridge Firmware
 *
 * Authors: Liam Mulshine, etc.
 */

#include <asf.h>
#include "Custom/pwm_driver.h"


int main (void)
{
	/* Initialize the system clock and board*/
	sysclk_init();
	board_init();
	
	pwm_test();

	/* Insert application code here, after the board has been initialized. */
}
