#include "mbed.h"

//DigitalOut pin9(PC_9);
//DigitalOut pin8(PC_8); 

class Relay 
{ 
private: 
    DigitalOut *relay1;
    DigitalOut *relay2;
public:
//mid-sam why do the followingg ????SOIDP Maowp urhb*WA&VGhb@(* Bn,
    Relay(PinName pin1);
    Relay(PinName pin1, PinName pin2);

       void onCharge()
    {
        *relay1 = 1;
    }
    
        void offCharge()
    {
        *relay1 = 0;
    }
    
        void onRelease()
    {
        *relay2 = 1;
    }
    
        void offRelease()
    {
        *relay2 = 0;
    }
};

