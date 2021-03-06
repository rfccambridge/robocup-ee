#include <RobocupDrivers.h>
#include <asf.h>


void test_dac(void) {
	sysclk_enable_peripheral_clock(ID_DACC);
	
	dacc_reset(DACC);
	// dacc_enable(DACC);
	
	uint32_t refresh = 1; // sets refresh period: how often the DAC implements a conversion; Period = 1024 * refresh/(DAC clock freq)
	uint32_t maxs = 0; // max speed mode off
	uint32_t startup = 8; // startup time, 8 -> 512 DAC clock periods
	uint32_t dac_channel_0 = 0; 
	
	uint32_t test_val = 0xFFFF; // test value
	
	dacc_set_timing(DACC,refresh,maxs,startup);
	dacc_write_conversion_data(DACC,0x000);
	
	dacc_disable_trigger(DACC); // enable free-running mode
	dacc_set_transfer_mode(DACC,0);
	
	dacc_set_channel_selection(DACC,dac_channel_0);
	dacc_enable_channel(DACC,dac_channel_0);
	
}

void configure_dac(void)
{
	// enables clock for dac peripheral (this also enables the dac)
	sysclk_enable_peripheral_clock(ID_DACC);
	
	// reset dac to start	
	dacc_reset(DACC);
		
	uint32_t refresh = 1; // sets refresh period: how often the DAC implements a conversion; Period = 1024 * refresh/(DAC clock freq)
	uint32_t maxs = 0; // max speed mode off
	uint32_t startup = 8; // startup time, 8 -> 512 DAC clock periods
	uint32_t dac_channel_0 = 0; // channel 0
		
	uint32_t start_val = 0x000; // test value
	
	// set dac timing... you can change the constants above to change the refresh rate, etc. 	
	dacc_set_timing(DACC,refresh,maxs,startup);
	dacc_write_conversion_data(DACC,start_val);
		
	dacc_disable_trigger(DACC); // enable free-running mode
	dacc_set_transfer_mode(DACC,0); 
	
	// configure DAC on channel 0	
	dacc_set_channel_selection(DACC,dac_channel_0);
	dacc_enable_channel(DACC,dac_channel_0);
		
}

void set_dac_level(uint16_t level)
{
	// check if another conversion is ready to be performed, and if so write to the conversion data register
	uint32_t conv_ready_bit_mask = 0x8;
	
	if(dacc_get_interrupt_status(DACC) & conv_ready_bit_mask){
		dacc_write_conversion_data(DACC,level);
	}
}

