#include "mbed.h"
#include "common.h"

class ActionEncoder : public Serial {
    private:
        // Robot Parameters
        static const float encoder_2_global_angle = AE_TO_GLOBAL_W;       //encoder coordinate system + 30 degree    =>  global coordinate system
        static const float encoder_2_global_x     = AE_TO_GLOBAL_X;    //encoder to center distance  in x   (tung)
        static const float encoder_2_global_y     = AE_TO_GLOBAL_Y;    //encoder to center distance  in y   (tung)
        static const float pi = PI;
        
        float encoder_to_center;
        float encoder2local_angle;
        float encoder_position_angle;//90 +  angle to encoder location
        float r;//encoder to center radius
        Timer actionTimeout;
        
        
        union {
            uint8_t data[24];
            float val[6];
        } posture;
        int action_counter;
        int i;
        struct position tempPos, degreePos, aeReadPos, startOffset, curPos;
        int LastRead;
        bool newDataArrived;
        char buffer[8];
        
    public:
        ActionEncoder(PinName tx, PinName rx);
        bool translate(char c);
        void calculatePos(float _X, float _Y, float _A, bool start = false);
        bool curPosIsAvailable();
        struct position getCurPos();
        float getR();
};


