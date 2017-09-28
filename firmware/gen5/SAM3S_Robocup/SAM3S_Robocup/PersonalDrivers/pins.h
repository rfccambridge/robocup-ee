/*
 * pins.h
 *
 * Created: 2/13/2017 2:46:43 PM
 *  Author: Liam James Mulshine
 */ 


#ifndef PINS_H_
#define PINS_H_

#include <asf.h>

#define DISCHARGE IOPORT_CREATE_PIN(PIOA,23)
#define CHARGE IOPORT_CREATE_PIN(PIOB,3)
#define CHARGE_DONE IOPORT_CREATE_PIN(PIOB,2)
#define BREN0 IOPORT_CREATE_PIN(PIOA,10)
#define DIR0 IOPORT_CREATE_PIN(PIOA,9)
#define FAULTN0 IOPORT_CREATE_PIN(PIOA,17)
#define BREN2 IOPORT_CREATE_PIN(PIOA,7)
#define DIR2 IOPORT_CREATE_PIN(PIOA,12)
#define FAULTN2 IOPORT_CREATE_PIN(PIOA,20)
#define DIR1 IOPORT_CREATE_PIN(PIOA,11)
#define BREN1 IOPORT_CREATE_PIN(PIOA,8)
#define FAULTN1 IOPORT_CREATE_PIN(PIOA,19)

void input_change_handle () 
{
	ioport_set_pin_level(DISCHARGE, true);
	uint8_t test[1] = {0};
	//!!!TODO: decode received buffer for each GPIO and perform 
	receive_packet(INTCAPA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
	receive_packet(INTCAPB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
	receive_packet(GPIOA,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
	receive_packet(GPIOB,sizeof(uint8_t),IO_EXPANDER_ADDRESS,test,sizeof(uint8_t));
}

void pin_config(void)
{
	ioport_init();
	
	//!!!TODO: Get rid of all unnecessary input/output pins due to introduction of IO-Expander
	// set pin directions
	ioport_set_pin_dir(DISCHARGE,IOPORT_DIR_OUTPUT);			// DISCHARGE - OUTPUT
	ioport_set_pin_dir(BREN0,IOPORT_DIR_OUTPUT);				// BREAK ENABLE - MOTOR 0 (BREN0) - OUTPUT
	ioport_set_pin_dir(BREN1,IOPORT_DIR_OUTPUT);				// BREAK ENABLE - MOTOR 1 (BREN1) - OUTPUT 
	ioport_set_pin_dir(BREN2,IOPORT_DIR_OUTPUT);				// BREAK ENABLE - MOTOR 2 (BREN2) - OUTPUT
	ioport_set_pin_dir(FAULTN0,IOPORT_DIR_INPUT);				// FAULT INPUT - MOTOR 0 (FAULTN0) - INPUT
	ioport_set_pin_dir(FAULTN2,IOPORT_DIR_INPUT);				// FAULT INPUT - MOTOR 2 (FAULTN2) - INPUT
	ioport_set_pin_dir(DIR0,IOPORT_DIR_OUTPUT);					// DIRECTION - MOTOR 0 (DIR0) - OUTPUT
	ioport_set_pin_dir(DIR1,IOPORT_DIR_OUTPUT);					// DIRECTION - MOTOR 1 (DIR1) - OUTPUT
	ioport_set_pin_dir(DIR2,IOPORT_DIR_OUTPUT);					// DIRECTION - MOTOR 2 (DIR2) - OUTPUT
	ioport_set_pin_dir(CHARGE,IOPORT_DIR_INPUT);				// CAP CHARGE - OUTPUT
	ioport_set_pin_dir(CHARGE_DONE,IOPORT_DIR_INPUT);			// CHARGE DONE - INPUT
	
	// set pin mode	
	ioport_set_pin_mode(FAULTN0,IOPORT_MODE_PULLUP);			// FAULTN0
	ioport_set_pin_mode(FAULTN1,IOPORT_MODE_PULLUP);			// FAULTN1
	ioport_set_pin_mode(FAULTN2,IOPORT_MODE_PULLUP);			// FAULTN2
	
	// set initial pin level
	ioport_set_pin_level(DISCHARGE,false);						// DISCHARGE - LOW	
	ioport_set_pin_level(BREN0,false);							// BREN0 - LOW
	ioport_set_pin_level(BREN1,false);							// BREN1 - LOW
	ioport_set_pin_level(BREN2,false);							// BREN2 - LOW
	ioport_set_pin_level(DIR0,false);							// DIR0 - LOW
	ioport_set_pin_level(DIR1,false);							// DIR1 - HIGH
	ioport_set_pin_level(DIR2,false);							// DIR2 - LOW
	ioport_set_pin_level(CHARGE,false);							// CHARGE - LOW	
	
	// enable external interrupts to interface with IO-Expander 
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_input(PIOA,PIO_PA9,PIO_INPUT);
//	pio_set_input(PIOA,PIO_PA20,PIO_INPUT);
	pio_handler_set(PIOA,ID_PIOA,PIO_PA9,PIO_IT_RISE_EDGE,input_change_handle);
//	pio_handler_set(PIOA,ID_PIOA,PIO_PA20,PIO_IT_RISE_EDGE,input_change_handle);
	pio_enable_interrupt(PIOA,PIO_PA9);
//	pio_enable_interrupt(PIOA,PIO_PA20);
	NVIC_EnableIRQ(PIOA_IRQn);
}

#endif /* PINS_H_ */