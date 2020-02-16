#include "mbed.h"
#include "common.h"

class DebugClass : public Serial {  
    public:
        DebugClass(PinName tx, PinName rx);
        void printLocation(int counter, struct position curPoint, struct position curVelocity);
        void printPath(struct pointInfo *path, int maxPoint);
        void printPID(struct position p, struct position i, struct position d);
};




