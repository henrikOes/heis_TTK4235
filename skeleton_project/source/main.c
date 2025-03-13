#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "code/startPhase.h"
#include "driver/elevio.h"
#include "code/security.h"
#include "code/queue.h"
#include "code/elevator.h"

int stopButton = 0;

int main(){

    for (int i = 0; i < 4; i++){
        upList[i] = malloc(sizeof(int));
        downList[i] = malloc(sizeof(int));
        insideList[i] = malloc(sizeof(int));
        *upList[i] = 0;
        *downList[i] = 0;
        *insideList[i] = 0;
    }

    startup();
    int nextFloor=-2;
    int prevFloor=0;
    setCurrentFloorLight(elevio_floorSensor());
    while(1){
        int timerCounter=0;
        listenForInput(directionPriority);
        if(elevio_floorSensor()!=-1){
            prevFloor=elevio_floorSensor();
        }
        if(nextFloor == elevio_floorSensor() && elevio_floorSensor()!=-1){
            elevio_motorDirection(DIRN_STOP);
            elevio_floorIndicator(nextFloor);
            emptyList();
            elevio_doorOpenLamp(1);
            while(timerCounter<180){
                if(elevio_obstruction()){
                    timerCounter=0;
                }
                wait();
                listenForInput(directionPriority);
                timerCounter++;
                if(elevio_stopButton()){
                    stopElevator();
                }
            }
            elevio_doorOpenLamp(0);
        }
        
        if (directionPriority == 1){
            if(floorFinderUp(prevFloor)!=-1){
                elevio_motorDirection(DIRN_UP);
                nextFloor = floorFinderUp(prevFloor);
            }
            if(floorFinderUp(prevFloor) == -1){
                directionPriority = -1;
            }
        }

        else if(directionPriority==-1){
            if(floorFinderDown(prevFloor)!=-1){
                elevio_motorDirection(DIRN_DOWN);
                nextFloor = floorFinderDown(prevFloor);
            }
            if(floorFinderDown(prevFloor) == -1){
                directionPriority = 1;
            }
        }

        if(elevio_floorSensor()>=0){
            elevio_floorIndicator(elevio_floorSensor());
        }

        if(elevio_stopButton()){
            stopElevator();
        }
    }  
    
    return 0;
}