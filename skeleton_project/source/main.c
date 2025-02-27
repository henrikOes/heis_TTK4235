#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "code/startPhase.h"
#include "driver/elevio.h"
#include "code/security.h"
#include "code/queue.h"
#include "code/lightPanel.h"
#include "code/elevator.h"

int stopButton = 0;

int main(){

    for (int i = 0; i < 4; i++){
        upList[i] = malloc(sizeof(int));
        downList[i] = malloc(sizeof(int));
        *upList[i] = 0;
        *downList[i] = 0;
    }

    startup();

    int nextFloor=-2;

    setCurrentFloorLight(elevio_floorSensor());
    int stop=0;
    while(stop==0){
        listenForInput();
        

        //Dobbelsjekk logikken
        if (directionPriority == 1){
            if(nextFloor == elevio_floorSensor() && elevio_floorSensor() >= 0){
                elevio_motorDirection(DIRN_STOP);
                printf("Ankommet etasje: %d\n", nextFloor+1);
                elevio_floorIndicator(nextFloor);
                emptyUpList();
                elevio_doorOpenLamp(1);
                waitThreeSeconds();
                while ((elevio_obstruction())){
                    waitThreeSeconds();
                }
                elevio_doorOpenLamp(0);
                nextFloor = -2;
                if(floorFinderUp() == -1){
                    directionPriority = -1;
                }
            }
            else if(floorFinderUp()>elevio_floorSensor() && elevio_floorSensor() >= 0){
                goToCallUp();
                nextFloor = floorFinderUp();
                printf("nextfloor ble satt til: %d\n", nextFloor);
            }
        }
        if (directionPriority == -1){
            if(nextFloor == elevio_floorSensor() && elevio_floorSensor() >= 0){
                elevio_motorDirection(DIRN_STOP);
                printf("Ankommet etasje: %d\n", nextFloor+1);
                elevio_floorIndicator(nextFloor);
                emptyDownList();
                elevio_doorOpenLamp(1);
                waitThreeSeconds();
                while ((elevio_obstruction())){
                    waitThreeSeconds();
                }
                elevio_doorOpenLamp(0);
                nextFloor = -2;
                if(floorFinderDown() == -1){
                    directionPriority = 1;
                }
            }
            else if(floorFinderDown()<elevio_floorSensor() && elevio_floorSensor() >= 0){
                goToCallDown();
                nextFloor = floorFinderDown();
                printf("nextfloor ble satt til: %d\n", nextFloor);
            }
        }


        //setter etasjelyset
        if(elevio_floorSensor()>=0){
            elevio_floorIndicator(elevio_floorSensor());
        }

    
        


        /*
        if(elevio_floorSensor()==2){
            newFloor = elevio_floorSensor();
            elevio_motorDirection(DIRN_STOP);
            elevio_buttonLamp(2,BUTTON_HALL_UP,0);
            upList[2]=0;
        }   
        
        if(upList[2]==1){
            elevio_motorDirection(DIRN_UP);
        }

        */
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            stop=1;
        }
    


        
    }  
    
    return 0;
}