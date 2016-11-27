
#ifndef UNIVERSAL_CONSTANTS
#define UNIVERSAL_CONSTANTS

//For error log printing
#include <stdio.h>

#define RATE 100
#define DT (1.0 / RATE)

#define PRINT_ERROR_AND(RET_CMD)                                        \
  do{                                                                   \
    fprintf(stderr, "Error at %s :: Line %d\n", __PRETTY_FUNCTION__, __LINE__); \
    RET_CMD;                                                            \
  }while(0)                                                             \

#endif /* UNIVERSAL_CONSTANTS */
