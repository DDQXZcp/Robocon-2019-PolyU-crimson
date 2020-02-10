/*************IMPORTANT NOTICE***************/
/********ACTION ENCODER.CPP HAS A WHILE LOOP, WHICH PREVENT THE CODE FROM EXECUTING*******/
//COMMENT THE FOLLOWING (IN ACTIONENCODER.CPP): (RAW SOURCE ON MY TEST5 PROGRAM)
/*
while (1)
    {
        if (readable())
        {
            char c = getc();
            if (translate(c))
            {
                calculatePos(aeReadPos.x, aeReadPos.y, aeReadPos.w, true); //global
                break;
            }
        }
    }
*/

#include "main.h"
#include <string>

//VESC vesc;
//Serial ps4PC(USBTX,USBRX,115200); //This is for PS4 input debug.
//DigitalOut myled(LED1);

void initPath()
{
points[0] = (pointInfo){.targetPos.x = 0.0948683, .targetPos.y = 0.0316228, .targetPos.w = 0};
points[1] = (pointInfo){.targetPos.x = 0.189756, .targetPos.y = 0.0631886, .targetPos.w = 0};
points[2] = (pointInfo){.targetPos.x = 0.2847, .targetPos.y = 0.0945837, .targetPos.w = 0};
points[3] = (pointInfo){.targetPos.x = 0.379737, .targetPos.y = 0.125694, .targetPos.w = 0};
points[4] = (pointInfo){.targetPos.x = 0.474904, .targetPos.y = 0.156405, .targetPos.w = 0};
points[5] = (pointInfo){.targetPos.x = 0.570236, .targetPos.y = 0.186603, .targetPos.w = 0};
points[6] = (pointInfo){.targetPos.x = 0.665764, .targetPos.y = 0.216173, .targetPos.w = 0};
points[7] = (pointInfo){.targetPos.x = 0.76152, .targetPos.y = 0.244998, .targetPos.w = 0};
points[8] = (pointInfo){.targetPos.x = 0.857529, .targetPos.y = 0.272965, .targetPos.w = 0};
points[9] = (pointInfo){.targetPos.x = 0.953817, .targetPos.y = 0.299958, .targetPos.w = 0};
points[10] = (pointInfo){.targetPos.x = 1.0504, .targetPos.y = 0.325861, .targetPos.w = 0};
points[11] = (pointInfo){.targetPos.x = 1.14731, .targetPos.y = 0.35056, .targetPos.w = 0};
points[12] = (pointInfo){.targetPos.x = 1.24453, .targetPos.y = 0.373942, .targetPos.w = 0};
points[13] = (pointInfo){.targetPos.x = 1.34209, .targetPos.y = 0.395897, .targetPos.w = 0};
points[14] = (pointInfo){.targetPos.x = 1.43999, .targetPos.y = 0.416315, .targetPos.w = 0};
points[15] = (pointInfo){.targetPos.x = 1.53821, .targetPos.y = 0.435092, .targetPos.w = 0};
points[16] = (pointInfo){.targetPos.x = 1.63675, .targetPos.y = 0.45213, .targetPos.w = 0};
points[17] = (pointInfo){.targetPos.x = 1.73558, .targetPos.y = 0.467332, .targetPos.w = 0};
points[18] = (pointInfo){.targetPos.x = 1.8347, .targetPos.y = 0.480615, .targetPos.w = 0};
points[19] = (pointInfo){.targetPos.x = 1.93406, .targetPos.y = 0.491899, .targetPos.w = 0};
points[20] = (pointInfo){.targetPos.x = 2.03363, .targetPos.y = 0.501117, .targetPos.w = 0};
points[21] = (pointInfo){.targetPos.x = 2.13338, .targetPos.y = 0.508212, .targetPos.w = 0};
points[22] = (pointInfo){.targetPos.x = 2.23326, .targetPos.y = 0.513139, .targetPos.w = 0};
points[23] = (pointInfo){.targetPos.x = 2.33322, .targetPos.y = 0.515867, .targetPos.w = 0};
points[24] = (pointInfo){.targetPos.x = 2.43322, .targetPos.y = 0.516378, .targetPos.w = 0};
points[25] = (pointInfo){.targetPos.x = 2.53321, .targetPos.y = 0.514667, .targetPos.w = 0};
points[26] = (pointInfo){.targetPos.x = 2.63313, .targetPos.y = 0.510745, .targetPos.w = 0};
points[27] = (pointInfo){.targetPos.x = 2.73294, .targetPos.y = 0.504638, .targetPos.w = 0};
points[28] = (pointInfo){.targetPos.x = 2.8326, .targetPos.y = 0.496381, .targetPos.w = 0};
points[29] = (pointInfo){.targetPos.x = 2.93206, .targetPos.y = 0.486028, .targetPos.w = 0};
points[30] = (pointInfo){.targetPos.x = 3.03129, .targetPos.y = 0.473639, .targetPos.w = 0};
points[31] = (pointInfo){.targetPos.x = 3.13026, .targetPos.y = 0.459288, .targetPos.w = 0};
points[32] = (pointInfo){.targetPos.x = 3.22893, .targetPos.y = 0.443058, .targetPos.w = 0};
points[33] = (pointInfo){.targetPos.x = 3.3273, .targetPos.y = 0.42504, .targetPos.w = 0};
points[34] = (pointInfo){.targetPos.x = 3.42533, .targetPos.y = 0.40533, .targetPos.w = 0};
points[35] = (pointInfo){.targetPos.x = 3.52304, .targetPos.y = 0.384033, .targetPos.w = 0};
points[36] = (pointInfo){.targetPos.x = 3.62041, .targetPos.y = 0.361255, .targetPos.w = 0};
points[37] = (pointInfo){.targetPos.x = 3.71745, .targetPos.y = 0.337107, .targetPos.w = 0};
points[38] = (pointInfo){.targetPos.x = 3.81417, .targetPos.y = 0.311703, .targetPos.w = 0};
points[39] = (pointInfo){.targetPos.x = 3.91058, .targetPos.y = 0.285158, .targetPos.w = 0};
points[40] = (pointInfo){.targetPos.x = 4.00671, .targetPos.y = 0.257586, .targetPos.w = 0};
points[41] = (pointInfo){.targetPos.x = 4.10257, .targetPos.y = 0.229104, .targetPos.w = 0};
points[42] = (pointInfo){.targetPos.x = 4.19819, .targetPos.y = 0.199829, .targetPos.w = 0};
points[43] = (pointInfo){.targetPos.x = 4.29359, .targetPos.y = 0.169877, .targetPos.w = 0};
points[44] = (pointInfo){.targetPos.x = 4.38882, .targetPos.y = 0.139362, .targetPos.w = 0};
points[45] = (pointInfo){.targetPos.x = 4.48391, .targetPos.y = 0.108402, .targetPos.w = 0};
points[46] = (pointInfo){.targetPos.x = 4.57889, .targetPos.y = 0.0771089, .targetPos.w = 0};
points[47] = (pointInfo){.targetPos.x = 4.67379, .targetPos.y = 0.0455988, .targetPos.w = 0};
points[48] = (pointInfo){.targetPos.x = 4.76867, .targetPos.y = 0.0139854, .targetPos.w = 0};
points[49] = (pointInfo){.targetPos.x = 4.86354, .targetPos.y = -0.0176173, .targetPos.w = 0};
points[50] = (pointInfo){.targetPos.x = 4.95846, .targetPos.y = -0.0490956, .targetPos.w = 0};
points[51] = (pointInfo){.targetPos.x = 5.05345, .targetPos.y = -0.0803355, .targetPos.w = 0};
points[52] = (pointInfo){.targetPos.x = 5.14856, .targetPos.y = -0.111223, .targetPos.w = 0};
points[53] = (pointInfo){.targetPos.x = 5.24382, .targetPos.y = -0.141643, .targetPos.w = 0};
points[54] = (pointInfo){.targetPos.x = 5.33927, .targetPos.y = -0.171482, .targetPos.w = 0};
points[55] = (pointInfo){.targetPos.x = 5.43493, .targetPos.y = -0.200625, .targetPos.w = 0};
points[56] = (pointInfo){.targetPos.x = 5.53083, .targetPos.y = -0.228955, .targetPos.w = 0};
points[57] = (pointInfo){.targetPos.x = 5.627, .targetPos.y = -0.256357, .targetPos.w = 0};
points[58] = (pointInfo){.targetPos.x = 5.72347, .targetPos.y = -0.282717, .targetPos.w = 0};
points[59] = (pointInfo){.targetPos.x = 5.82024, .targetPos.y = -0.30792, .targetPos.w = 0};
points[60] = (pointInfo){.targetPos.x = 5.91733, .targetPos.y = -0.331852, .targetPos.w = 0};
points[61] = (pointInfo){.targetPos.x = 6.01476, .targetPos.y = -0.3544, .targetPos.w = 0};
points[62] = (pointInfo){.targetPos.x = 6.11252, .targetPos.y = -0.375456, .targetPos.w = 0};
points[63] = (pointInfo){.targetPos.x = 6.2106, .targetPos.y = -0.394914, .targetPos.w = 0};
points[64] = (pointInfo){.targetPos.x = 6.30901, .targetPos.y = -0.41267, .targetPos.w = 0};
points[65] = (pointInfo){.targetPos.x = 6.40773, .targetPos.y = -0.42863, .targetPos.w = 0};
points[66] = (pointInfo){.targetPos.x = 6.50674, .targetPos.y = -0.442704, .targetPos.w = 0};
points[67] = (pointInfo){.targetPos.x = 6.606, .targetPos.y = -0.45481, .targetPos.w = 0};
points[68] = (pointInfo){.targetPos.x = 6.70549, .targetPos.y = -0.464876, .targetPos.w = 0};
points[69] = (pointInfo){.targetPos.x = 6.80518, .targetPos.y = -0.47284, .targetPos.w = 0};
points[70] = (pointInfo){.targetPos.x = 6.90501, .targetPos.y = -0.478654, .targetPos.w = 0};
points[71] = (pointInfo){.targetPos.x = 7.00494, .targetPos.y = -0.482279, .targetPos.w = 0};
points[72] = (pointInfo){.targetPos.x = 7.10493, .targetPos.y = -0.483693, .targetPos.w = 0};
points[73] = (pointInfo){.targetPos.x = 7.20493, .targetPos.y = -0.482885, .targetPos.w = 0};
points[74] = (pointInfo){.targetPos.x = 7.30488, .targetPos.y = -0.479861, .targetPos.w = 0};
points[75] = (pointInfo){.targetPos.x = 7.40475, .targetPos.y = -0.474639, .targetPos.w = 0};
points[76] = (pointInfo){.targetPos.x = 7.50447, .targetPos.y = -0.467251, .targetPos.w = 0};
points[77] = (pointInfo){.targetPos.x = 7.60402, .targetPos.y = -0.457744, .targetPos.w = 0};
points[78] = (pointInfo){.targetPos.x = 7.70335, .targetPos.y = -0.446174, .targetPos.w = 0};
points[79] = (pointInfo){.targetPos.x = 7.80242, .targetPos.y = -0.432612, .targetPos.w = 0};
points[80] = (pointInfo){.targetPos.x = 7.90122, .targetPos.y = -0.417136, .targetPos.w = 0};
points[81] = (pointInfo){.targetPos.x = 7.99971, .targetPos.y = -0.399834, .targetPos.w = 0};
points[82] = (pointInfo){.targetPos.x = 8.09788, .targetPos.y = -0.3808, .targetPos.w = 0};
points[83] = (pointInfo){.targetPos.x = 8.19573, .targetPos.y = -0.360136, .targetPos.w = 0};
points[84] = (pointInfo){.targetPos.x = 8.29323, .targetPos.y = -0.337947, .targetPos.w = 0};
points[85] = (pointInfo){.targetPos.x = 8.39041, .targetPos.y = -0.314343, .targetPos.w = 0};
points[86] = (pointInfo){.targetPos.x = 8.48726, .targetPos.y = -0.289436, .targetPos.w = 0};
points[87] = (pointInfo){.targetPos.x = 8.58379, .targetPos.y = -0.263341, .targetPos.w = 0};
points[88] = (pointInfo){.targetPos.x = 8.68003, .targetPos.y = -0.236173, .targetPos.w = 0};
points[89] = (pointInfo){.targetPos.x = 8.77599, .targetPos.y = -0.208047, .targetPos.w = 0};
points[90] = (pointInfo){.targetPos.x = 8.87171, .targetPos.y = -0.179081, .targetPos.w = 0};
points[91] = (pointInfo){.targetPos.x = 8.9672, .targetPos.y = -0.14939, .targetPos.w = 0};
points[92] = (pointInfo){.targetPos.x = 9.0625, .targetPos.y = -0.119091, .targetPos.w = 0};
points[93] = (pointInfo){.targetPos.x = 9.15764, .targetPos.y = -0.0882974, .targetPos.w = 0};
points[94] = (pointInfo){.targetPos.x = 9.25265, .targetPos.y = -0.0571259, .targetPos.w = 0};
points[95] = (pointInfo){.targetPos.x = 9.34758, .targetPos.y = -0.0256904, .targetPos.w = 0};
points[96] = (pointInfo){.targetPos.x = 9.44246, .targetPos.y = 0.00589465, .targetPos.w = 0};
points[97] = (pointInfo){.targetPos.x = 9.53733, .targetPos.y = 0.0375154, .targetPos.w = 0};
points[98] = (pointInfo){.targetPos.x = 9.63223, .targetPos.y = 0.0690581, .targetPos.w = 0};
points[99] = (pointInfo){.targetPos.x = 9.72719, .targetPos.y = 0.100409, .targetPos.w = 0};

 maxPointCount = 100;
}

