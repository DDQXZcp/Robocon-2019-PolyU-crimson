#include "DebugClass.h"

DebugClass::DebugClass(PinName tx, PinName rx) : Serial(tx, rx, 115200)
{
    setbuf(stdout, NULL);
}

void DebugClass::printLocation(int counter, struct position curPoint, struct position curVelocity)
{
    printf("%d,%f,%f,%f,%f,%f,%f\n", counter, curPoint.x, curPoint.y, curPoint.w, curVelocity.x, curVelocity.y, curVelocity.w);
}

void DebugClass::printPath(struct pointInfo *path, int maxPoint)
{
    printf("path\n");
    for(int i = 0; i < maxPoint; i++)
    {
        printf("%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d\n", i, path->targetPos.x, path->targetPos.y, path->targetPos.w, path->tolerance.x, path->tolerance.y, path->tolerance.w, path->maxSpeed.x, path->maxSpeed.y, path->maxSpeed.w, path->pidOn);
        path++;
    }
    printf("e\n");
}

void DebugClass::printPID(struct position p, struct position i, struct position d)
{
    printf("PID\n");
    printf("%f,%f,%f,%f,%f,%f,%f,%f,%f\n", p.x, p.y, p.w, i.x, i.y, i.w, d.x, d.y, d.w);
    printf("e\n");
}




