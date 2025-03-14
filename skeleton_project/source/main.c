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

    //Initialiserer og reserverer minne til de dynamiske listene våre
    for (int i = 0; i < 4; i++){
        upList[i] = malloc(sizeof(int));
        downList[i] = malloc(sizeof(int));
        insideList[i] = malloc(sizeof(int));
        *upList[i] = 0;
        *downList[i] = 0;
        *insideList[i] = 0;
    }

    startup();
    int nextFloor=-2; //Setter verdien -2 for å vise at vi ikke har noe next floor enda.
    int prevFloor=0;
    setCurrentFloorLight(elevio_floorSensor());
    while(1){
        int timerCounter=0;
        listenForInput(directionPriority);

        //Setter etasjen til der heisen er. Hvis heisen er mellom 2 etasjer setter vi den til forrige verdi på sensoren
        if(elevio_floorSensor()!=-1){
            prevFloor=elevio_floorSensor();
        }

        //Ankommet etasje
        if(nextFloor == elevio_floorSensor() && elevio_floorSensor()!=-1){
            elevio_motorDirection(DIRN_STOP);
            elevio_floorIndicator(nextFloor);
            emptyList();
            elevio_doorOpenLamp(1);
            //Stopper i 3 sekunder
            while(timerCounter<180){
                if(elevio_obstruction()){
                    timerCounter=0;
                }
                wait();
                listenForInput(directionPriority);
                timerCounter++;
                //Stopp knapp logikk
                if(elevio_stopButton()){
                    stopElevator();
                }
            }
            elevio_doorOpenLamp(0);
        }
        
        //Logikk for retning opp
        if (directionPriority == 1){
            if(floorFinderUp(prevFloor)!=-1){
                elevio_motorDirection(DIRN_UP);
                nextFloor = floorFinderUp(prevFloor);
            }
            if(floorFinderUp(prevFloor) == -1){
                directionPriority = -1;
            }
        }

        //Logikk for retning ned
        else if(directionPriority==-1){
            if(floorFinderDown(prevFloor)!=-1){
                elevio_motorDirection(DIRN_DOWN);
                nextFloor = floorFinderDown(prevFloor);
            }
            if(floorFinderDown(prevFloor) == -1){
                directionPriority = 1;
            }
        }

        //Setter etasjelys for den etasjen vi er i
        if(elevio_floorSensor()>=0){
            elevio_floorIndicator(elevio_floorSensor());
        }

        //Stopp knappen trykkes og funksjonen utføres
        if(elevio_stopButton()){
            stopElevator();
        }
    }  
    
    return 0;
}