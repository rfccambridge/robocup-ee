/*
 * TWI_Driver.c
 *
 * Created: 2/22/2017 9:13:07 PM
 *  Author: Liam James Mulshine
 */ 
/******************************
 * Includes
 ******************************/
#include <twi_driver.h>

/******************************
 * Data Types
 ******************************/

/******************************
 * Constant and Macro Definitions
 ******************************/

/******************************
 * Static Data Declarations
 ******************************/

/******************************
 * Private Function Prototypes
 ******************************/


/******************************
 * Public Function Bodies
 ******************************/
/******************************
 * Private Function Bodies
 ******************************/

void configure_twi(void) 
{
	pio_configure_pin(TWCK, PIO_TYPE_PIO_PERIPH_A | PIO_DEFAULT); // configure TWI clock pin
	pio_configure_pin(TWD, PIO_TYPE_PIO_PERIPH_A | PIO_DEFAULT);  // configure TWI data pin

	pmc_enable_periph_clk(ID_TWI0);	// enable clock for TWI peripheral through power management controller (pmc)

	// twi options struct
	twi_options_t options = 
	{
		.master_clk = sysclk_get_cpu_hz(),    // 
		.speed = 100000,                      // 
		.smbus = 0,                           //
		.chip = IO_EXPANDER_ADDRESS           // default address for TWI comms usage
	};
	
	// initialize twi with options
	twi_master_init(TWI0, &options);
	
}

void send_packet(uint8_t internal_addr, uint8_t internal_addr_sz, uint8_t device_addr, uint8_t *buf, uint8_t buf_sz)
{
	twi_packet_t tx =
	{
		.chip = device_addr,
		.addr = internal_addr,
		.addr_length = internal_addr_sz,
		.buffer = buf,
		.length = buf_sz
	};
	
	twi_master_write(TWI0,&tx);
}

void receive_packet(uint8_t internal_addr, uint8_t internal_addr_sz, uint8_t device_addr, uint8_t *buf, uint8_t buf_sz)
{
	twi_packet_t rx =
	{
		.chip = device_addr,
		.addr = internal_addr,
		.addr_length = internal_addr_sz,
		.buffer = buf,
		.length = buf_sz
	};
	
	twi_master_read(TWI0,&rx);
}


