//lib
#include "mbed.h"

class hfCore
{
    public:
        hfCore(bool debug);
        hfCore(bool debug,float hfSpeed,float hfTurboSpeed, double readyToChargeLengthInp);
        //hfCore(bool debug,float hfSpeed,float hfTurboSpeed, double turboPercentage, double length, double gearRatio);
        
        void homing(bool turbo);
        void charge(bool turbo);
        void ready(bool turbo);
        void init(void);
        
        //servo=================================================================
        void servoMove();
        void setupServo(PinName pin, double period = 0.020, double pulseWidth1 = 0.0005, double pulseWidth2 = 0.0025, double timeInterval = 1);
        void vsc(float pos);
        void brake(void);
        //void brake(float inp);
        
        void setHfCoreDebug(bool inp);
        bool getHfCoreDebug(void);
        
        float getMotorSpeed(void);
        
        float getMotorTurboSpeed(void);
        
        double getTravelLength(void);
        
        double getReadyToChargeLength(void);
        void calReadyToChargeRatio(void);
        
        //calHf time for turbo Time
        void calHfTurboTime();
        double getHfTurboTime(void);
        
        char getCurrentLocation(void);

    private:
//getter setter=================================================================
        //debug mode
        
        //using Edge limit SW for EStop(if non edge senor is persent)
        void setEdgeLimitEStop(bool inp);
        bool getEdgeLimitEStop(void);
        
        void setMotorSpeed(float inp);
        
        void setMotorTurboSpeed(float inp);
        
        void setHfTurboPercentage(double inp);
        double getHfTurboPercentage(void);
        
        void setTravelLength(double inp);
        
        void setReadyToChargeLength(double inp);
        
        void setGeartRatio(double inp);
        double getGeartRatio(void);
        
        
//variable and object===========================================================
        Timeout turboEnd;
        Ticker motorUpdater;
    
        //bebug mode flage
        bool hfCoreDebug;
        
        bool turboLock;//check if hf motor allow turbo mode, ture -> not allow turbo  
        bool lock;//lock another hf related is running 
        char currentLocation;//I hate myself, current location of the hf load 
        
        bool edgeLimitEStop;//using Edge limit SW for EStop(if non edge senor is persent)
        
        float motorSpeed;
        float motorTurboSpeed;
        bool motorMode;//true for Turbo, false for normal speed
        
        //travel Length of the hf
        double travelLength;
        double readyToChargeLength;
        double readyToChargeRatio;
        double geartRatio;
        double hfTurboPercentage;
        double hfTurboTime;
        
        //acceleration and deceleration
        int acc;
        int dec;

        //stop hf motor
        bool isStop;
        
//other function================================================================
        void motorInitialization(void);
        
        void turboOff(void);
        void stopProcedure(char currentLocationInp);
        
        void homingMotorUpdate(void);
        void chargeMotorUpdate(void);
        void readyMotorUpdate(void);
        
//servo=========================================================================
        PwmOut *servo;
        PinName pin;
        bool rcServoDebug;
        double period;
        double pulseWidth1;
        double pulseWidth2;
        double timeInterval;
};

