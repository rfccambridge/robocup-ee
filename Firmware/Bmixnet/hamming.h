/* hamming.h
 *
 * Defines a function for decoding and correcting data that has been 
 * encoded using a Hamming (7,4) code:
 * http://en.wikipedia.org/wiki/Hamming(7,4)
 *
 * These functions assume that the data was encoded as follows:
 *
 * 			|bit0|
 * 		  H*|bit1|   where H is the Hamming matrix.
 *			|bit2|
 *			|bit3|
 *
 * They further assume that the resulting 7-element vector is encoded in 1
 * byte as follows:
 *
 * 			|bit0|
 * 			|bit1|
 * 			 ...
 * 			|bit5|
 * 			|bit6|
 *
 * In both cases, the low-order byte is the top of the vector.
 *
 * This file also defines many useful constants for bit manipulation.
 */

#ifndef HAMMING_H
#define HAMMING_H

/* First we'll define a bunch of bit masks */
#define BIT_ZERO 0x1
#define BIT_ONE 0x2
#define BIT_TWO 0x4
#define BIT_THREE 0x8
#define BIT_FOUR 0x10
#define BIT_FIVE 0x20
#define BIT_SIX 0x40
#define BIT_SEVEN 0x80

/* 
 * unsigned char correct(unsigned char rawData) - takes a byte of rawData 
 * from the transmitter and applies the necessary Hamming corrections. 
 * Returns the corrected byte
 */
unsigned char correct(unsigned char rawData);

/*
 * unsigned char decode(unsigned char lowByte, unsigned char highByte) - 
 * takes two encoded nibbles, decodes them, and returns the orignial byte. 
 * Assumes that the bytes have ALREADY been corrected.
 */
unsigned char decode(unsigned char lowByte, unsigned char highByte);

/*
 * unsigned char correctAndDecode(unsigned char lowByte, 
 * unsigned char highByte) - takes two encoded nibbles, corrects them, 
 * decodes them, and returns the original byte.
 */
unsigned char correctAndDecode(unsigned char lowByte, 
		unsigned char highByte);

#endif

