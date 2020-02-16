
#ifndef PS4_SERIAL_H
#define PS4_SERIAL_H

//Serial  PS(PA_9, PA_10);  // UART1 tx, rx

void PS4_SERIAL_INIT();
void PS4_Rx_interrupt();   
void PS4_send(char transmitword[], unsigned int limit);

#endif







