#include <RobocupDrivers.h>
#include <asf.h>


void test_dac(void) {
	sysclk_enable_peripheral_clock(ID_DACC);
	
	dacc_reset(DACC);
}