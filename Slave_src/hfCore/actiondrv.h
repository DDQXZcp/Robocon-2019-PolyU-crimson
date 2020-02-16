#include "mbed.h"

class actionDrv
{
public:    
    actionDrv(int hfIdInp, int bowIdInp);
    void SetOperationalMode();
    void Enable();
    void Configvelocity(int acc, int dec);
    //void SetVelocity(int vel); //rip
    void SetVelocity_mod(int vel);  //added
    void send(char* msg);
    void send_mod(char* msg);  //added
    void SetHeartBeat(int interval); //added
    void stop();
    
    void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index);
    bool sendPacket(uint32_t id, uint8_t packet[], int32_t len);
    void SetVelocity(float duty);
    void crossbow(float pos);
    void brake(float brake_current);
    
    int hfId, bowId;
    long unsigned int rxId;
    unsigned char rxBuf[8];
    char msgString[128];
    char display_buffer[8];
    
};

