/* hamming.c
 *
 * Implements functions for decoding and correcting Hamming-encoded data.
 *
 * I may work on condensing the code, but this should work for now.
 */

#include "hamming.h"

/*
 * unsigned char correct(unsigned char rawData) - takes a byte of rawData 
 * and applies needed corrections, treating the low-order bit as the top of
 * the vector.
 */
unsigned char correct(unsigned char rawData)
{
	
	/* A byte to hold the results in */
	unsigned char result = 0x0;

	/* Do the first row of matrix multiplication */
	if(BIT_ZERO & rawData) {
		
		/* The if statement will evaluate to TRUE only if bit zero of 
		   rawData is 1. With that done, we can flip the third bit of the 
		   result. Now, normally in matrix multiplication, one would add -- 
		   but we would ultimately take the result modulo 2, so flipping the
		   bit every time we would add one will have the same effect */

		result = result ^ BIT_ZERO;
	}
	if(BIT_TWO & rawData)
		result = result ^ BIT_ZERO;
	if(BIT_FOUR & rawData)
		result = result ^ BIT_ZERO;
	if(BIT_SIX & rawData)
		result = result ^ BIT_ZERO;

	/* Do the next row of matrix multiplication */
	if(BIT_ONE & rawData)
		result = result ^ BIT_ONE;
	if(BIT_TWO & rawData)
		result = result ^ BIT_ONE;
	if(BIT_FIVE & rawData)
		result = result ^ BIT_ONE;
	if(BIT_SIX & rawData)
		result = result ^ BIT_ONE;

	/* Do the third row of matrix multiplication */
	if(BIT_THREE & rawData)
		result = result ^ BIT_TWO;
	if(BIT_FOUR & rawData)
		result = result ^ BIT_TWO;
	if(BIT_FIVE & rawData)
		result = result ^ BIT_TWO;
	if(BIT_SIX & rawData)
		result = result ^ BIT_TWO;

	/* Now the results of matrix multiplication should be stored in the 
	   low-order bytes of result. So if result is non-zero, we have an error
	   to correct! So we'll fix it if need be */

	switch(result) {

		case 0x1:
			rawData = rawData ^ BIT_ZERO;
			break;
	 	case 0x2:
			rawData = rawData ^ BIT_ONE;
			break;
		case 0x3:
			rawData = rawData ^ BIT_TWO;
			break;
		case 0x4:
			rawData = rawData ^ BIT_THREE;
			break;
		case 0x5:
			rawData = rawData ^ BIT_FOUR;
			break;
		case 0x6:
			rawData = rawData ^ BIT_FIVE;
			break;
		case 0x7:
			rawData = rawData ^ BIT_SIX;
			break;

	}

	/* With that done, our byte should be corrected, so we can pass it on
	   for decoding. */

	return rawData;
}


/*
 * unsigned char decode(unsigned char lowByte, unsigned char highByte) - 
 * takes two encoded nibbles and recovers the original byte. Assumes the 
 * low-order nibble is given first.
 */
unsigned char decode(unsigned char lowByte, unsigned char highByte)
{

	/* A byte to stick the result in */
	unsigned char result = 0x0;

	/* Recover the information bits in the first nibble, and stick them into
	   the result */

	if(BIT_TWO & lowByte) {

		/* This will evaluate to true only if the first data bit in the 
		   encoded nibble is 1. In that case, we set the first bit of the
		   result to 1. Since the bit is by default 0, we need not do 
		   anything if the first data bit is a 0 */

		result = result | BIT_ZERO;
	}

	if(BIT_FOUR & lowByte) 
		result = result | BIT_ONE;
	if(BIT_FIVE & lowByte)
		result = result | BIT_TWO;
	if(BIT_SIX & lowByte)
		result = result | BIT_THREE;

	/* Now on to the second encoded nibble */
	if(BIT_TWO & highByte)
		result = result | BIT_FOUR;
	if(BIT_FOUR & highByte)
		result = result | BIT_FIVE;
	if(BIT_FIVE & highByte)
		result = result | BIT_SIX;
	if(BIT_SIX & highByte)
		result = result | BIT_SEVEN;

	/* With that done, result should hold the proper byte. Return it. */
	return result;

}

/* 
 * unsigned char correctAndDecode(unsigned char lowByte, unsigned char 
 * highByte) - corrects and decodes two encoded nibbles, returning the 
 * original byte.
 */
unsigned char correctAndDecode(unsigned char lowByte, 
		unsigned char highByte)
{

	/* Correct both bytes */
	lowByte = correct(lowByte);
	highByte = correct(highByte);

	/* Decode and return them */
	return decode(lowByte, highByte);

}

