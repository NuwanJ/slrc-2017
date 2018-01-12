

#define BLACK 0
#define WHITE 1

boolean debug = 0;
int lineType =  BLACK;

#define slave_address 8

enum {BLUE_BOX, GREEN_BOX, RED_BOX, FINAL_BOX, DEF};

#define PIN_STEPPER_EN 22
#define PIN_SERVO 24
#define PIN_SPINNER 2

#define SERVO_RELEASE 170 //170
#define SERVO_LOAD 90 //90

#define SPINNER_PWM 100

#define PIN_R 52
#define PIN_G 50
#define PIN_B 48

#define PIN_MA 3
#define PIN_MB 4

// B G R
// 28 52 76
// 5 5 5
int x[] = {14, 36, 55, 180};
int y[] = {-1, -1, -1, 0};
int s[] = {100, 90, 100, 100, 100};
int del[] = {5000, 4000, 5000, 5000, 5000};

/*
  int x[] = {28, 52, 77, 180};
  int y[] = {5, 5, 5, 0};
*/

int finalX[] = {175, 170, 165, 155, 140};
int finalY[] = {0, 0, 0, 0, 0};





