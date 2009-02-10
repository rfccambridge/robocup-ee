# 
# Makefile - Hamming Tests
#
# John Bestoso, 2/10/09
#

CC 	= gcc

CFLAGS 	= -ggdb -Wall

HEADERS	= hamming.h
LDLIBS 	= -lm

# The test rig
TEST		= hamtest
TEST_SRCS	= hamming.c hamtest.c
TEST_OBJS	= $(TEST_SRCS:.c=.o)

$(TEST): $(TEST_OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) $(LDLIBS)

clean:
	rm -f core $(TEST) *.o *~

