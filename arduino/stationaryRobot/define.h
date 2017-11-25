

#define BLACK 0
#define WHITE 1

boolean debug = 0;
int lineType =  BLACK;

#define slave_address 8

#define FRONT 8
#define LEFT 4
#define RIGHT 6
#define BACK 2

// Mode eNum
enum {BEGIN, TEST};

// EEPROM eNum
enum {eP, eI, eD, eMax, eBase, eDebug};

//-------------------------------------------------------------------------------------------------------------- Pin Mapping

#define PIN_LED 13
#define BUTTON_1 5

int buttonStatus = 1;

//-------------------------------------------------------------------------------------------------------------- IR Sensors Array

#define NUM_SENSORS 6
#define RIGHT_EDGE_READING 0
#define LEFT_EDGE_READING (NUM_SENSORS - 1) * 10
#define CENTER_EDGE_READING (NUM_SENSORS - 1) * 5

unsigned int sensor_values[NUM_SENSORS];

const unsigned int irPins[] = {A0, A1, A2, A3, A6, A7};
const unsigned int midPin = 18;

boolean allOut = 0;
boolean allIn = 0;
String irLineString = "000000";
int lastReading = CENTER_EDGE_READING;
int weight = 0, sum = 0, value = 0;
int leftEnd = 0, rightEnd = 0;
int reading[6];

int frontSensor[] = {0, 0 , 0, 0};

//-------------------------------------------------------------------------------------------------------------- Line Following

float kP = 0, kD = 0, kI = 0;

int pos = CENTER_EDGE_READING;
int error = 0;
int lastError = 0;

// 11 12 10
#define rightMotor1 7
#define rightMotor2 8
#define rightMotorPWM 9

// 7 8 9
#define leftMotor1 11
#define leftMotor2 12
#define leftMotorPWM 10


int leftSpd = 0, rightSpd = 0;
const double slowFactor = 0.5;
const double speedFactor = 1;

int rightMotorSpeed = 0, leftMotorSpeed = 0;

int maxSpeed = 250;
int baseSpeed = 150;

int drift = 0;
int linePos = 0;



