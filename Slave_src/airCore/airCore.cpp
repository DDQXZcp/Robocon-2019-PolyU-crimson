//version 5.0 19/6/2019
//state : not tested 
//v5 added cylinder, pusher
//v4 getter update
//v3.0 george , toggle FEATURE AND prepare()
//v2.0 lock 

#include "airCore.h"
//              Charge, Release 

/*
//construstor
airCore::airCore(bool debug, PinName pin1, PinName pin2, PinName pin3, PinName pin4, PinName pin5, PinName pin6, PinName pin7, PinName pin8, PinName pin9, PinName pin10) {
	printf("[airCore]configing...\n");
	airCoreDebug = debug;
	rotationalC = new Relay(pin1, pin2);
	linearC = new Relay(pin3, pin4);
	lock = true;

	george = new Relay(pin5, pin6);
	georgeLock = false;

	cylinder = new Relay(pin7, pin8);
	pusher = new Relay(pin9, pin10);
}

// minimal relay
airCore::airCore(bool debug, PinName VS1, PinName HS1, PinName HS2, PinName NC, PinName VG) {
	printf("[airCore]configing...\n");
	airCoreDebug = debug;
	rotationalC = new Relay(VS1);
	linearC = new Relay(HS1,HS2);
	lock = true;

	//typed NC because there is no pin assigned
	george = new Relay(NC,VG);
	georgeLock = false;
}
*/
//(v4.0)
//(toggleMove()[2pins], toggleC()[2pins], toggleGeorgeHold()[1pin], toggleGeorgeMove()[1pin])
airCore::airCore(bool debug, PinName pin1, PinName pin2, PinName pin3, PinName pin4, PinName pin5, PinName pin6) {
	printf("[airCore]configing...\n");
	airCoreDebug = debug;
	rotationalC = new Relay(pin1, pin2);
	linearC = new Relay(pin3, pin4);
	lock = true;

	george = new Relay(pin5, pin6);
	georgeLock = false;
}


//set flag
void airCore::setAirCoreDebug(bool inp) {
	airCoreDebug = inp;
	if (inp) {
		printf("[airCore]debug:ON\n");
	}
	else {
		printf("[airCore]debug:OFF\n");
	}
}

bool airCore::getAirCoreDebug(void) {
	return airCoreDebug;
}

//shit==========================================================
//basic movements
void airCore::openC(void) {
	linearC->offRelease();
	wait(0.1);
	linearC->onCharge();
	wait(0.1);

	linearState = true;

	if (airCoreDebug) {
		printf("[airCore]OpenC\n");
	}

}

void airCore::closeC(void) {
	linearC->offCharge();
	wait(0.1);
	linearC->onRelease();
	wait(0.1);

	linearState = false;

	if (airCoreDebug) {
		printf("[airCore]CloseC\n");
	}
}

void airCore::toggleC(void) {
	if (linearState) {
		closeC();
	}
	else {
		openC();
	}
}

bool airCore::getC(void){
	return linearState;
}


void airCore::moveUp(void) {
	rotationalC->offRelease();
	wait(0.1);
	rotationalC->onCharge();
	wait(0.1);

	rotationalState = true;

	if (airCoreDebug) {
		printf("[airCore]Move up\n");
	}
}

void airCore::moveDown(void) {
	rotationalC->offCharge();
	wait(0.1);
	rotationalC->onRelease();
	wait(0.1);

	rotationalState = false;

	if (airCoreDebug) {
		printf("[airCore]Move down\n");
	}
}

void airCore::toggleMove(void) {
	if (rotationalState) {
		moveDown();
	}
	else {
		moveUp();
	}
}

bool airCore::getMove(void){
	return 	rotationalState;
}


//pro. s** movements
void airCore::init(void) {
	if (airCoreDebug) {
		printf("[airCore]init: start\n");
	}

	//Shit Init
	moveUp();
	closeC();

	//George Init
	georgeMoveUp();
	georgeHold();

	if (airCoreDebug) {
		printf("[airCore]init: end\n");
	}

	lock = false;
}

////////////////////////////////////////////Path Auto
void airCore::fss(float time) {
	if (lock) {

		printf("[airCore]ERROR:some else is running\n");

	}
	else {
		lock = true;

		if (airCoreDebug) {
			printf("[airCore]fullSequenceShit: start\n");
		}

		////////////////////////
		//hold s*** and move up
		openC(); // init
		wait(time / 2);


		////////////////////////
		closeC(); // hold the shit
		wait(time * 2);
		moveUp(); //rise the shit
		wait(time);

		//open and close
		openC();
		wait(time / 2);
		closeC();
		wait(time / 2);

		/////////////////////////
		openC();
		wait(time * 2);
		//back to ready
		moveDown();
		wait(time);
		closeC(); //back to init

		if (airCoreDebug) {
			printf("[airCore]fullSequence: end\n");
		}

		lock = false;

	}
}

