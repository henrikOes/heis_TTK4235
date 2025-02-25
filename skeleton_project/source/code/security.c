#include "security.h"
#include "startPhase.h"
#include <time.h>

extern int stopButton;

void resetElevator(){
    startup();
}

void waitThreeSeconds(){
    nanosleep(&(struct timespec){3, 0}, NULL);
}