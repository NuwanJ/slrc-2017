
#define BLACK 0
#define WHITE 1

boolean debug = 0;
int buttonStatus = 1;
int lineType =  WHITE;

#define FRONT 8
#define LEFT 4
#define RIGHT 6
#define BACK 2

#define SERIAL_PORT 0
#define DEBUG_PORT 1

// Modes
enum {BEGIN, TEST, BLUETOOTH, MAZE_FOLLOW, WALL_FOLLOW, LINE_FOLLOW};

// EEPROM
enum {eP, eI, eD, eMax, eBase, eDebug};

#define DELAY_BUZZER 100
#define DELAY_BLINK 200

//-------------------------------------------------------------------------------------------------------------- Define debug options

//#define REALTIME_MOTOR_SPEEDS
//#define DEBUG_MODE

//-------------------------------------------------------------------------------------------------------------- Pin Mapping

#define LED_GREEN 13
#define LED_RED 11

#define BUTTON_0 4
#define BUTTON_1 3
#define BUTTON_2 2
#define BUTTON_3 A0
#define BUTTON_4 A1

#define PIN_BUZZER 34

#define rightMotor1 8
#define rightMotor2 6
#define rightMotorPWM 7

#define leftMotor1 10
#define leftMotor2 12
#define leftMotorPWM 9

//-------------------------------------------------------------------------------------------------------------- IR Sensors Array

#define NUM_SENSORS 6
#define RIGHT_EDGE_READING 0
#define LEFT_EDGE_READING (NUM_SENSORS - 1) * 10
#define CENTER_EDGE_READING (NUM_SENSORS - 1) * 5

unsigned int sensor_values[NUM_SENSORS];
const unsigned int irPins[] = {23, 25, 27, 49, 51, 53};

boolean allOut = 0, allIn = 0;
String irLineString = "000000";
int lastReading = CENTER_EDGE_READING;
int weight = 0, sum = 0, value = 0;
int leftEnd = 0, rightEnd = 0;

int frontSensor[] = {0, 0 , 0, 0};

//-------------------------------------------------------------------------------------------------------------- Line Following

float kP = 0, kD = 0, kI = 0;

int pos = CENTER_EDGE_READING;
int error = 0, lastError = 0;

int leftSpd = 0, rightSpd = 0;
const double slowFactor = 0.5, speedFactor = 1;

int rightMotorSpeed = 0, leftMotorSpeed = 0;

int maxSpeed = 250;
int baseSpeed = 150;

int drift = 0;

//-------------------------------------------------------------------------------------------------------------- Sonar Sensors

#define NUM_SONAR 4

enum {SONAR_1, SONAR_2, SONAR_3, SONAR_4};
const int pinTrig[] = { 31, 35, 39, 43};
const int pinEcho[] = { 33, 37, 41, 45};

double distance = 0, duration = 0;
const int maxDistance = 100;

double sonarDist[] = {0, 0, 0, 0} ;

//-------------------------------------------------------------------------------------------------------------- Color Sensor

uint16_t raw_clr, raw_red, raw_green, raw_blue;
enum {COLOR_OPEN, COLOR_RED, COLOR_GREEN, COLOR_BLUE};
int boxColor = 0;

#define WHITE_THERSOLD  800 // **This depends with the distance from sensor to the object
#define RED_GB_GAP 100

