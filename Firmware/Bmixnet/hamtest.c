/*
 * hamtest.c
 *
 * Does some tests on my Hamming decoding functions.
 *
 */

#include <stdio.h>
#include <assert.h>
#include "hamming.h"

int
main(int argc, char * argv[]) 
{

	/* We'll start with a byte that encodes 1011, according to Wikipedia */
	char lowByte = 0x66;

	/* We'll take another byte that should be 1001 encoded */
	char highByte = 0x4c;

	/* So we should have encoded 10011101, or 0x9d. Let's see if the decoder
	   recovers that */
	assert(decode(lowByte, highByte) == 0x9d);

	/* Now let's try flipping one of the bits on highByte */
	char badHighByte = highByte ^ BIT_FOUR;
	assert(badHighByte != highByte);
	
	/* Now we'll try and correct that error */
	assert(correct(badHighByte) == highByte);

	/* Lastly, let's put it together. We'll encode 0110 1011, put an error
	   in each nibble, and see if correctAndDecode recovers the original
	   input. */
	lowByte = 0x55 ^ BIT_TWO;
	highByte = 0x33 ^ BIT_SIX;
	
	assert(correctAndDecode(lowByte, highByte) == 0x6b);

	/* We can perhapse implement more rigorous test routines later, but that
	   should be enough for now. */

	return 0;

}

