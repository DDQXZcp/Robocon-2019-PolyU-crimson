/*
version 6 7/6/2019
ready()

 This is VESC. rip donald's code
*/

///////////////////////////
#include <hfCore.h>
#include "actiondrv.h"//THIS is not a actiondriver code.
#include <limits>
///////////////////////////

actionDrv action1(8,9); //the node of the 2 vesc

//WATCH THIS !!!!!
//d12 if you are connecting the sig.(D12) to GND PullUp  if +5V PullDown
DigitalIn homingLimitSwitch(PA_6,PullUp);
//d11
DigitalIn chargeLimitSwitch(PA_7,PullUp);
//ready
DigitalIn readyLimitSwitch(PA_9,PullUp);

//construstor
hfCore::hfCore(bool debug)
    :edgeLimitEStop(false)
    ,motorMode(false)
    ,isStop(false)
    ,lock(false)
    ,turboLock(true)
{
    printf("[HFCore]configing...\n");
    setHfCoreDebug(true);
    setMotorSpeed(800);
    setMotorTurboSpeed(1600);
    setHfTurboPercentage(0.8);
    setTravelLength(0.23);
    setGeartRatio(12.5);
    
    acc = INT_MAX-100;
    dec = INT_MAX-100;
}
/*
hfCore::hfCore(bool debug,float hfSpeed,float hfTurboSpeed, double turboPercentage, double length, double gearRatio)
    :edgeLimitEStop(false)
    ,motorMode(false)
    ,isStop(false)
    ,turboLock(true)
    ,lock(false)
{
    setHfCoreDebug(debug);
    setMotorSpeed(hfSpeed);
    setMotorTurboSpeed(hfTurboSpeed);
    setHfTurboPercentage(turboPercentage);
    setTravelLength(length);
    setGeartRatio(gearRatio);
    
    acc = INT_MAX-100;
    dec = INT_MAX-100;
}*/


// :>
hfCore::hfCore(bool debug,float hfSpeed,float hfTurboSpeed, double readyToChargeLengthInp)
    :edgeLimitEStop(false)
    ,motorMode(false)
    ,isStop(false)
    ,turboLock(true)
    ,lock(false)
{
    setHfCoreDebug(debug);
    setMotorSpeed(hfSpeed);
    setMotorTurboSpeed(hfTurboSpeed);
    
    setHfCoreDebug(true);
    setHfTurboPercentage(0.8);
    setTravelLength(0.23);
    setReadyToChargeLength(readyToChargeLengthInp);
    setGeartRatio(12.5);
    
    acc = INT_MAX-100;
    dec = INT_MAX-100;
}

//on999 servo===================================================================
void hfCore::setupServo(PinName pin, double periodINP, double pulseWidth1INP, double pulseWidth2INP, double timeIntervalINP)
{
    servo = new PwmOut(pin);
    period = periodINP;
    pulseWidth1 = pulseWidth1INP;
    pulseWidth2 = pulseWidth2INP;
    timeInterval = timeIntervalINP;
  
  
    //start servo
    servo->period(period); 
}

//move the RC servo
void hfCore::servoMove()
{
  //initalize position
    servo->pulsewidth(pulseWidth1);
  //wait(timeInterval);
  
  //pull anticlockwise if pulseWidth2 > pulseWidth1
    servo->pulsewidth(pulseWidth2); 
    wait(timeInterval);
  
  //back to original position
    servo->pulsewidth(pulseWidth1);
    wait(timeInterval);
}
//hf core=======================================================================
//set/get debug mode------------------------------------------------------------
void hfCore::setHfCoreDebug(bool inp){
    hfCoreDebug = inp;
    if (inp){
        printf("[HFCore]Turn on debug mode\n");
    }else{
        printf("[HFCore]Turn off debug mode\n");
    }
}

bool hfCore::getHfCoreDebug(void){
    return hfCoreDebug;
}

//Estop-------------------------------------------------------------------------
void hfCore::setEdgeLimitEStop(bool inp){
    edgeLimitEStop = inp;
    if (hfCoreDebug){
        printf("[HFCore]Turn on edge estop mode");
    }
}

bool hfCore::getEdgeLimitEStop(void){
    return edgeLimitEStop;
}

//set/get motorSpeed------------------------------------------------------------
void hfCore::setMotorSpeed(float inp){
    motorSpeed = inp;
    
    if(hfCoreDebug){
        printf("[HF:Core]Set Motor Speed to %.2lf\n",motorSpeed);
    }
}

