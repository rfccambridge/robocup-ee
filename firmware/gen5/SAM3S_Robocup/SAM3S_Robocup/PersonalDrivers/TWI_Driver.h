/*
 * TWI_Driver.h
 *
 * Created: 2/22/2017 9:12:46 PM
 *  Author: Liam James Mulshine
 */ 



#ifndef TWI_DRIVER_H_
#define TWI_DRIVER_H_

/******************************
 * Includes
 ******************************/
#include <asf.h>

#include "board.h"

/******************************
 * Constant and Macro Definitions
 ******************************/

#define TWCK IOPORT_CREATE_PIN(PIOA,4)
#define TWD IOPORT_CREATE_PIN(PIOA,3)
#define ARDUINO_ADDR 0x08

/******************************
 * Public Function Prototypes
 ******************************/
// configures twi module for use with io_expander and communications board
void configure_twi (void); 

// sends a packet of information to any device given its address, and internal address (if applicable)
void send_packet(const uint8_t internal_addr, const uint8_t internal_addr_sz, const uint8_t device_addr, const uint8_t *buf, const uint8_t buf_sz);

// receives a packet of information from a slave device given its address, and internal address (if applicable) 
void receive_packet(const uint8_t internal_addr, const uint8_t internal_addr_sz, const uint8_t device_addr, const uint8_t *buf, const uint8_t buf_sz);

#endif /* TWI_DRIVER_H_ */