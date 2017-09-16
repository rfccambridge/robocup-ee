/*
 * io_expander.c
 *
 * Created: 8/17/2017 6:14:18 PM
 *  Author: Liam James Mulshine
 */ 
/******************************
 * Includes
 ******************************/
#include <asf.h>

#include "io_expander.h"
#include "twi_driver.h"
#include "board.h"

/******************************
 * Data Types
 ******************************/

/******************************
 * Constant and Macro Definitions
 ******************************/
#define IO_EXPANDER_ADDRESS (0x40 >> 1)
// Register Numbers - Assume IOCON.BANK = 0
#define IODIRA 0x00			/* Direction Register, port A*/
#define IODIRB 0x01			/* Direction Register, port B */
#define IPOLA 0x02			/* Input Polarity Port Register, port A  */
#define IPOLB 0x03			/* Input Polarity Port Register, port B */
#define GPINTENA 0x04		/* Interrupt on Change Enable Register, port A */
#define GPINTENB 0x05		/* Interrupt on Change Enable Register, port B */
#define DEFVALA 0x6			/* Default Values Register for Interrupt on Change, port A */
#define DEFVALB 0x0			/* Default Values Register for Interrupt on Change, port B */
#define INTCONA 0x08		/* Interrupt on Change Control Register, port A */
#define INTCONB 0x09		/* Interrupt on Change Control Register, port B */
#define IOCONA 0x0a			/* I/O Expander Configuration Register, port A */
#define IOCONB 0x0b			/* I/O Expander Configuration Register, port A */
#define GPPUA 0x0c			/* GPIO Pull-up resistor Register, port A */
#define GPPUB 0x0d			/* GPIO Pull-up resistor Register, port B */
#define INTFA 0x0e			/* Interrupt Flag Register, port A */
#define INTFB 0x0f			/* Interrupt Flag Register, port B */
#define INTCAPA 0x10		/* Interrupt Captured Value for port A Register */
#define INTCAPB 0x11		/* Interrupt Captured Value for port A Register */
#define GPIOA 0x12			/* GPIO Port Register, port A */
#define GPIOB 0x13			/* GPIO Port Register, port B */
#define OLATA 0x14			/* Output Latch Register, port A */
#define OLATB 0x15			/* Output Latch Register, port B */

typedef struct
{
	// control bits for IO expander - see data sheet for info on how to change them to meet your needs
	uint8_t io_dir_a; // set direction of io pins on port A
	uint8_t io_dir_b;	          // set direction of io pins on port B
	uint8_t ipol_a;	              // polarity of gpio bit not inverted
	uint8_t ipol_b;		              // polarity of gpio bit not inverted
	uint8_t gpinten_a;	      // enable/disable interrupts for specific pins
	uint8_t gpinten_b;	      // enable/disable interrupts for specific pins
	uint8_t defval_a;         // set default value of all pins to 0 on port a
	uint8_t defval_b;	              // set default value of all pins to 0 on port b
	uint8_t intcon_a;             // set interrupt to trigger whenever pin-value changes, port a
	uint8_t intcon_b;              // set interrupt to trigger whenever pin-value changes, port b
	uint8_t iocon_a;	          // see data sheet of MCP23017 for understanding of this register and the values set here
	uint8_t iocon_b;	          // see data sheet of MCP23017 for understanding of this register and the values set here
	uint8_t gppu_a;            // pull up register (1 = enable pull-up, 0 disable pull-up)
	uint8_t gppu_b;		              // pull up register (1 = enable pull-up, 0 disable pull-up)
	uint8_t gpio_a;	      // assign pins as either inputs or outputs
	uint8_t gpio_b; 		      // assign pins as either inputs or outputs
	
}io_expander_options;

/******************************
 * Static Data Declarations
 ******************************/
static const io_expander_options options = { .io_dir_a = 0b01010001U, .io_dir_b = 0b10001000U, .ipol_a = 0U, .ipol_b = 0U, .gpinten_a = 0b01010001U, .gpinten_b = 0b10001000U, .defval_a = 0U, .defval_b = 0U, .intcon_a = 0U, .intcon_b = 0U, .iocon_a = 0b01001010U, .iocon_b = 0b01001010U, .gppu_a = 0U, .gppu_b = 0U, .gpio_a = 0b10101110U, .gpio_b = 0b01110111U};

/******************************
 * Private Function Prototypes
 ******************************/
/******************************
 * Public Function Bodies
 ******************************/

void io_expander_init (void)
{	
	// initialization packets - TODO: configure IO chip for inputs and M3 for external interrupts
	send_packet(IODIRA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.io_dir_a,sizeof(uint8_t));
	send_packet(IODIRB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.io_dir_b,sizeof(uint8_t));
	send_packet(INTCONA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.intcon_a,sizeof(uint8_t));
	send_packet(INTCONB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.intcon_b,sizeof(uint8_t));
	send_packet(GPINTENA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.gpinten_a,sizeof(uint8_t));
	send_packet(GPINTENB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.gpinten_b,sizeof(uint8_t));
	send_packet(IOCONA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.iocon_a,sizeof(uint8_t));
	send_packet(IOCONB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.iocon_b,sizeof(uint8_t));
	send_packet(GPIOA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.gpio_a,sizeof(uint8_t));
	send_packet(GPIOB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,&options.gpio_b,sizeof(uint8_t));
	
	
	// enable external interrupts to interface with IO-Expander
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_input(PIOA,PIO_PA9,PIO_INPUT);
	//	pio_set_input(PIOA,PIO_PA20,PIO_INPUT);
	pio_handler_set(PIOA,ID_PIOA,PIO_PA9,PIO_IT_RISE_EDGE,io_expander_interrupt_handle);
	//	pio_handler_set(PIOA,ID_PIOA,PIO_PA20,PIO_IT_RISE_EDGE,io_expander_interrupt_handle);
	pio_enable_interrupt(PIOA,PIO_PA9);
	//	pio_enable_interrupt(PIOA,PIO_PA20);
	NVIC_EnableIRQ(PIOA_IRQn);
}

void io_expander_interrupt_handle(uint32_t a, uint32_t b)
{
	uint8_t test[1] = {0}; //!!!TODO: decode received buffer for each GPIO and perform
		
	receive_packet(INTCAPA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
	receive_packet(INTCAPB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
	receive_packet(GPIOA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
	receive_packet(GPIOB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
}


/******************************
 * Private Function Bodies
 ******************************/