float hfCore::getMotorSpeed(void){
    return motorSpeed;
}

//set/get motorTurboSpeed-------------------------------------------------------
void hfCore::setMotorTurboSpeed(float inp){
    motorTurboSpeed = inp;
    
    if(hfCoreDebug){
        printf("[HF:Core]Set Motor Turbo Speed to %.2lf\n",motorTurboSpeed);
    }
}

float hfCore::getMotorTurboSpeed(void){
    return motorTurboSpeed;
}

//set/get hfTurboPercentage-----------------------------------------------------
void hfCore::setHfTurboPercentage(double inp){
    if ((inp <1) && (inp >=0)){
        hfTurboPercentage = inp; 
          
        if(hfCoreDebug){
            printf("[HF:Core]Set HF Turbo Percentage %.2lf\n",hfTurboPercentage);
        }
    }else{
        printf("what the FUCK you are doing? you think %.2lf is safe? are you mk max?",hfTurboPercentage);
        
        setHfTurboPercentage(0.8);
    }
}


double hfCore::getHfTurboPercentage(void){
    return hfTurboPercentage;
}

//set/get travelLength----------------------------------------------------------
void hfCore::setTravelLength(double inp){
    travelLength = abs(inp);
    
    if(hfCoreDebug){
        printf("[HF:Core]Set Travel Length to %.2lfm\n",travelLength);
    }
}

double hfCore::getTravelLength(void){
    return travelLength;
}

//set/get ReadyToChargeLength--------------------------------------------------
void hfCore::setReadyToChargeLength(double inp){
    readyToChargeLength = abs(inp);
    
    if(hfCoreDebug){
        printf("[HF:Core]Set Homing To Charge Length to %.2lfm\n",readyToChargeLength);
    }
    calReadyToChargeRatio();
}

double hfCore::getReadyToChargeLength(void){
    return readyToChargeLength;
}

void hfCore::calReadyToChargeRatio(void){
    readyToChargeRatio = readyToChargeLength/travelLength;
    
    if(hfCoreDebug){
        printf("[HF:Core]Set Homing To Charge ratio to %.2lfm\n",readyToChargeLength);
    }
}


//set/get geartRatio------------------------------------------------------------
void hfCore::setGeartRatio(double inp){
    geartRatio = abs(inp);
    
    if(hfCoreDebug){
        printf("[HF:Core]Set Geart Ratio to %.2lf\n",geartRatio);
    }
}

double hfCore::getGeartRatio(void){
    return geartRatio;
}


//cal turbo Time----------------------------------------------------------------
void hfCore::calHfTurboTime(){
    //hfTurboTime = (travelLength * hfTurboPercentage * geartRatio * 60)/ (motorTurboSpeed * 0.008 * 3);
    //hfTurboTime = 0.6;
    hfTurboTime = 0.475;
    /*
    TRY TurboTime starting from 0.2!!
    */
    if(hfCoreDebug){
        printf("[HF:Core]Turbo Time %.2lf\n",hfTurboTime);
    }
}

double hfCore::getHfTurboTime(void){
    return hfTurboTime;
}

char hfCore::getCurrentLocation(void){
    return currentLocation;
}


//==============================================================================
//initialization
void hfCore::motorInitialization(void)
{
    if(hfCoreDebug){
        printf("[HF:Core]HF config: start\n");    
    }
    
    //set speed 
    action1.SetVelocity(0);
    
    //estop
    //HFestop.attach(&HFEdge, 0.05); 
    
    if(hfCoreDebug){
        printf("[HF:Core]HF config: done\n");    
    }
}

void hfCore::init(void)
{
    calHfTurboTime();
    motorInitialization();
    charge(false);
}

//homing and charge=============================================================
void hfCore::turboOff(void){
    motorMode = false;
    
    if(hfCoreDebug){
        printf("[HF:Core]turbo motor mode off\n");
    }
}

void hfCore::stopProcedure(char currentLocationInp){
    action1.SetVelocity(0);
    brake();
    isStop = true;
    turboLock =false;
    lock = false;
    currentLocation=currentLocationInp;
    if(hfCoreDebug){
        printf("[HF:Core]hf motor: stop HF, Location:%c\n",currentLocationInp); 
    }
    motorUpdater.detach();
    wait(0.001);
    motorUpdater.attach(callback(this, &hfCore::brake), 5);
}

