#include "startPhase.h"
#include "../driver/elevio.h"

void startup(){
    elevio_init();
    while(elevio_floorSensor()!=1){
        elevio_motorDirection(DIRN_UP);   
    }
}