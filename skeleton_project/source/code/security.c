#include "security.h"
#include "startPhase.h"
#include "queue.h"
#include "../driver/elevio.h"
#include <time.h>

extern int stopButton;

void resetElevator(){
    startup();
}

void wait(){
    nanosleep(&(struct timespec){0, 10000000}, NULL);
}

void deleteOrders(){
    for(int floor=0;floor<=N_FLOORS-1;floor++){
        *upList[floor]=0;
        *downList[floor]=0;
        *insideList[floor]=0;
        elevio_buttonLamp(floor, BUTTON_HALL_UP, 0);
        elevio_buttonLamp(floor, BUTTON_CAB, 0);
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, 0);
    }
}

void stopElevator(){
    elevio_motorDirection(DIRN_STOP);
    deleteOrders();

    printf("uplist: [%d,%d,%d,%d]\n", *upList[0],*upList[1],*upList[2],*upList[3]);
    printf("downlist: [%d,%d,%d,%d]\n", *downList[0],*downList[1],*downList[2],*downList[3]);
    printf("insidelist: [%d,%d,%d,%d]\n", *insideList[0],*insideList[1],*insideList[2],*insideList[3]);

    while (elevio_stopButton())
    {
        wait();
    }
}