// Pin names
#define SS_M PINB0
#define SCK PINB1
#define MOSI PINB2
#define MISO PINB3
#define PWM1 PINB4
#define PWM2 PINB5
#define PWM3 PINB6
#define PWM4 PINB7

#define LED1 PINC0
#define LED2 PINC1
#define LED3 PINC2
#define LED4 PINC3

#define DIR1 PIND0
#define DIR2 PIND1
#define DIR3 PIND2
#define DIR4 PIND3
#define BREN PIND4

#define M1QA PINE0
#define M1QB PINE1
#define M2QA PINE2
#define M2QB PINE3
#define M3QA PINE4
#define M3QB PINE5
#define M4QA PINE6
#define M4QB PINE7

#define FAULT1 PING0
#define FAULT2 PING1
#define FAULT3 PING2
#define FAULT4 PING3
#define RESET PING5

// Set up system clock to max frequency and enable pins as output
void init(void);

// Set the break on if true (D4 low), otherwise turn break off (D4 high)
void setBrake(bool enable);

// Given a PWM line number and a direction as bool, sets the direction of that motor
void setDirection(PWM pwmNum, bool dir);