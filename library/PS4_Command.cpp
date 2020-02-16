#include "pinDefind.h"
//readable ver.

    //void init()
//    {
//        for(int i = 0; i < 19; i++)
//            CommandFlat[i] = false;  
//        StringCommand = new char[255];
//    }

    char *StringCommand;
    uint16_t CommandLength;
    bool old_CommandFlat[19];
    bool CommandFlat[19];
    uint16_t LX,LY,RX,RY,LA2,RA2; //LXLY RXRY 0-255
    float getLX(){
        return (float)LX;
        }
    float getLY(){
        return (float)LY;
        }
        
    float getRX(){
        
        return (float)RX;
        }
    float getRY(){
        
        return (float)RY;
        }
        
    void (*ps4high_func_ptr[19])() = {
        high_func_CommandChange,
        high_func_LH ,
        high_func_RH ,
        high_func_L2 ,
        high_func_R2 ,
        high_func_TRI ,
        high_func_CIR ,
        high_func_CRO,
        high_func_SQU,
        high_func_UP,
        high_func_RIGHT,
        high_func_DOWN,
        high_func_LEFT,
        high_func_L1,
        high_func_L3,
        high_func_R1,
        high_func_R3,
        high_func_SHARE,
        high_func_OPTIONS
    };
    
    void (*ps4low_func_ptr[19])() = {
        low_func_CommandChange,
        low_func_LH ,
        low_func_RH ,
        low_func_L2 ,
        low_func_R2 ,
        low_func_TRI ,
        low_func_CIR ,
        low_func_CRO,
        low_func_SQU,
        low_func_UP,
        low_func_RIGHT,
        low_func_DOWN,
        low_func_LEFT,
        low_func_L1,
        low_func_L3,
        low_func_R1,
        low_func_R3,
        low_func_SHARE,
        low_func_OPTIONS
    };
    
    void (*ps4fall_func_ptr[19])() = {
        fall_func_CommandChange,
        fall_func_LH ,
        fall_func_RH ,
        fall_func_L2 ,
        fall_func_R2 ,
        fall_func_TRI ,
        fall_func_CIR ,
        fall_func_CRO,
        fall_func_SQU,
        fall_func_UP,
        fall_func_RIGHT,
        fall_func_DOWN,
        fall_func_LEFT,
        fall_func_L1,
        fall_func_L3,
        fall_func_R1,
        fall_func_R3,
        fall_func_SHARE,
        fall_func_OPTIONS
    };
    
    void (*ps4rise_func_ptr[19])() = {
        rise_func_CommandChange,
        rise_func_LH ,
        rise_func_RH ,
        rise_func_L2 ,
        rise_func_R2 ,
        rise_func_TRI ,
        rise_func_CIR ,
        rise_func_CRO,
        rise_func_SQU,
        rise_func_UP,
        rise_func_RIGHT,
        rise_func_DOWN,
        rise_func_LEFT,
        rise_func_L1,
        rise_func_L3,
        rise_func_R1,
        rise_func_R3,
        rise_func_SHARE,
        rise_func_OPTIONS
    };


    
    uint16_t char2dec(char a,char b, char c)
    {
        return (a & 0x0F)*100 + (b & 0x0F)*10 + (c & 0x0F);
    }
    
    void SetCommand(char InputCommand[],uint16_t limit)
    {
        delete StringCommand;
        StringCommand =  new char[255];
        for(int i = 0; i < limit; i++)
            StringCommand[i] = InputCommand[i];
        CommandFlat[CommandChange] = true;
        CommandLength = limit;
        
    }
    
    void SetFlat()
    {
        
        for(int i = 0;i<19;i++)
        {
            old_CommandFlat[i] = CommandFlat[i];
            CommandFlat[i] = false;
        }
            
            
        for(int i = 0;i < CommandLength ; i++)
        {
            switch(StringCommand[i])
            {
                case 'L':
                    switch(StringCommand[i+1])
                    {
                        case '1':
                            CommandFlat[L1] = true;
                        break;
                        
                        case '2':
                            CommandFlat[L2] = true;
                            LA2 = char2dec(StringCommand[i+4],StringCommand[i+5],StringCommand[i+6]);
                        break;
                        
                        case '3':
                            CommandFlat[L3] = true;
                        break;
                        
                        case 'e':
                            if(StringCommand[i+7] == 'X'){
                                LX = char2dec(StringCommand[i+10],StringCommand[i+11],StringCommand[i+12]);
                                CommandFlat[LH] = true;
                            }else if (StringCommand[i+7] == 'Y'){
                                LY = char2dec(StringCommand[i+10],StringCommand[i+11],StringCommand[i+12]);
                                CommandFlat[LH] = true;
                            }
                        break;
                        
                        case 'E':
                            if(StringCommand[i+2] == 'F')
                                CommandFlat[LEFT] = true;
                        break;
                        
                        default:
                        break;
                    }
                break;
                
                case 'R':
                    switch(StringCommand[i+1])
                    {
                        case '1':
                            CommandFlat[R1] = true;
                        break;
                        
                        case '2':
                            CommandFlat[R2] = true;
                            RA2 = char2dec(StringCommand[i+4],StringCommand[i+5],StringCommand[i+6]);
                        break;
                        
                        case '3':
                            CommandFlat[R3] = true;
                        break;
                        
                        case 'i':
                            if(StringCommand[i+8] == 'X'){
                                RX = char2dec(StringCommand[i+11],StringCommand[i+12],StringCommand[i+13]);
                                CommandFlat[RH] = true;
                            }else if (StringCommand[i+8] == 'Y'){
                                RY = char2dec(StringCommand[i+11],StringCommand[i+12],StringCommand[i+13]);
                                CommandFlat[RH] = true;
                            }
                        break;
                        
                        case 'I':
                            if(StringCommand[i+2] == 'G')
                                CommandFlat[RIGHT] = true;
                        break;
                        
                        default:
                        break;
                    }
                break;
                
                case 'U':
                    if(StringCommand[i+1] == 'P')
                        CommandFlat[UP] = true;
                break;
                
                case 'D':
                    if(StringCommand[i+1] == 'O')
                        CommandFlat[DOWN] = true;
                break;
                
                case 'T':
                    if(StringCommand[i+1] == 'R')
                        CommandFlat[TRI] = true;
                break;
                
                case 'C':
                    if(StringCommand[i+1] == 'R')
                        CommandFlat[CRO] = true;
                    else if(StringCommand[i+1] == 'I')
                        CommandFlat[CIR] = true;
                break;
                
                case 'S':
                    if(StringCommand[i+1] == 'Q')
                        CommandFlat[SQU] = true;
                    else if (StringCommand[i+1] == 'H')
                        CommandFlat[SHARE] = true;
                break;
                
                case 'O':
                    if(StringCommand[i+1] == 'P')
                        CommandFlat[OPTIONS] = true;
                break;
                
                default:
                break;
            }
        }
    }
    void checkFlatLoop()
    {
        if(CommandFlat[CommandChange] != old_CommandFlat[CommandChange] || CommandFlat[CommandChange])
            SetFlat();
        
        for(int i = 0; i < 19; i++)
        {
            if(CommandFlat[i] && !old_CommandFlat[i])
                (*ps4rise_func_ptr[i])();
            if(!CommandFlat[i] && old_CommandFlat[i])
                (*ps4fall_func_ptr[i])(); 
            if(CommandFlat[i])
                (*ps4high_func_ptr[i])();
            if(!CommandFlat[i])
                (*ps4low_func_ptr[i])();
            
            
        }
    }
    
    

    
    







