#include "lightPanel.h"
#include "../driver/elevio.h"


void setCurrentFloorLight(){
    elevio_floorIndicator(elevio_floorSensor());
}

void testLights(){
    int floor = elevio_floorSensor();
    printf("%i", floor);

    while(1){
        if(floor != 2){
            elevio_motorDirection(DIRN_UP);
        }
        floor = elevio_floorSensor();
        printf("%i", floor);
        elevio_motorDirection(DIRN_STOP);
        elevio_floorIndicator(floor);
        elevio_doorOpenLamp(floor);
    }
}