
#ifndef UNIVERSAL_CONSTANTS
#define UNIVERSAL_CONSTANTS

// For error log printing
#include <stdio.h>

#define RATE 100
#define DT (1.0 / RATE)

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

#define ROBOT_COMMAND_TOPIC "messenger_set_pos"
#define ROBOT_POS_SERVER "service_get_pos"

// different colors indicate different robots
enum
{
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  PURPLE,
  BALL_ID
};

#endif /* UNIVERSAL_CONSTANTS */
