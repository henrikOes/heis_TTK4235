#include <stdio.h>
#include "elevator.h"
#include "queue.h"
#include "../driver/elevio.h"


//n-cases for ned 4 etasje og opp 1 etasje
//finner ut om det er flere calls i samme retning
int floorFinderUp(int counter, int prevFloor){
    int floorUp=-1;
    int floorInside=-1;
    if(counter == 0){
        for(int floor=0;floor<N_FLOORS;floor++){
            if(*upList[floor]==1 && floorUp == -1){
                floorUp=floor;
            }
        }
        for(int floor=prevFloor-1;floor==0;floor--){
            if(*insideList[floor]==1){
                floorInside=floor;
                break;
            }
        }
        if(floorInside!=-1){
            return floorInside;
        }
        else if(floorUp!=-1){
            return floorUp;
        }
    }
    else{
        for(int floor=prevFloor+1;floor<N_FLOORS;floor++){
            if(*upList[floor]==1){
                floorUp = floor;
            }
            if(*insideList[floor]==1){
                floorInside=floor;
            }
        }
        if(floorInside>=floorUp && floorUp != -1){
            return floorUp;
        }
        else if(floorInside<floorUp && floorInside!=-1){
            return floorInside;
        }
    }
    return -1;
}

int floorFinderDown(int counter, int prevFloor){
    int floordown=-1;
    int floorInside=-1;
    if(counter == 0){
        for(int floor=N_FLOORS-1;floor>=0;floor--){
            if(*downList[floor]==1){
                floordown= floor;
            }
        }
        for(int floor=prevFloor+1;floor==N_FLOORS-1;floor++){
            if(*insideList[floor]==1){
                floorInside=floor;
                break;
            }
        }
        if(floorInside!=-1){
            return floorInside;
        }
        else if(floordown!=-1){
            return floordown;
        }
    }
    else{
        for(int floor=prevFloor-1;floor>=0;floor--){
            if(*downList[floor]==1){
                floordown=floor;
            }
            if(*insideList[floor]==1){
                floorInside=floor;
            }
        }
        if(floorInside<=floordown && floordown != -1){
            return floordown;
        }
        else if(floorInside>floordown && floorInside!=-1){
            return floorInside;
        }
    }
    return -1;
}
void emptyUpList(){
    *upList[elevio_floorSensor()]=0;
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_UP, 0);
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_CAB, 0);
}

void emptyDownList(){ 
    *downList[elevio_floorSensor()]=0;
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_HALL_DOWN, 0);
    elevio_buttonLamp(elevio_floorSensor(), BUTTON_CAB, 0);
}

void goToCallUp(int counter, int prevFloor){
    printf("%d finder \n", floorFinderUp(counter,prevFloor));
    printf("%d sensor \n", elevio_floorSensor());

    if(floorFinderUp(counter,prevFloor)>elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_UP);
    }
    else if(floorFinderUp(counter,prevFloor)<elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_DOWN);
    }
}

void goToCallDown(int counter, int prevFloor){

    if(floorFinderDown(counter,prevFloor)>elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_UP);
    }
    else if(floorFinderDown(counter,prevFloor)<elevio_floorSensor() && elevio_floorSensor()!=-1){
        elevio_motorDirection(DIRN_DOWN);
    }
}

