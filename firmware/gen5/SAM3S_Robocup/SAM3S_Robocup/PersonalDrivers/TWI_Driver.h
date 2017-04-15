/*
 * TWI_Driver.h
 *
 * Created: 2/22/2017 9:12:46 PM
 *  Author: Liam James Mulshine
 */ 



#ifndef TWI_DRIVER_H_
#define TWI_DRIVER_H_

#include <asf.h>
#include "board.h"

#define TWCK IOPORT_CREATE_PIN(PIOA,4)
#define TWD IOPORT_CREATE_PIN(PIOA,3)

#define ARDUINO_ADDR 0x08
#define IO_EXPANDER_ADDRESS (0x40 >> 1)

// Assuming IOCON.BANK = 0
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

// configures twi module for use with io_expander and communications board
void configure_twi (void); 

// send initialization data to io_expander 
void configure_io_expander (void);

// sends a packet of information to any device given its address, and internal address (if applicable)
void send_packet(uint8_t internal_addr, uint8_t internal_addr_sz, uint8_t device_addr, uint8_t *buf, uint8_t buf_sz);

#endif /* TWI_DRIVER_H_ */