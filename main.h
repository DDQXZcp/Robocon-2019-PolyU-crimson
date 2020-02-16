#include "ActionEncoder.h"
#include "DebugClass.h"
#include "Motor.h"
#include "SlaveBoard.h"

// Heading for manual mode
#include "pinDefind.h"
#include "PS4_serial.h"



//Robot components
//DebugClass pc(USBTX, USBRX); //UART_2 (USBTX, USBRX = PA_9, PA_10)
SlaveBoard slave (PA_9, PA_10); //UART_1  //(PA_0, PA_1); //UART_4 for 446 only
Motor motor;
ActionEncoder action(PC_10, PC_11); //UART_3
DigitalIn  startAuto(USER_BUTTON);
DigitalOut led(LED1);

// Ticker
Ticker motorUpdateTicker;
//Ticker odom_updater;

// Constants
const float UPDATE_RATE = 0.08;//0.08;

// Robot parameters
float lx = INVERSE_KINEMATICS_LX;
float ly = INVERSE_KINEMATICS_LY;
float wheelR = WHEEL_RADIUS; // RoboMaster Mecanum wheel
float gear = GEAR_RATIO;
//float radian_to_rpm_convert = (RAD_TO_DEG / 360) * 60 * gear;
float radian_to_rpm_convert = (1/((2*PI)/60)) * gear * 2;
float r = action.getR();

// Robot Positioning
int targetPoint = 0;
int maxPointCount = 0; // will be replaced in initPath
struct pointInfo points[100];
struct position localVelocity = {.x = 0, .y = 0, .w = 0}, globalVelocity = {.x = 0, .y = 0, .w = 0}, curPos = {.x = 0, .y = 0, .w = 0};
struct position lastError = {.x = 0, .y = 0, .w = 0}; // For PID_D
struct position targetPos = {
    .x = points[0].targetPos.x,  //  +  startup_offset_x_encoder;
    .y = points[0].targetPos.y,  //  +  startup_offset_y_encoder;
    .w = points[0].targetPos.w * RAD_TO_DEG // -  startup_offset_w_encoder;
};
struct position tolerance = {
    .x = 0.08,
    .y = 0.08,
    .w = 0.1
};
struct position maxSpeed = {
    .x = 1,
    .y = 1,
    .w = 1
};
bool pidOn = points[0].pidOn;
Command command = points[0].command;

// PID
struct position PID_P = {.x = 2.75, .y = 2.75, .w = 2.5};
struct position PID_I = {.x = 0, .y = 0, .w = 0};
struct position PID_D = {.x = 0.75, .y = 0.75, .w = 0};

// Motor
int motor1 = 0;
int motor2 = 0;
int motor3 = 0;
int motor4 = 0;

// Runtime Parameters
bool autoMode = true;//true;

// Block PS4 button
Timer buttonBlock;
int blockTime = 100; // Block for 500 ms
bool firstPress = true;

// manual mode
float joy_range_mid = 128;
float joy_range = 1; //15
float linear_speed = 2;
float angular_speed = 2;
float vt = 0 ;
float vnt = 0 ;
float wt = 0 ;