void inverse(float vx, float vy, float w)
{ 
    int maxPVelocity = motor.getMaxPVelocity();
    motor1 = constrain(int((1 / wheelR) * (vx - vy - (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
    motor2 = constrain(int((1 / wheelR) * (vx + vy + (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
    motor3 = constrain(int((1 / wheelR) * (vx + vy - (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
    motor4 = constrain(int((1 / wheelR) * (vx - vy + (lx + ly) * w) * radian_to_rpm_convert) , -maxPVelocity, maxPVelocity);
}

void motorUpdate()
{
    //motor.update(motor1, motor2, motor3, motor4);
    // PS4 function
    //checkFlatLoop();
}

void odomUpdate()
{
    // Run the function if timeout
    if(odomTimer.read_ms() >= int(odomTime) || firstRun)
    {
        firstRun = false;
        // Stop the timer
        odomTimer.stop();
        
        // Stop the robot if finished
        if(targetPoint >= maxPointCount - 1)
        {
            odomTimer.reset();
            motor.update(0, 0, 0, 0);
            return;
        }

        // find nearest point
        double lowestMagnitude = 99999.9;
        for(int i = targetPoint; i < maxPointCount; i++)
        {
            // find the error
            struct position error = {.x = points[i].targetPos.x - curPos.x, .y = points[i].targetPos.y - curPos.y, .w = 0};
            double magnitude = sqrt(error.x * error.x + error.y * error.y);
            // the nearest point found, set the target
            if(magnitude < lowestMagnitude)
            {
                lowestMagnitude = magnitude;
                if(i + 1 > maxPointCount)
                {
                    targetPoint = maxPointCount - 1;
                    break;
                }   
                else
                    targetPoint = i + 1;
            }
        }

        // find the magnitude
        struct position error = {.x = points[targetPoint].targetPos.x - curPos.x, .y = points[targetPoint].targetPos.y - curPos.y, .w = 0};
        // Find reaching time for next point
        odomTime = sqrt(error.x * error.x + error.y * error.y) / maximunSpeed * 1000.0;
        
        // Use maximun speed to run
        
        // find the speed of x & y
        double theta = atan(error.y/error.x);
        localVelocity.x = maximunSpeed * cos(theta);
        localVelocity.y = maximunSpeed * sin(theta);

        
        // convert to global
        globalVelocity.x = localVelocity.x * cos(-curPos.w) - localVelocity.y * sin(-curPos.w);
        globalVelocity.y = localVelocity.x * sin(-curPos.w) + localVelocity.y * cos(-curPos.w); //local to global transformation   (angle only)
        inverse(globalVelocity.x, globalVelocity.y, 0);
        motor.update(motor1, motor2, motor3, motor4);
    
        // Restart the timer
        odomTimer.reset();
        odomTimer.start();
    }
}

float map(float in, float inMin, float inMax, float outMin, float outMax)
{
    // check it's within the range
    if (inMin < inMax)
    {
        if (in <= inMin)
            return outMin;
        if (in >= inMax)
            return outMax;
    }
    else
    { // cope with input range being backwards.
        if (in >= inMin)
            return outMin;
        if (in <= inMax)
            return outMax;
    }
    // calculate how far into the range we are
    float scale = (in - inMin) / (inMax - inMin);
    // calculate the output.
    return outMin + scale * (outMax - outMin);
}

void high_func_LH()
{
    if (!autoMode)
    {
        if (((joy_range_mid - joy_range) < getLY()) and (getLY() < (joy_range_mid + joy_range)))
        {
            vt = 0;
        }
        else
        {
            //vt = map(getLY(),0,255,-1,1) * linear_speed ;
            float temp = map(getLY(), 0, 255, -1, 1);
            if (temp < 0)
            {
                vt = (temp * temp) * -1 * linear_speed;
            }
            else
            {
                vt = (temp * temp) * linear_speed;
            }
        }

        if (((joy_range_mid - joy_range) < getLX()) and (getLX() < (joy_range_mid + joy_range)))
        {
            vnt = 0;
        }
        else
        {
            //vnt = map(getLX(),0,255,-1,1) * linear_speed ;
            float temp = map(getLX(), 0, 255, -1, 1);
            if (temp < 0)
            {
                vnt = (temp * temp) * -1 * linear_speed;
            }
            else
            {
                vnt = (temp * temp) * linear_speed;
            }
        }
    }
}
void high_func_RH()
{
    if (!autoMode)
    {
        if (((joy_range_mid - joy_range) < getRX()) and (getRX() < (joy_range_mid + joy_range)))
        {
            wt = 0;
        }
        else
        {
            //wt = map(getRX(),0,255,-1,1) * angular_speed ;
            float temp = map(getRX(), 0, 255, -1, 1);
            if (temp < 0)
            {
                wt = (temp * temp) * -1 * angular_speed;
            }
            else
            {
                wt = (temp * temp) * angular_speed;
            }
        }
    }
}
void high_func_CommandChange() {}
void high_func_L2() {}
void high_func_R2() {}
void high_func_TRI() 
{
}
void high_func_CIR() {}
void high_func_CRO() {}
void high_func_SQU() {}
void high_func_UP() 
{   }
void high_func_RIGHT() {}
void high_func_DOWN() {}
void high_func_LEFT() {}
void high_func_L1()
{
    if (!autoMode)
    {
        targetPoint = 0;
        maxPointCount = 1;
                
        tolerance.x = 0.01;
        tolerance.y = 0.01;
        tolerance.w = 0.1;

        targetPos.x = 4.1;              //+    startup_offset_x_encoder;
        targetPos.y = -3;              //+    startup_offset_y_encoder;
        targetPos.w = -165 * DEG_TO_RAD; //-    startup_offset_w_encoder;

        command = noAction;

        maxSpeed.x = 1.5;
        maxSpeed.y = 1.5;
        maxSpeed.w = 1.5;
        
        autoMode = true;
        motorUpdateTicker.attach(&motorUpdate, UPDATE_RATE);
    }
}
void high_func_L3() {}
void high_func_R1()
{
    if (autoMode)
    {
        targetPoint = 0;
        maxPointCount = 1;
                
        tolerance.x = 0.01;
        tolerance.y = 0.01;
        tolerance.w = 0.1;

        targetPos.x = 4.1;              //+    startup_offset_x_encoder;
        targetPos.y = -3;              //+    startup_offset_y_encoder;
        targetPos.w = -165 * DEG_TO_RAD; //-    startup_offset_w_encoder;

        command = noAction;

        maxSpeed.x = 1.5;
        maxSpeed.y = 1.5;
        maxSpeed.w = 1.5;
        
        autoMode = false;
        motorUpdateTicker.detach();
        motor.manual(); //This changes the acceleration to 99999;
        inverse(0,0,0);
    }
}
void high_func_R3() {}
void high_func_SHARE() 
{
    
}
void high_func_OPTIONS() {}
void low_func_CommandChange() {}
void low_func_LH()
{
    if (!autoMode)
    {
        vt = 0;
        vnt = 0;
    }
}
void low_func_RH()
{
    if (!autoMode)
    {
        wt = 0;
    }
}
void low_func_L2() {}
void low_func_R2() {}
void low_func_TRI() {}
void low_func_CIR() {}
void low_func_CRO() {}
void low_func_SQU() {}
void low_func_UP() {}
void low_func_RIGHT() {}
void low_func_DOWN() {}
void low_func_LEFT() {}
void low_func_L1() {}
void low_func_L3() {}
void low_func_R1() {}
void low_func_R3() {}
void low_func_SHARE() {}
void low_func_OPTIONS() {}
void fall_func_CommandChange() {}
void fall_func_LH()
{
    if (!autoMode)
    {
        vt = 0;
        vnt = 0;
    }
}
void fall_func_RH()
{
    if (!autoMode)
    {
        wt = 0;
    }
}
void fall_func_L2() {}
void fall_func_R2() {}
void fall_func_TRI() {}
void fall_func_CIR() {}
void fall_func_CRO() {}
void fall_func_SQU() {}
void fall_func_UP() {}
void fall_func_RIGHT() {}
void fall_func_DOWN() {}
void fall_func_LEFT() {}
void fall_func_R1()
{
    if (autoMode)
    {
        targetPoint = 0;
        maxPointCount = 1;
                
        tolerance.x = 0.01;
        tolerance.y = 0.01;
        tolerance.w = 0.1;

        targetPos.x = 4.1;              //+    startup_offset_x_encoder;
        targetPos.y = -3;              //+    startup_offset_y_encoder;
        targetPos.w = -165 * DEG_TO_RAD; //-    startup_offset_w_encoder;
        
        command = noAction;

        maxSpeed.x = 1.5;
        maxSpeed.y = 1.5;
        maxSpeed.w = 1.5;
        
        autoMode = false;
        motorUpdateTicker.detach();
    }
}
void fall_func_L3() {}
void fall_func_L1()
{
    if (!autoMode)
    {
        targetPoint = 0;
        maxPointCount = 1;
                
        tolerance.x = 0.01;
        tolerance.y = 0.01;
        tolerance.w = 0.1;

        targetPos.x = 4.1;              //+    startup_offset_x_encoder;
        targetPos.y = -3;              //+    startup_offset_y_encoder;
        targetPos.w = -165 * DEG_TO_RAD; //-    startup_offset_w_encoder;

        command = noAction;

        maxSpeed.x = 1.5;
        maxSpeed.y = 1.5;
        maxSpeed.w = 1.5;
        
        autoMode = true;
        motorUpdateTicker.attach(&motorUpdate, UPDATE_RATE);
    }
}
void fall_func_R3() {}
void fall_func_SHARE() {}
void fall_func_OPTIONS() {}
void rise_func_CommandChange() {}
void rise_func_LH() {}
void rise_func_RH() {}
void rise_func_L2() {}
void rise_func_R2() {}
void rise_func_TRI() 
{
    // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        slave.vesc();
        //slave.homing(); //<- For 3 pt
        //Debug
        //ps4PC.printf("VESC");
        //ps4PC.printf("the timer now is :%d \n",buttonBlock.read_ms());
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
        pc.printf("RISE TRI \n");
    }    
}
void rise_func_CIR() 
{
    // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        slave.fire();
        //Debug
        //ps4PC.printf("the timer now is :%d \n",buttonBlock.read_ms());
        //ps4PC.printf("Fire");       
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
    } 
}
void rise_func_CRO()
{
    // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        slave.charge();
        //Debug
        //ps4PC.printf("Stop");
        //ps4PC.printf("the timer now is :%d \n",buttonBlock.read_ms());
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
    }
    }
void rise_func_SQU() 
{
    // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        slave.homing();
        //slave.readyPosition(); //<- For 3 pt
        //Debug
        //ps4PC.printf("Homing");
        //ps4PC.printf("the timer now is :%d \n",buttonBlock.read_ms());
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
    }    
}
void rise_func_UP() 
{
    // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        slave.toggleVG();
        //Debug
        //ps4PC.printf("ToggleVG");
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
        pc.printf("RISE UP");
}    
    }
void rise_func_RIGHT() 
{
    // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        //slave.toggleHG();
        //slave.vesc();
        //Debug
        //ps4PC.printf("ToggleHG");
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
        pc.printf("RISE RIGHT");
    }       
}
void rise_func_DOWN() 
{
    // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        slave.toggleVS();
        //Debug
        //ps4PC.printf("ToggleVS");
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
        pc.printf("RISE DOWN");
}    
    }
void rise_func_LEFT() 
{
            // if the button blocked for 500 ms or the button press for first time
    if(buttonBlock.read_ms() >= blockTime || firstPress)
    {
        firstPress = false;
        // Stop the timer
        buttonBlock.stop();
        // Send messege to slave
        slave.toggleHS();
        //Debug
        //ps4PC.printf("toggleHS");
        // Restart the timer
        buttonBlock.reset();
        buttonBlock.start();
        pc.printf("RISE LEFT");
    } 
}
void rise_func_L1() {}
void rise_func_L3()
{
    if (!autoMode)
    {
        vt = 0;
        vnt = 0;
    }
}
void rise_func_R1() {}
void rise_func_R3()
{
    if (!autoMode)
    {
        wt = 0;
    }
}
void rise_func_SHARE() {}
void rise_func_OPTIONS() {}

int main()
{
    //myled = 1;
    //diu.printf("1");
    pc.printf("Now in main(), before initPath()");
    initPath();
    //diu.printf("2");
    // Manual mode
    //PS4_SERIAL_INIT();
    
    // Interrupt
    //motorUpdateTicker.attach(&motorUpdate, UPDATE_RATE);
    //pc.attach(&debugCommand, Serial::RxIrq);
    //pc.printf("Main");
    
    if(autoMode == false)
        motor.manual();
    
    while (1)
    {
        if (autoMode)
        {
            //diu.printf("In autoMode");
            if(action.curPosIsAvailable())
            {
                curPos = action.getCurPos();
                pc.printLocation(targetPoint, curPos, globalVelocity);
                odomUpdate();
            }
        }
        else
        {
            //diu.printf("In manual");
            inverse(-vt, -vnt, -wt);
            motorUpdate();
        }
    }
}


