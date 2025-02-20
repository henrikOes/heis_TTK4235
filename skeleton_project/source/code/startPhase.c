#include "startPhase.h"
#include "../driver/elevio.h"



void startup(){
    elevio_init();
    int test=elevio_floorSensor();
    while(test!=0){
        elevio_motorDirection(DIRN_DOWN);  
        test=elevio_floorSensor();
    }
}