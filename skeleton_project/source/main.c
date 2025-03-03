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
    int deliverCounter=0;
    int nextFloor=-2; //random value that is not in the system code
    int prevFloor=0;
    setCurrentFloorLight(elevio_floorSensor());
    int stop=0;
    while(stop==0){
        listenForInput(directionPriority);
        //sjekker tilstand
        if(elevio_floorSensor()!=-1){
            prevFloor=elevio_floorSensor();
        }
        if (directionPriority == 1){
            //sjekker annkomst og om flere mål i listen
            if(nextFloor == elevio_floorSensor() && elevio_floorSensor()!=-1){
                elevio_motorDirection(DIRN_STOP);
                printf("Ankommet opp-etasje: %d\n", nextFloor);
                elevio_floorIndicator(nextFloor);
                emptyUpList();
                elevio_doorOpenLamp(1);
                waitThreeSeconds();
                deliverCounter++;
                while ((elevio_obstruction())){
                    waitThreeSeconds();
                    listenForInput(directionPriority);
                }
                elevio_doorOpenLamp(0);
                nextFloor = -2;
            }
            //kjører til mål
            else if(floorFinderUp(deliverCounter,prevFloor)!=-1){
                goToCallUp(deliverCounter,prevFloor);
                nextFloor = floorFinderUp(deliverCounter,prevFloor);
                printf("nextfloor opp ble satt til: %d\n", nextFloor);
            }
            //flipper direction hvis listen opp er tom
            if(floorFinderUp(deliverCounter,prevFloor) == -1){
                directionPriority = -1;
                deliverCounter=0;
                printf("flip to down\n");
            }
        }
        if (directionPriority == -1){
            if(nextFloor == elevio_floorSensor() && elevio_floorSensor()!= -1){
                elevio_motorDirection(DIRN_STOP);
                printf("Ankommet ned-etasje: %d\n", nextFloor);
                elevio_floorIndicator(nextFloor);
                emptyDownList();
                elevio_doorOpenLamp(1);
                waitThreeSeconds();
                deliverCounter++;
                while ((elevio_obstruction())){
                    waitThreeSeconds();
                    listenForInput(directionPriority);
                }
                elevio_doorOpenLamp(0);
                nextFloor = -2;
            }
            else if(floorFinderDown(deliverCounter,prevFloor)!=-1){
                goToCallDown(deliverCounter,prevFloor);
                nextFloor = floorFinderDown(deliverCounter,prevFloor);
                printf("nextfloor ned ble satt til: %d\n", nextFloor);
            }
            //flipper direction hvis listen ned er tom
            if(floorFinderDown(deliverCounter,prevFloor) == -1){
                directionPriority = 1;
                deliverCounter=0;
                printf("flip to up\n");
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