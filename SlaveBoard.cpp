#include "SlaveBoard.h"

SlaveBoard::SlaveBoard(PinName tx, PinName rx) : Serial(tx, rx){}

void SlaveBoard::homing()
{
    putc('H');
}

void SlaveBoard::readyPosition()
{
    putc('R');
}

void SlaveBoard::fire()
{
    putc('F');
}
/*
void SlaveBoard::estop()
{
    putc('E');
}
*/
void SlaveBoard::vesc()
{
    putc('V');
}

void SlaveBoard::charge()
{
    putc('C');
}
/*
void SlaveBoard::grasp()
{
    putc('A');    
}

void SlaveBoard::openC()
{
    putc('O');    
}

void SlaveBoard::pick()
{
    putc('U');    
}

void SlaveBoard::aim()
{
    putc('M');    
}

void SlaveBoard::upG()
{
    putc('P');    
}

void SlaveBoard::downG()
{
    putc('B');    
}

void SlaveBoard::toggleHG()
{
    putc('L');    
}
*/
void SlaveBoard::toggleVG()
{
    putc('I');    
}

void SlaveBoard::toggleHS()
{
    putc('X');    
}

void SlaveBoard::toggleVS()
{
    putc('Y');    
}

