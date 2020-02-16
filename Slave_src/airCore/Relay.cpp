#include "Relay.h"
#include "mbed.h"


//DigitalOut pin9(PC_9);
//DigitalOut pin8(PC_8); 

Relay::Relay(PinName pin1, PinName pin2)
  {
      relay1 = new DigitalOut(pin1);
      relay2 = new DigitalOut(pin2);
  }

Relay::Relay(PinName pin1)
  {
      relay1 = new DigitalOut(pin1);
  }