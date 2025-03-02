#include <stdio.h>
#include "elevator.h"
#include "queue.h"
#include "../driver/elevio.h"


//n-cases for ned 4 etasje og opp 1 etasje
//finner ut om det er flere calls i samme retning
int floorFinderUp(){
    for(int floor=0;floor<N_FLOORS;floor++){
        if(*upList[floor]==1 && elevio_floorSensor() < 3){
            printf("Neste opp-etasje: %d\n", floor);
            return floor;
        }
    }
    return -1;
}

int floorFinderDown(){
    for(int floor=N_FLOORS-1;floor>=0;floor--){
        if(*downList[floor]==1 && elevio_floorSensor() > 0){
            printf("Neste ned-etasje: %d\n", floor);
            return floor;
        }
    }
    return -1;
}
void emptyUpList(){
    *upList[elevio_floorSensor()]=0;
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_UP, 0);
}

void emptyDownList(){ 
    *downList[elevio_floorSensor()]=0;
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_DOWN, 0);
}

void goToCallUp(){
    printf("%d finder \n", floorFinderUp());
    printf("%d sensor \n", elevio_floorSensor());

    if(floorFinderUp()>elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_UP);
    }
    else if(floorFinderUp()<elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_DOWN);
    }
}

void goToCallDown(){

    if(floorFinderDown()>elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_UP);
    }
    else if(floorFinderDown()<elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_DOWN);
    }
}

/*
void stop(){

};

void move(){
    
};

void openDoor(){

};


void elevatorStateMachine(elevatorState *change){
    switch (*change){
        case STATE_IDLE:
            *change = STATE_IDLE;
            break;
        case STATE_UP:
            *change = STATE_UP;
            break;

        case STATE_DOWN:
            *change = STATE_DOWN;
            break;
        default:
            *change = STATE_IDLE;
            break;
    }

}
    */