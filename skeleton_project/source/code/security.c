#include "security.h"
#include "startPhase.h"
#include <time.h>

extern int stopButton;

void resetElevator(){
    startup();
}

void waitThreeSeconds(){
    nanosleep(&(struct timespec){1, 0}, NULL);
}