#include "ActionEncoder.h"

ActionEncoder::ActionEncoder(PinName tx, PinName rx) : Serial(tx, rx, 115200)
{
    format(8, SerialBase::None, 1);
    action_counter = 0;
    i = 0;
    LastRead = 0;
    newDataArrived = false;

    encoder_to_center = sqrt((encoder_2_global_x * encoder_2_global_x) + (encoder_2_global_y * encoder_2_global_y));
    encoder2local_angle = encoder_2_global_angle * DEG_TO_RAD;
    encoder_position_angle = ((270)) / float(180) * pi;                                              //90 +  angle to encoder location
    r = sqrt((encoder_2_global_x * encoder_2_global_x) + (encoder_2_global_y * encoder_2_global_y)); //encoder to center radius

    actionTimeout.start(); //This is for the ActionEncoder timeout, lest trapped in infinite loop/ cannot read char.
    //POTENTIAL BUG HERE. USE TIMER (MBED) FOR TIMEOUT TO ESCAPE LOOP.
    while (actionTimeout.read_ms() < 5000) //Wait for 5 seconds to check if it receives all information.
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
    } //start first to take offset from encoder... in case already moved
    
    actionTimeout.stop(); //Stop the timer, since it has no use afterwards.
}


bool ActionEncoder::translate(char c)
{
    switch (action_counter)
    {
    case 0:
        if (c == 0x0d)
            action_counter++;
        else
            action_counter = 0;
        break;
    case 1:
        if (c == 0x0a)
        {
            i = 0;
            action_counter++;
        }
        else if (c == 0x0d)
        {
        }
        else
            action_counter = 0;
        break;
    case 2:
        posture.data[i] = c;
        i++;
        if (i >= 24)
        {
            i = 0;
            action_counter++;
        }
        break;
    case 3:
        if (c == 0x0a)
            action_counter++;
        else
            action_counter = 0;
        break;
    case 4:
        if (c == 0x0d)
        {
            degreePos.w = posture.val[0] - tempPos.w;
            if (degreePos.w < -180)
            {
                degreePos.w = degreePos.w + 360;
            }
            else if (degreePos.w > 180)
            {
                degreePos.w = degreePos.w - 360;
            }
            aeReadPos.w += degreePos.w;
            tempPos.w = posture.val[0];
            aeReadPos.x = posture.val[3];
            aeReadPos.y = posture.val[4];
            newDataArrived = true;
        }
        action_counter = 0;
        return true;
        //break;
    default:
        action_counter = 0;
        break;
    }
    return false;
}

void ActionEncoder::calculatePos(float _X, float _Y, float _A, bool start)
{
    float zangle = _A - 360 * int(_A / 360);
    float zrangle = zangle * pi / float(180); //degree 2 rad

    float tx = ((_X / float(1000)) * cos(-encoder2local_angle)) - ((_Y / float(1000)) * sin(-encoder2local_angle));
    float ty = ((_X / float(1000)) * sin(-encoder2local_angle)) + ((_Y / float(1000)) * cos(-encoder2local_angle));

    float s = copysign(sqrt(2 * (r * r) - 2 * (r * r) * cos(zrangle)), zrangle);

    float x_bias = s * cos(zrangle / 2);
    float y_bias = s * sin(zrangle / 2);

    float x_tbias = (x_bias) * (cos(encoder_position_angle)) - (y_bias) * (sin(encoder_position_angle));
    float y_tbias = (x_bias) * (sin(encoder_position_angle)) + (y_bias) * (cos(encoder_position_angle));

    if (start)
    {
        startOffset.x = tx + y_tbias; //-
        startOffset.y = ty - x_tbias;
        //startOffset.x = tx + y_tbias ;
        //startOffset.y = ty - x_tbias ;  //+
        startOffset.w = _A * pi / float(180); //degree 2 rad
    }
    else
    {
        curPos.x = tx + y_tbias - startOffset.x; //-
        curPos.y = ty - x_tbias - startOffset.y;
        //curPos.x = tx + y_tbias   - startOffset.x;  //+
        //curPos.y = ty - x_tbias   - startOffset.y;
        curPos.w = _A * pi / float(180) - startOffset.w;
    }
}

bool ActionEncoder::curPosIsAvailable()
{
    if (readable())
    {
        char c = getc();
        if (translate(c))
        {
            calculatePos(aeReadPos.x, aeReadPos.y, aeReadPos.w);
            return true;
        }
    }
    return false;
}

struct position ActionEncoder::getCurPos()
{
    return curPos;
}

float ActionEncoder::getR()
{
    return r;
}




