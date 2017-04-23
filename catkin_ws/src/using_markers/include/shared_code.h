
#ifndef UNIVERSAL_CONSTANTS
#define UNIVERSAL_CONSTANTS

// Field constants
#define FIELD_LENGTH 9
#define FIELD_WIDTH 6
#define FIELD_CIRCLE 2
#define FIELD_LINE_WIDTH .05 // official is .01 but hard to see

// For error log printing
#include <stdio.h>

#define RATE 100
#define DT (1.0 / RATE)

#define d 4.0

#define PI 3.14159265358979323846

#define PRINT_ERROR(ERR)                                                                   \
do                                                                                       \
{                                                                                        \
	fprintf(stderr, "Error at %s :: Line %d :: %s\n", __PRETTY_FUNCTION__, __LINE__, ERR); \
} while(0)

#define PRINT_ERROR_AND(RET_CMD)                                                \
do                                                                            \
{                                                                             \
	fprintf(stderr, "Error at %s :: Line %d\n", __PRETTY_FUNCTION__, __LINE__); \
	RET_CMD;                                                                    \
} while(0)

#define MARKER_COMMAND_TOPIC "messenger_set_pos"
#define MARKER_POS_SERVER "service_get_pos"

//Different colors indicate different robots
enum
{
	RED_ID,
	ORANGE_ID,
	YELLOW_ID,
	GREEN_ID,
	BLUE_ID,
	PURPLE_ID,
	BALL_ID,
	FIELD_LINES_ID,
	FIELD_GRASS_ID,
	FIELD_CIRCLE_ID1,
	FIELD_CIRCLE_ID2
};

#endif /* UNIVERSAL_CONSTANTS */
