#include "security.h"
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
    elevio_stopLamp(1);
    if(elevio_floorSensor()!=-1){
        elevio_doorOpenLamp(1);
    }
    while (elevio_stopButton())
    {
        wait();
    }
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);
}

void startup(){
    elevio_init();
    elevio_doorOpenLamp(0);
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int buttonType = 0; buttonType < N_BUTTONS; buttonType++){
            elevio_buttonLamp(floor, buttonType, 0);
        }
    }
    while(elevio_floorSensor()!=0){
        elevio_motorDirection(DIRN_DOWN);  
    }
    elevio_motorDirection(DIRN_STOP);  
}