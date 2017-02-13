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

void pin_config(void)
{
	ioport_init();
		
	// set pin directions
	ioport_set_pin_dir(DISCHARGE,IOPORT_DIR_OUTPUT);			// DISCHARGE - OUTPUT
	ioport_set_pin_dir(BREN0,IOPORT_DIR_OUTPUT);				// BREAK ENABLE - MOTOR 0 (BREN0) - OUTPUT 
	ioport_set_pin_dir(BREN2,IOPORT_DIR_OUTPUT);				// BREAK ENABLE - MOTOR 2 (BREN2) - OUTPUT
	ioport_set_pin_dir(FAULTN0,IOPORT_DIR_INPUT);				// FAULT INPUT - MOTOR 0 (FAULTN0) - INPUT
	ioport_set_pin_dir(FAULTN2,IOPORT_DIR_INPUT);				// FAULT INPUT - MOTOR 2 (FAULTN2) - INPUT
	ioport_set_pin_dir(DIR0,IOPORT_DIR_OUTPUT);					// DIRECTION - MOTOR 0 (DIR0) - OUTPUT
	ioport_set_pin_dir(DIR2,IOPORT_DIR_OUTPUT);					// DIRECTION - MOTOR 2 (DIR2) - OUTPUT
	ioport_set_pin_dir(CHARGE,IOPORT_DIR_INPUT);				// CAP CHARGE - OUTPUT
	ioport_set_pin_dir(CHARGE_DONE,IOPORT_DIR_INPUT);			// CHARGE DONE - INPUT
	
	// set pin mode	
	ioport_set_pin_mode(FAULTN0,IOPORT_MODE_PULLUP);			// FAULTN0
	ioport_set_pin_mode(FAULTN2,IOPORT_MODE_PULLUP);			// FAULTN2
	
	// set initial pin level
	ioport_set_pin_level(DISCHARGE,false);						// DISCHARGE - LOW	
	ioport_set_pin_level(BREN0,false);							// BREN0 - LOW
	ioport_set_pin_level(BREN2,false);							// BREN2 - LOW
	ioport_set_pin_level(DIR0,false);							// DIR0 - LOW
	ioport_set_pin_level(DIR2,false);							// DIR2 - LOW
	ioport_set_pin_level(CHARGE,false);							// CHARGE - LOW		
}

#endif /* PINS_H_ */