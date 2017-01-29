/* Atmega328pHardware.h
 * Hardware header for atmega328p for use with
 * ROS and rosserial package.
 *
 * Jon Cruz
 */

#ifndef _ATMEGA328P_HARDWARE_H_
#define _ATMEGA328P_HARDWARE_H_

extern "C" {
	#include <avr/interrupt.h>
	#include <avr/wdt.h>
	#include "avr_time.h"
	#include "avr_uart.h"
}

class Atmega328pHardware {
	public:
		Atmega328pHardware();
		
		// Initialize micro
		void init(void) {
			wdt_disable();
			avr_time_init();
			avr_uart_init();
			sei();
		}
		
		// Read byte from ROS connection.
		// If no data, returns -1.
		int read(void) {
			return avr_uart_receive_byte();
		}
		
		// Send array of bytes to ROS connection.
		void write(uint8_t* data, int length) {
			for (int i = 0; i < length; i++)
				avr_uart_send_byte(data[i]);
		}
		
		// Returns ms since program started
		unsigned long time(void) {
			return avr_time_now();
		}
	};
	
#endif