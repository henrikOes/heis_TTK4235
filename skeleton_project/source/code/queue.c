#include "queue.h"
#include <stdio.h>

void removeFromInsideList(){
    int floor = elevio_floorSensor();
    insideList[floor] = 0;
}

void addToInsideList(int floor){
    insideList[floor] = 1;
}

void removeFromOutsideList(int directionPriority){
    int floor = elevio_floorSensor();
    if(directionPriority == 1 && floor <3){
        upList[floor] = 0;
    }
    else if(directionPriority == -1 && floor >0){
        downList[floor] = 0;
    }
}

void addToOutsideList(int floor, int direction){
    if(direction == 1){
        upList[floor] = 1;
    }
    else if (direction == -1){
        downList[floor] = 1;
    }
}

void listenForInput(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);
        }
    }
}