

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

// Mode eNum
enum {BEGIN, TEST, BLUETOOTH};

// EEPROM eNum
enum {eP, eI, eD, eMax, eBase, eDebug};

#define DELAY_BUZZER 200

//-------------------------------------------------------------------------------------------------------------- Pin Mapping

#define PIN_LED 13

#define BUTTON_1 52
#define BUTTON_2 53
#define BUTTON_3 7
#define BUTTON_4 8

#define PIN_BUZZER -1

//-------------------------------------------------------------------------------------------------------------- IR Sensors Array

#define NUM_SENSORS 6
#define RIGHT_EDGE_READING 0
#define LEFT_EDGE_READING (NUM_SENSORS - 1) * 10
#define CENTER_EDGE_READING (NUM_SENSORS - 1) * 5

unsigned int sensor_values[NUM_SENSORS];
const unsigned int irPins[] = {A0, A1, A2, A3, A4, A5};

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

#define rightMotor1 11
#define rightMotor2 12
#define rightMotorPWM 7

#define leftMotor1 10
#define leftMotor2 8
#define leftMotorPWM 9

int leftSpd = 0, rightSpd = 0;
const double slowFactor = 0.5, speedFactor = 1;

int rightMotorSpeed = 0, leftMotorSpeed = 0;

int maxSpeed = 250;
int baseSpeed = 150;

int drift = 0;


//-------------------------------------------------------------------------------------------------------------- Sonar Sensors

#define NUM_SONAR 3

enum {SONAR_1, SONAR_2, SONAR_3};
const int pinTrig[] = { 5, 3, -1};
const int pinEcho[] = { 6, 4, -1};

//-------------------------------------------------------------------------------------------------------------- Color Sensor
uint16_t raw_clr, raw_red, raw_green, raw_blue;
enum {COLOR_OPEN, COLOR_RED, COLOR_GREEN, COLOR_BLUE};
int boxColor = 0;

#define WHITE_THERSOLD  800 // **This depends with the distance from sensor to the object
#define RED_GB_GAP 100


//-------------------------------------------------------------------------------------------------------------- Sonar Sensor
double distance = 0, duration = 0;
const int maxDistance = 100;

