#include <stdio.h>
#include "elevator.h"
#include "queue.h"
#include "../driver/elevio.h"


//n-cases for ned 4 etasje og opp 1 etasje
//finner ut om det er flere calls i samme retning
int floorFinderUp(int prevFloor){
    for(int floor=prevFloor+1;floor<N_FLOORS;floor++){
        if(*upList[floor]==1 || *downList[floor]==1 || *insideList[floor]==1){
            printf("test up %d\n", floor);
            return floor;
        }
    }
    return -1;
}

int floorFinderDown(int prevFloor){
    for(int floor=prevFloor-1;floor>=0;floor--){
        if(*upList[floor]==1 || *downList[floor]==1 || *insideList[floor]==1){
            printf("test down %d\n", floor);
            return floor;
        }
    }
    return -1;
}
void emptyList(){
    *upList[elevio_floorSensor()]=0;
    *downList[elevio_floorSensor()]=0;
    *insideList[elevio_floorSensor()]=0;
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_UP, 0);
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_CAB, 0);
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_DOWN, 0);
}

void setCurrentFloorLight(int floor){
    elevio_floorIndicator(floor);
}
