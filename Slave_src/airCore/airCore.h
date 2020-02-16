#include "mbed.h"
#include "Relay.h"

class airCore
{
public:
	airCore(bool debug, PinName pin1, PinName pin2, PinName pin3, PinName pin4, PinName pin5, PinName pin6, PinName pin7, PinName pin8, PinName pin9, PinName pin10);

	airCore(bool debug, PinName VS1, PinName HS1, PinName HS2, PinName NC, PinName VG);

	airCore(bool debug, PinName pin1, PinName pin2, PinName pin3, PinName pin4, PinName pin5, PinName pin6);

	void setAirCoreDebug(bool inp);
	bool getAirCoreDebug(void);

	//init
	void init(void);

	// SHIT
	void openC(void);
	void closeC(void);
	void toggleC(void);
	bool getC(void);

	void moveUp(void);
	void moveDown(void);
	void toggleMove(void);
	bool getMove(void);
	
	void fss(float time);
	void prepareS(float time);
	void holdS(float time);
	void aimS(float time);

	// George
	void georgeMoveUp(void);
	void georgeMoveDown(void);
	void toggleGeorgeMove(void);
	bool getGMove(void);

	void georgeHold(void);
	void georgeRelease(void);
	void toggleGeorgeHold(void);
	bool getGHold(void);

	//Cylinder
	void cylinderOpen(void);
	void cylinderClose(void);

	void toggleCylinder(void);

	//Pusher
	void pusherOpen(void);
	void pusherClose(void);
	void togglePusher(void);

private:
	bool airCoreDebug;
	bool lock;
	bool rotationalState;
	bool linearState;

	bool georgeLock;
	bool georgeMoveState;
	bool georgeHoldeState;

	bool cylinderState;
	bool pusherState;

	Relay *rotationalC;
	Relay *linearC;
	Relay *george;
	Relay *cylinder;
	Relay *pusher;
};

