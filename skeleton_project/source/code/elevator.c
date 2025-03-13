#include <stdio.h>
#include "elevator.h"
#include "queue.h"
#include "../driver/elevio.h"

//Leter etter etasje fra der vi er og oppover i køen, returnerer -1 om ingen funnet, etasje int ellers
int floorFinderUp(int prevFloor){
    for(int floor=prevFloor+1;floor<N_FLOORS;floor++){
        if(*upList[floor]==1 || *downList[floor]==1 || *insideList[floor]==1){
            return floor;
        }
    }
    return -1;
}

//Leter etter etasje fra der vi er og nedover i køen, returnerer -1 om ingen funnet, etasje int ellers
int floorFinderDown(int prevFloor){
    for(int floor=prevFloor-1;floor>=0;floor--){
        if(*upList[floor]==1 || *downList[floor]==1 || *insideList[floor]==1){
            return floor;
        }
    }
    return -1;
}

//Tømmer listen og lys for den etasjen vi er i 
void emptyList(){
    *upList[elevio_floorSensor()]=0;
    *downList[elevio_floorSensor()]=0;
    *insideList[elevio_floorSensor()]=0;
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_UP, 0);
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_CAB, 0);
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_DOWN, 0);
}

//Setter etasjelys på utsiden av kabinen basert på hvilken etasje vi er i
void setCurrentFloorLight(int floor){
    elevio_floorIndicator(floor);
}