//homing========================================================================
//attach to ticker
void hfCore::homingMotorUpdate(void)
{
    if(hfCoreDebug){
        printf("[HF:Core]Homing motor: update...\n");    
    }
    
    if (homingLimitSwitch){
        if(hfCoreDebug){
            printf("[HomingLimitSW]closed\n");
        }
        
        stopProcedure('H');
        
        if(hfCoreDebug){
            printf("[HF:Core]Homing: done\n");   
        }
    }
    
    if(!isStop){
        if (motorMode){
            action1.SetVelocity(-motorTurboSpeed);
        
            if(hfCoreDebug){
                printf("[HF:Core]Homing motor: set HF to turbo speed: %.2lf\n", -motorTurboSpeed);
            }
            
        }else{
            action1.SetVelocity(-motorSpeed);
        
            if(hfCoreDebug){
                printf("[HF:Core]Homing motor: set HF to speed: %.2lf\n", -motorSpeed);
            }
        }
    }
}

void hfCore::homing(bool turbo){
    
    //debug
    if(hfCoreDebug){
        printf("[HF:Core]Homing: start...\n");    
    }
    
    if (!lock){
        lock = true;
        //detach any runing program on the thicker
        motorUpdater.detach();
    
        isStop = false;
        wait(0.001);
    
        if ((turbo)&&(!turboLock)){
            motorMode = true;
            switch (currentLocation){
                case 'H':
                    printf("[HF:Core]are you on99?\n");
                    turboOff();
                    break;
                case 'R':
                    turboEnd.attach(callback(this, &hfCore::turboOff), hfTurboTime * (1 - readyToChargeRatio) );
                    printf("[HF:Core]turbo for %.2lfs\n", hfTurboTime * (1 - readyToChargeRatio) );
                    break;
                case 'C':
                    turboEnd.attach(callback(this, &hfCore::turboOff), hfTurboTime);
                    printf("[HF:Core]turbo for %.2lfs\n",hfTurboTime);
                    break;
                default :
                    printf("[HF:Core]you are on99\n");
                    turboOff();
            }
            
        }else{
            motorMode = false;
        }
    
        //attach with homingMotorUpdate() with 0.05s interval 
        motorUpdater.attach(callback(this, &hfCore::homingMotorUpdate), 0.05);
        
    }else{
        if(hfCoreDebug){
            printf("[HF:Core]HF in lock state\n");    
        }
    }

}


//Charge========================================================================
//attach to ticker
void hfCore::chargeMotorUpdate(void)
{
    if(hfCoreDebug){
        printf("[HF:Core]Charge motor: update...\n");    
    }
    
    if (chargeLimitSwitch){
        if(hfCoreDebug){
            printf("[HomingLimitSW]closed\n");
        }
        
        stopProcedure('C');
        
        if(hfCoreDebug){
            printf("[HF:Core]Charge: done\n");   
        }
    }
    
    
    if(!isStop){
        if (motorMode){
            action1.SetVelocity(motorTurboSpeed);
        
            if(hfCoreDebug){
                printf("[HF:Core]Charge motor: set HF to turbo speed: %.2lf\n", motorTurboSpeed);
            }
            
        }else{
            action1.SetVelocity(motorSpeed);
        
            if(hfCoreDebug){
                printf("[HF:Core]Charge motor: set HF to speed: %.2lf\n", motorSpeed);
            }
        }
    }
}

void hfCore::charge(bool turbo){
    
    //debug
    if(hfCoreDebug){
        printf("[HF:Core]Charge: start...\n");    
    }
    
    if (!lock){
        lock = true;
        //detach any runing program on the thicker
        motorUpdater.detach();
        isStop = false;
        wait(0.001);
    
        if ((turbo)&&(!turboLock)){
            motorMode = true;
            
            switch (currentLocation){
                case 'H':
                    turboEnd.attach(callback(this, &hfCore::turboOff), hfTurboTime);
                    printf("[HF:Core]turbo for %.2lfs\n",hfTurboTime);
                    break;
                case 'R':
                    turboEnd.attach(callback(this, &hfCore::turboOff), hfTurboTime * readyToChargeRatio);
                    printf("[HF:Core]turbo for %.2lfs\n",hfTurboTime * readyToChargeRatio);
                    break;
                case 'C':
                    printf("[HF:Core]are you on99?\n");
                    turboOff();
                    break;
                default :
                    printf("[HF:Core]you are on99\n");
                    turboOff();
            }
        }else{
            motorMode = false;
        }
    
        //attach with homingMotorUpdate() with 0.05s interval 
        motorUpdater.attach(callback(this, &hfCore::chargeMotorUpdate), 0.05); 
    }else{
        if(hfCoreDebug){
            printf("[HF:Core]HF in lock state\n");    
        }
    }
}


