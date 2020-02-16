# Robocon-2019-PolyU-crimson
Robocon 2019 PolyU crimson full explanation

## Positioning

### Data structure of points

In the init_path() of main.cpp
~~~
points[0] = (pointInfo){.targetPos.x = 0.0948683, .targetPos.y = 0.0316228, .targetPos.w = 0};
~~~

Trace back to main.h

~~~
struct pointInfo points[2000];

struct position targetPos = {
    .x = points[0].targetPos.x,  //  +  startup_offset_x_encoder;
    .y = points[0].targetPos.y,  //  +  startup_offset_y_encoder;
    .w = points[0].targetPos.w * RAD_TO_DEG // -  startup_offset_w_encoder;
};
~~~

Trace back to ActionEncoder.h Then to common.h(There is a bit confusing not to include common.h in main.h, but we also include common.h in ActionEncoder.h, so it doesn't matter

~~~
struct position {
    float x;
    float y;
    float w;
};
struct pointInfo
{
   struct position targetPos;

};
~~~
For struct pointInfo and position, I would like to say they the same thing. We just want to change the name only to avoid confusion. However, the struct in pointInfo is unnecessary

If apporved by team, we will change the struct "position" to other name

For your reference, there is an example of nested struct:
~~~
struct Employee
{
    short id;
    int age;
    double wage;
};
 
struct Company
{
    Employee CEO; // Employee is a struct within the Company struct
    int numberOfEmployees;
};
 
Company myCompany;
~~~
The hierarchy: Position = pointInfo < points = targetPos

## Slave board

## Manual mode

### configuration

in main.cpp
~~~
if(autoMode == false)
        motor.manual();
~~~

in main.h

Headings for manual mode
~~~
#include "ActionEncoder.h"
#include "DebugClass.h"
#include "Motor.h"
#include "SlaveBoard.h"

// Heading for manual mode
#include "pinDefind.h"
#include "PS4_serial.h"
~~~
parameters for manual mode
~~~
// manual mode
float joy_range_mid = 128;
float joy_range = 1; //15
float linear_speed = 2;
float angular_speed = 2;
float vt = 0 ;
float vnt = 0 ;
float wt = 0 ;
~~~

in motor.cpp

we found
~~~
void Motor::manual(){
    SET_P_ACCELERATION(1, 99999);
    SET_P_ACCELERATION(2, 99999);
    SET_P_ACCELERATION(3, 99999);
    SET_P_ACCELERATION(4, 99999);

    SET_P_DECELERATION(1, 99999);
    SET_P_DECELERATION(2, 99999);
    SET_P_DECELERATION(3, 99999);
    SET_P_DECELERATION(4, 99999);

    SET_QUICK_STOP_DECELERATION(1, 99999);
    SET_QUICK_STOP_DECELERATION(2, 99999);
    SET_QUICK_STOP_DECELERATION(3, 99999);
    SET_QUICK_STOP_DECELERATION(4, 99999);
}
~~~
There are a class called Motor and function manual()

And three setting functions: SET_P_ACCELERATION, SET_P_DECELERATION and SET_QUICK_STOP_DECELERATION for four wheels

in robot.h

~~~
#include "mbed.h"
//#include "LED.h"
#include "CANOpen.h"
#include "motion.h"
~~~

in motion.cpp

~~~
bool SET_P_ACCELERATION(uint8_t node_num, uint32_t data)
{
    if(!SDO_EXE(node_num,0x83,0x60,0x00,data,4)){; return 0;}
    //PC_SEND("SET PROFILE ACCELERATION: %d\n", data);
    return 1;
}
~~~
~~~
bool SET_P_DECELERATION(uint8_t node_num, uint32_t data)
{
    if(!SDO_EXE(node_num,0x84,0x60,0x00,data,4)){; return 0;}
    //PC_SEND("SET PROFILE DECELERATION: %d\n", data);
    return 1;
}
~~~
~~~
bool SET_QUICK_STOP_DECELERATION(uint8_t node_num, uint32_t data)
{
    if(!SDO_EXE(node_num,0x85,0x60,0x00,data,4)){; return 0;}
    //PC_SEND("SET QUICK STOP DECELERATION: %d\n", data);
    return 1;
}
~~~

### Set motor velocity

in main.cpp
~~~
void inverse(float vx, float vy, float w)
{ 
    int maxPVelocity = motor.getMaxPVelocity();
    motor1 = constrain(int((1 / wheelR) * (vx - vy - (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
    motor2 = constrain(int((1 / wheelR) * (vx + vy + (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
    motor3 = constrain(int((1 / wheelR) * (vx + vy - (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
    motor4 = constrain(int((1 / wheelR) * (vx - vy + (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
}
~~~
You have to know that, constrain is not an function, but a #define

in common.h
~~~
// Functions
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
~~~

in motor.cpp
~~~
int Motor::getMaxPVelocity()
{
    return maxPVelocity;
}
~~~

There is also a motor.update()
~~~
void motorUpdate()
{
    //motor.update(motor1, motor2, motor3, motor4);
    // PS4 function
    //checkFlatLoop();
}
~~~
~~~
void Motor::update(int motor1, int motor2, int motor3, int motor4) {
    /*
    SET_TARGET_VELOCITY(1, motor1*-1);
    SET_TARGET_VELOCITY(2, motor2);
    SET_TARGET_VELOCITY(3, motor3*-1);
    SET_TARGET_VELOCITY(4, motor4);
    */
    SET_TARGET_VELOCITY(1, motor1);
    SET_TARGET_VELOCITY(2, motor2 * -1);
    SET_TARGET_VELOCITY(3, motor3);
    SET_TARGET_VELOCITY(4, motor4 * -1);

    wait(0.002);
    RPDO1_EXE(1, SWITCH_ON_ENABLE_OP);
    RPDO1_EXE(2, SWITCH_ON_ENABLE_OP);
    RPDO1_EXE(3, SWITCH_ON_ENABLE_OP);
    RPDO1_EXE(4, SWITCH_ON_ENABLE_OP);
    wait(0.002);
}
~~~

For maxPVelocity, in motor.h
~~~
lass Motor {
    public:
        void init();
        void update(int motor1, int motor2, int motor3, int motor4);
        void manual();
        int getMaxPVelocity();
        Motor();
    private:
        static const int maxPVelocity = 8700;
};
~~~
maxPVelocity = 8700, it is a key parameter that needs to modify in actual use

Also, in PS4_command.cpp, there is a function of checkFlatLoop() to update the command
~~~
void checkFlatLoop()
    {
        if(CommandFlat[CommandChange] != old_CommandFlat[CommandChange] || CommandFlat[CommandChange])
            SetFlat();
        
        for(int i = 0; i < 19; i++)
        {
            if(CommandFlat[i] && !old_CommandFlat[i])
                (*ps4rise_func_ptr[i])();
            if(!CommandFlat[i] && old_CommandFlat[i])
                (*ps4fall_func_ptr[i])(); 
            if(CommandFlat[i])
                (*ps4high_func_ptr[i])();
            if(!CommandFlat[i])
                (*ps4low_func_ptr[i])();
~~~
