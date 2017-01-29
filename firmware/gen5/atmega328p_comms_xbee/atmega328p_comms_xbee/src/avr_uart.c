#include "avr_uart.h"
#include <avr/io.h>

#define BAUD 57600
#define UBRR_VAL ((F_CPU / (16UL * BAUD)) - 1)
#define _BV(bit) (1 << (bit))

// Initialize UART
void avr_uart_init(void) {
	// Set baud
	UBRR0H = (unsigned char) (UBRR_VAL >> 8);
	UBRR0L = (unsigned char) UBRR_VAL;
	// Enable receiver and transmitter
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
	// 8 bit characters
	UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);
}

// Send on char (blocking)
void avr_uart_send_byte(uint8_t tx_byte) {
	// Wait to transmit
	while((UCSR0A & _BV(UDRE0)) == 0);
	// Put data in buffer
	UDR0 = tx_byte;
}

// Receive one char if available, -1 else
int16_t avr_uart_receive_byte(void) {
	if ((UCSR0A & _BV(RXC0)) != 0)
	return UDR0;
	else
	return -1;
}