//ready=========================================================================
//attach to ticker
void hfCore::readyMotorUpdate(void)
{
    if(hfCoreDebug){
        printf("[HF:Core]Ready motor: update...\n");    
    }
    
    if (readyLimitSwitch){
        if(hfCoreDebug){
            printf("[readyLimitSW]closed\n");
        }
        
        stopProcedure('R');
        
        if(hfCoreDebug){
            printf("[HF:Core]Ready: done\n");   
        }
    }
    
    if(!isStop){
        if(currentLocation == 'H'){
            //copy from charge
            if (motorMode){
                action1.SetVelocity(motorTurboSpeed);
        
                if(hfCoreDebug){
                    printf("[HF:Core]Ready motor: set HF to turbo speed: %.2lf\n", motorTurboSpeed);
                }
            
            }else{
                action1.SetVelocity(motorSpeed);
        
                if(hfCoreDebug){
                    printf("[HF:Core]Ready motor: set HF to speed: %.2lf\n", motorSpeed);
                }
            }
        }else{
            if (motorMode){
                action1.SetVelocity(-motorTurboSpeed);
        
                if(hfCoreDebug){
                    printf("[HF:Core]Ready motor: set HF to turbo speed: %.2lf\n", -motorTurboSpeed);
                }
            
            }else{
                action1.SetVelocity(-motorSpeed);
        
                if(hfCoreDebug){
                    printf("[HF:Core]Ready motor: set HF to speed: %.2lf\n", -motorSpeed);
                }
            }
        }
    }
}

void hfCore::ready(bool turbo){
    
    //debug
    if(hfCoreDebug){
        printf("[HF:Core]Charge: start...\n");    
    }
    
    switch (currentLocation){
        case 'H':
            if(hfCoreDebug){
                printf("[HF:Core]Current location: %c\n", currentLocation);
            }
            break;
        case 'R':
            if(hfCoreDebug){
                printf("[HF:Core]Current location: %c\n", currentLocation);
            }
            break;
        case 'C':
            if(hfCoreDebug){
                printf("[HF:Core]Current location: %c\n", currentLocation);
            }
            break;
        default :
            if(hfCoreDebug){
                printf("[HF:Core]unknow location\n");
            }
            charge(true);
    }
    
        
    
    
    if (!lock){
        lock = true;
        //detach any runing program on the thicker
        motorUpdater.detach();
        isStop = false;
        wait(0.001);
    
        if ((turbo)&&(!turboLock)){
            motorMode = true;
            
            switch (currentLocation){
                case 'H':
                    turboEnd.attach(callback(this, &hfCore::turboOff), hfTurboTime * (1 - readyToChargeRatio));
                    printf("[HF:Core]turbo for %.2lfs\n",hfTurboTime * (1 - readyToChargeRatio));
                    break;
                case 'R':
                    printf("[HF:Core]are you on99?\n");
                    turboOff();
                    break;
                case 'C':
                    turboEnd.attach(callback(this, &hfCore::turboOff), hfTurboTime * readyToChargeRatio);
                    printf("[HF:Core]turbo for %.2lfs\n",hfTurboTime * readyToChargeRatio);
                    turboOff();
                    break;
                default :
                    printf("[HF:Core]you are on99\n");
                    turboOff();
            }
        }else{
            motorMode = false;
        }
    
        //attach with homingMotorUpdate() with 0.05s interval 
        motorUpdater.attach(callback(this, &hfCore::readyMotorUpdate), 0.05); 
    }else{
        if(hfCoreDebug){
            printf("[HF:Core]HF in lock state\n");    
        }
    }
}


void hfCore::vsc(float pos){
    motorUpdater.detach();
    action1.crossbow(0);
    wait(0.01);
    brake();
    motorUpdater.attach(callback(this, &hfCore::brake), 5);
}


void hfCore::brake(void){
    action1.brake(20.0);
    if(hfCoreDebug){
            printf("[HF:Core]braking state\n");    
    }
}

/*
void hfCore::brake(float inp){
    action1.brake(abs(inp));
}
*/