////////////////////////////////////////////Path Semi-Auto
void airCore::prepareS(float time) {
	if (lock) {

		printf("[airCore]ERROR:some else is running\n");

	}
	else {
		lock = true;

		openC();
		wait(time);

		lock = false;
	}
}

void airCore::holdS(float time) {
	if (lock) {

		printf("[airCore]ERROR:some else is running\n");

	}
	else {
		lock = true;

		closeC(); // hold the shit
		wait(time * 2);
		moveUp(); //rise the shit
		wait(time);

		openC();
		wait(time / 2);
		closeC();
		wait(time / 2);

		lock = false;
	}
}

void airCore::aimS(float time) {

	if (lock) {

		printf("[airCore]ERROR:some else is running\n");

	}
	else {
		lock = true;

		openC();
		wait(time * 2);
		moveDown(); //back to ready
		wait(time);
		closeC(); //back to init

		lock = false;
	}
}

//george========================================================================
//basic movement
void airCore::georgeMoveUp(void) {
	if (georgeLock) {

		printf("[airCore]George said:some else is running\n");

	}
	else {
		georgeLock = true;

		george->onCharge();
		wait(0.1);

		georgeMoveState = true;

		georgeLock = false;
		
		if (airCoreDebug) {
			printf("[airCore]George : Move Up\n");
		}
	}

}

void airCore::georgeMoveDown(void) {
	if (georgeLock) {

		printf("[airCore]George said:some else is running\n");

	}
	else {
		georgeLock = true;

		george->offCharge();
		wait(0.1);

		georgeMoveState = false;

		georgeLock = false;
		
		if (airCoreDebug) {
			printf("[airCore]George : Move Down\n");
		}
	}

}

void airCore::toggleGeorgeMove(void) { //toggle up and down

	if (georgeMoveState) {
		georgeMoveDown();
	}
	else {
		georgeMoveUp();
	}

}

bool airCore::getGMove(void){
	return georgeMoveState;
}


void airCore::georgeHold(void) {
	if (georgeLock) {

		printf("[airCore]George said:some else is running\n");

	}
	else {
		georgeLock = true;

		george->onRelease();
		wait(0.1);

		georgeHoldeState = true;

		georgeLock = false;
		
		if (airCoreDebug) {
			printf("[airCore]George : Hold\n");
		}
	}

}

void airCore::georgeRelease(void) {
	if (georgeLock) {

		printf("[airCore]George said:some else is running\n");

	}
	else {
		georgeLock = true;

		george->offRelease();
		wait(0.1);

		georgeHoldeState = false;

		georgeLock = false;
		
		if (airCoreDebug) {
			printf("[airCore]George : Release\n");
		}
	}

}

void airCore::toggleGeorgeHold(void) { //toggle hold and release

	if (georgeHoldeState) {
		georgeRelease();
	}
	else {
		georgeHold();
	}

}

bool airCore::getGHold(void){
	return georgeHoldeState;
}

/*
//cylinder ========================================================================
void airCore::cylinderOpen(void) {
	cylinder->offRelease();
	wait(0.1);
	cylinder->onCharge();
	wait(0.1);

	cylinderState = true;

	if (airCoreDebug) {
		printf("[airCore]Cylinder Open\n");
	}

}

void airCore::cylinderClose(void) {
	cylinder->offCharge();
	wait(0.1);
	cylinder->onRelease();
	wait(0.1);

	cylinderState = false;

	if (airCoreDebug) {
		printf("[airCore]Cylinder Close\n");
	}
}

void airCore::toggleCylinder(void) {
	if (cylinderState) {
		cylinderClose();
	}
	else {
		cylinderOpen();
	}
}

//pusher =============================================================================
void airCore::pusherOpen(void) {
	pusher->offRelease();
	wait(0.1);
	pusher->onCharge();
	wait(0.1);

	pusherState = true;

	if (airCoreDebug) {
		printf("[airCore]Pusher Up\n");
	}

}

void airCore::pusherClose(void) {
	pusher->offCharge();
	wait(0.1);
	pusher->onRelease();
	wait(0.1);

	pusherState = false;

	if (airCoreDebug) {
		printf("[airCore]Pusher Down\n");
	}
}

void airCore::togglePusher(void) {
	if (pusherState) {
		pusherClose();
	}
	else {
		pusherOpen();
	}
}
*/