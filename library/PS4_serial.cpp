#include "pinDefind.h"

Serial  PS(PC_6, PC_7,115200);  // UART1 tx, rx

    
const int PS4_buffer_size = 255;
// might need to increase buffer size for high baud rates
char PS4_tx_buffer[PS4_buffer_size+1];
char PS4_rx_buffer[PS4_buffer_size+1];
unsigned int PS4_rx_in;
unsigned int PS4_tx_limit;
bool PS4_IsCommand;


void PS4_SERIAL_INIT()
{
    PS.attach(&PS4_Rx_interrupt, Serial::RxIrq);
}

void PS4_Rx_interrupt() {
    while(PS.readable())
    {

        PS4_rx_buffer[PS4_rx_in] = PS.getc();
        
        if(PS4_rx_buffer[PS4_rx_in] == '4')
        {
            if(PS4_rx_buffer[PS4_rx_in-1] == 'S')
            {
                if(PS4_rx_buffer[PS4_rx_in-2] == 'P')
                PS4_IsCommand = true;
            }
        }
        if(PS4_rx_buffer[PS4_rx_in] == 'D' && (PS4_rx_in > 2))
        {  
            if(PS4_rx_buffer[PS4_rx_in-1] == 'N')
            {
                if(PS4_rx_buffer[PS4_rx_in-2] == 'E')
                {
                    if(PS4_IsCommand)
                    {
                        //PC_send(PS4_rx_buffer,PS4_rx_in);
                        SetCommand(PS4_rx_buffer,PS4_rx_in);
                    }
                    PS4_rx_in = 0;
                    PS4_IsCommand = false;
                    return;
                }
            }
        }
        PS4_rx_in++;
        if(PS4_rx_in == PS4_buffer_size) PS4_rx_in = 0;
    }
    return;
}

void PS4_send(char transmitword[], unsigned int limit)
{
    PS4_tx_limit = limit;
    for(int i = 0; i <= PS4_tx_limit ; i++)
    {
        while (!PS.writeable());
        PS.putc(transmitword[i]);
        
    }
    PS.putc('\n');  //new line
}










