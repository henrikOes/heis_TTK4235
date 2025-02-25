#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "code/startPhase.h"
#include "driver/elevio.h"
#include "code/security.h"
#include "code/queue.h"
#include "code/lightPanel.h"

int stopButton = 0;

int main(){

    startup();

    int newFloor;

    setCurrentFloorLight(elevio_floorSensor());
    int stop=0;
    while(stop==0){
        listenForInput();
        
        if(elevio_floorSensor()==2){
            newFloor = elevio_floorSensor();
            elevio_motorDirection(DIRN_STOP);
            elevio_buttonLamp(2,BUTTON_HALL_UP,0);
            upList[2]=0;
        }   
        
        if(upList[2]==1){
            elevio_motorDirection(DIRN_UP);
        }

        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            stop=1;
        }


        
    }  
    
    return 0;
}