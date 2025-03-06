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
    int nextFloor=-2; //random value that is not in the system code
    int prevFloor=0;
    setCurrentFloorLight(elevio_floorSensor());
    int stop=0;
    int counter=0;
    while(stop==0){
        int timerCounter=0;
        printf("uplist: [%d,%d,%d,%d]\n", *upList[0],*upList[1],*upList[2],*upList[3]);
        printf("downlist: [%d,%d,%d,%d]\n", *downList[0],*downList[1],*downList[2],*downList[3]);
        printf("insidelist: [%d,%d,%d,%d]\n", *insideList[0],*insideList[1],*insideList[2],*insideList[3]);
        printf("pref floor %d\n", prevFloor);
        listenForInput(directionPriority);
        printf("%d\n", directionPriority);
        //sjekker tilstand
        if(elevio_floorSensor()!=-1){
            prevFloor=elevio_floorSensor();
        }
        if(nextFloor == elevio_floorSensor() && counter==0 && elevio_floorSensor()!=-1){
            elevio_motorDirection(DIRN_STOP);
            elevio_floorIndicator(nextFloor);
            emptyList();
            elevio_doorOpenLamp(1);
            counter=1;
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
                counter=0;
            }
            //flipper direction hvis listen opp er tom
            if(floorFinderUp(prevFloor) == -1){
                directionPriority = -1;
            }
        }

        else if(directionPriority==-1){
            if(floorFinderDown(prevFloor)!=-1){
                elevio_motorDirection(DIRN_DOWN);
                nextFloor = floorFinderDown(prevFloor);
                counter=0;
            }
            //flipper direction hvis listen ned er tom
            if(floorFinderDown(prevFloor) == -1){
                directionPriority = 1;
            }
        }

        //setter etasjelyset
        if(elevio_floorSensor()>=0){
            elevio_floorIndicator(elevio_floorSensor());
        }

        if(elevio_stopButton()){
            stopElevator();
        }
    }  
    
    return 0;
}