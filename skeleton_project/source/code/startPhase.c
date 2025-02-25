#include "startPhase.h"
#include "../driver/elevio.h"



void startup(){
    elevio_init();
    elevio_doorOpenLamp(0);
    while(elevio_floorSensor()!=0){
        elevio_motorDirection(DIRN_DOWN);  
    }
    elevio_motorDirection(DIRN_STOP);  
}