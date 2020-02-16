#include "mbed.h"
#include "actiondrv.h"

unsigned char len = 0;

DigitalOut led1(LED1);
CAN CAN0(PA_11, PA_12, 500000);

typedef enum {
   CAN_PACKET_SET_DUTY = 0,
   CAN_PACKET_SET_CURRENT,
   CAN_PACKET_SET_CURRENT_BRAKE,
   CAN_PACKET_SET_RPM,
   CAN_PACKET_SET_POS,
   CAN_PACKET_FILL_RX_BUFFER,
   CAN_PACKET_FILL_RX_BUFFER_LONG,
   CAN_PACKET_PROCESS_RX_BUFFER,
   CAN_PACKET_PROCESS_SHORT_BUFFER,
   CAN_PACKET_STATUS
} CAN_PACKET_ID;

actionDrv::actionDrv(int hfIdInp, int bowIdInp)
{
    hfId= hfIdInp;
    bowId = bowIdInp;
}

void actionDrv::send(char* msg)
{}

void actionDrv::buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) 
{
   buffer[(*index)++] = number >> 24;
   buffer[(*index)++] = number >> 16;
   buffer[(*index)++] = number >> 8;
   buffer[(*index)++] = number;
}

bool actionDrv::sendPacket(uint32_t id, uint8_t packet[], int32_t len)
{
   if (CAN0.write(CANMessage(id, (const char*)packet, sizeof(packet),CANData,CANExtended)))
   {
   
      return true;
   }
   else {
      //Serial.println("Error Sending Message...");
      return false;
   }
}

void actionDrv::crossbow(float pos) {
  int32_t send_index = 0;
  uint8_t buffer[4];
  buffer_append_int32(buffer, (int32_t)(pos * 1e6), &send_index);
  printf("[%i]VSC %.2lf\n",bowId,pos);
  sendPacket(bowId | ((uint32_t)14 << 8), buffer, send_index);   //crossbow=14
}
 
//this sh**t is 
void actionDrv::brake(float brake_current) {
  int32_t send_index = 0;
  uint8_t buffer[4];
  buffer_append_int32(buffer, (int32_t)(brake_current * 1e3), &send_index);
  printf("[%i]Set braking current %.2lfA\n",hfId,brake_current);
  sendPacket(hfId | ((uint32_t)CAN_PACKET_SET_CURRENT_BRAKE << 8), buffer, send_index);   //CAN_PACKET_SET_CURRENT_BRAKE = 2
}

void actionDrv::SetVelocity(float duty){
    if ( (duty < -0.97)||(duty > 0.97) ){
        printf("Duty cannot be less then -0.95 or larger than 0.95. MK max 1999-2019\n");
        SetVelocity(0);
    }else{
        printf("[%i]Set duty to %.2lf\n",hfId,duty);
        int32_t send_index = 0;
        uint8_t buffer[4];
        buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
        sendPacket(hfId | ((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
    }

    
}    
void actionDrv::stop(){
    SetVelocity(0);
}

