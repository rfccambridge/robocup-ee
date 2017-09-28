/*
 * TWI_Driver.c
 *
 * Created: 2/22/2017 9:13:07 PM
 *  Author: Liam James Mulshine
 */ 

#include <TWI_Driver.h>

void configure_twi(void) 
{
	// configure pins for TWI communication
	pio_configure_pin(TWCK, PIO_TYPE_PIO_PERIPH_A | PIO_DEFAULT);
	pio_configure_pin(TWD, PIO_TYPE_PIO_PERIPH_A | PIO_DEFAULT);
	
	// enable clock for TWI peripheral
	pmc_enable_periph_clk(ID_TWI0);

	// set twi options struct
	twi_options_t options = 
	{
		.master_clk = sysclk_get_cpu_hz(),
		.speed = 100000,
		.smbus = 0,
		.chip = IO_EXPANDER_ADDRESS
	};
	
	// initialize twi with options
	twi_master_init(TWI0, &options);
	
}

void configure_io_expander (void) 
{
	// control bits for IO expander - see data sheet for info on how to change them to meet your needs
	uint8_t io_dir_a[1] = {0b01010001};	// set direction of io pins on port A
	uint8_t io_dir_b[1] = {0b10001000};	// set direction of io pins on port B
	uint8_t ipol_a[1] = {0x00};		// polarity of gpio bit not inverted
	uint8_t ipol_b[1] = {0x00};		// polarity of gpio bit not inverted
	uint8_t gpinten_a[1] = {0b01010001};	// interrupts disabled
	uint8_t gpinten_b[1] = {0b10001000};	// interrupts disabled
	uint8_t defval_a[1] = {0x00};	// set default value of all pins to 0 port a (shouldn't matter too much for our application)
	uint8_t defval_b[1] = {0x00};	// set default value of all pins to 0 port b (shouldn't matter too much for our application)
	uint8_t intcon_a[1] = {0x00};	// set interrupt to trigger whenever pin-value changes, port a
	uint8_t intcon_b[1] = {0x00};	// set interrupt to trigger whenever pin-value changes, port b
	uint8_t iocon_a[1] = {0b01001010};	// see data sheet of MCP23017 for understanding of this register and the values set here
	uint8_t iocon_b[1] = {0b01001010};	// see data sheet of MCP23017 for understanding of this register and the values set here
	uint8_t gppu_a[1] = {0x00};		// pull up register (1 = enable pull-up, 0 disable pull-up)
	uint8_t gppu_b[1] = {0x00};		// pull up register (1 = enable pull-up, 0 disable pull-up)
	uint8_t gpio_a[1] = {0b10101110};		// input/output register
	uint8_t gpio_b[1] = {0b01110111};		// input/output register
		
	// initialization packets - TODO: configure IO chip for inputs and M3 for external interrupts
	send_packet(IODIRA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,io_dir_a,sizeof(uint8_t));
	send_packet(IODIRB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,io_dir_b,sizeof(uint8_t));
	send_packet(INTCONA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,intcon_a,sizeof(uint8_t));
	send_packet(INTCONB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,intcon_b,sizeof(uint8_t));
	send_packet(GPINTENA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,gpinten_a,sizeof(uint8_t));
	send_packet(GPINTENB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,gpinten_b,sizeof(uint8_t));
	send_packet(IOCONA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,iocon_a,sizeof(uint8_t));
	send_packet(IOCONB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,iocon_b,sizeof(uint8_t));
	send_packet(GPIOA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,gpio_a,sizeof(uint8_t));
	send_packet(GPIOB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,gpio_b,sizeof(uint8_t));
	
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


