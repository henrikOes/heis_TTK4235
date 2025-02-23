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

    int oldFloor = elevio_floorSensor();

    int newFloor;

    MotorDirection m = DIRN_UP;

    setCurrentFloorLight(oldFloor);
    
    while(1){
        if(elevio_floorSensor()>=0){
            newFloor = elevio_floorSensor();
        }   

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }

        if (oldFloor != newFloor){printf("%i", newFloor);
            elevio_motorDirection(DIRN_STOP);
            setCurrentFloorLight(newFloor);
            elevio_doorOpenLamp(1);
            while(elevio_obstruction()){
                waitThreeSeconds();
            }
            waitThreeSeconds();
            elevio_doorOpenLamp(0);

            if(newFloor == 3){
                m = DIRN_DOWN;
            }
            if(newFloor == 0 && oldFloor == 1){
                m = DIRN_UP;
            }

            oldFloor = newFloor;
        }
        elevio_motorDirection(m);
    }  
    
    return 0;
}