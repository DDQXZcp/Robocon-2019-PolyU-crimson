#include "mbed.h"

class SlaveBoard : public Serial {
    private:
        
    public:
        SlaveBoard(PinName tx, PinName rx);
        void homing();
        void readyPosition();
        void fire();
        void estop();
        void vesc();
        void charge();
        void grasp();
        void openC();
        void pick();
        void aim();
        void upG();
        void downG();
        void toggleHG();
        void toggleVG();
        void toggleVS();
        void toggleHS();
};


