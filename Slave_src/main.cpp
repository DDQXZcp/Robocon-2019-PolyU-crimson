//mian v.3
//v.3 bug fix

//hf core v.6
//air core v.3
////////////////////////////////////////
#include "mbed.h"
#include "hfCore.h"
#include "string.h"
#include "airCore.h"
////////////////////////////////////////

//pin need to change later.
//airCore airt(true, PC_9,PC_8,PB_8,PC_6); //<- for STM32F103RB (TEST ONLY) 

airCore airt(true, PC_3,PC_2,PC_0,PA_4,PB_0,PC_5); //<- for STM32F446RE
//(toggleMove()[2pins], toggleC()[2pins], toggleGeorgeHold()[1pin], toggleGeorgeMove()[1pin])

////////////////////////////////////////

//ONLY enable ONE! Parameter order: (Debug mode onoff, normal speed, turbo speed)
//Turbo Time interval fixed to 0.475s in hfCore.cpp

//hfCore hft(true,0.3,0.4); //Safe speed
//hfCore(bool debug,float hfSpeed,float hfTurboSpeed, double readyToChargeLengthInp)
hfCore hft(true,0.3,0.95,0.1);  //Fastest speed. use CAREFULLY. the Speed is between 0 to 0.95.
//hfCore hft(true,0.95,0.95,0.1);  //Craziest speed.

////////////////////////////////////////

//-------Notice to Programmer----------
//if you are not fuck off of this section :P
/*
.----.
| HF ===homing=========ready=========charge
.----.
*/
//-------Notice End--------------------

////////////////////////////////////////
/*
    Charging -> VSC -> sand -> Homing -> Shoot
     C->V->A->H->F
*/

bool isVSC = false;

//TX, RX
Serial usbDebug(USBTX, USBRX); // <- Serial Testing
//Serial  Gsam(PC_10, PC_11); //not used
//Serial  Gsam(PA_0, PA_1);  // <- this is for the fully functional program Gboard -> WillamV2 setup.
Serial Gsam(PC_12, PD_2); //<- this is uart5. For DronDom(U1) -> WillamV2(U5) setup.

char temp; // get the input

////////////////////////////////////////

void inputInterrupter(char inp){
    switch(inp) {
        //////////////////////////////////////////////////////////////////////
        case 'H':
            hft.homing(true); //Stop at -------|----- [HF]
            break;
        case 'R':
            hft.ready(true); //Stop at -------|----- [HF]
            break;
        case 'C':
            hft.charge(true); //Stop at ------------| [HF]
            break;
        case 'F':
        /*
            if ( (airt.getMove()) && (!airt.getC()) ){
                printf("you on99 forgot to openC\n"); 
                airt.openC();
                
                //I do not think move down is needed - steve
                //airt.moveDown();
                
                //wait may be longer or shorter depend on the speed of openC (and moveDown), I am looking at you ME people. 
                //if you make this process as fast as hf then MAYBE hf no need to be this fast ;)
                wait(3);
            }
            
            printf("Fire!!!\n"); 
            hft.servoMove(); // Servo turn anticlockwise 180 degree (Fire the hole) [HF]
            
            isVSC= false;
        */
            //=================================================
            printf("Fire!!!\n"); // Servo turn anticlockwise 180 degree (Fire the hole) [HF]
            hft.servoMove();
            //=================================================
            break;
            
        case 'V':
            /*
            //sometime at home(ME:charge) cannot successfully charge (maybe design problem?
            if (hft.getCurrentLocation() == 'H'){
                hft.charge(true);
                wait(1);//actually I do not know how long should I set.....
            }
            
            printf("VSC!!!\n");
            hft.vsc(0); // Pull the trigger [HF]
            
            isVSC = true;
            */
            //=================================================
            printf("VSC!!!\n");
            hft.vsc(0); // Pull the trigger [HF]
            //=================================================
            break;
        //////////////////////////////////////////////////////////////////////
            /*
        case 'A':
            airt.fss(2); //auto clipping [S]
            break;
        case 'O':
            airt.prepareS(0.1); //(clip the shit part1) [S]
            break;
        case 'U':
            airt.holdS(2); //pick the shit up (clip the shit part2) [S]
            break;
        case 'M':
            airt.aimS(2); //prepare to shoot (clip the shit part3) [S]
            break;
        case 'P':
            airt.georgeMoveUp(); //move up george [G]
            break;
        case 'B':
            airt.georgeMoveDown(); //move down george [G]
            break;
            */
        //////////////////////////////////////////////////////////////////////
        /*
        case 'L':
            airt.toggleGeorgeHold(); // toggle hold and release george. [G] //PC_5
            break;
        */
        case 'I':
            airt.toggleGeorgeMove(); // toggle george moveup and down [G] //PB_0
            break;
        case 'X':
            airt.toggleC(); //toggle openC and closeC. [S] //PA_4 close , PC_0 open
            break;
        case 'Y':
            /*if (!airt.getMove()){
                if (hft.getCurrentLocation()!= 'C') {
                    printf("you on99 hf at wrong location\n");
                    hft.charge(true);
                    wait(1.5);//actually I do not know how long should I set.....
                }
                
                if ( !isVSC ) {
                    printf("you on99 VSC not yet charge\n");
                    hft.vsc(0);
                    wait(0.5);
                    hft.vsc(0);//just to be safe
                    wait(3);//actually I do not know how long should I set.....
                    isVSC = true;
                }
            }*/    
            airt.toggleMove(); //toggle move up and down. [S] //PC_2 up, PC_3 down
            
            break;
        //////////////////////////////////////////////////////////////////////
    }
}


void rxInterrupt() {
        while(Gsam.readable()){
            temp = Gsam.getc();
            //Gsam.printf("%c",temp);
            printf("[uArt]Input:%c\n",temp);
            inputInterrupter(temp);
        }      
}


void usbInterrupt() {
        if(usbDebug.readable()){
            temp = usbDebug.getc();
            //Gsam.printf("%c",temp);
            printf("[USB]Input:%c\n",temp);
            inputInterrupter(temp);
        }      
}

///////////////////////////////////////

int main() {
    
    //Gsam.baud(115200); //for changing the baud. not used.
    printf("ST32 Ready\n");
    wait(1);
    
    isVSC = false;
    
    airt.init(); //airCore wake
    
    hft.init(); //hfCore wake
    hft.setupServo(PC_8); //servo@hfCore wake
    
    Gsam.attach(&rxInterrupt, Serial::RxIrq); // PS4 side interrupt
    usbDebug.attach(&usbInterrupt, Serial::RxIrq); //PC side interrupt
    while(1) {
        wait(1); 
    }
}
