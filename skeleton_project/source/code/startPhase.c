#include "startPhase.h"
#include "../driver/elevio.h"


//Startup funksjonen vår. Initsialiserer heisen, skrur av alle lys og sender den til første etasje før den tar imot bestillinger.
void startup(){
    elevio_init();
    elevio_doorOpenLamp(0);
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int buttonType = 0; buttonType < N_BUTTONS; buttonType++){
            elevio_buttonLamp(floor, buttonType, 0);
        }
    }
    while(elevio_floorSensor()!=0){
        elevio_motorDirection(DIRN_DOWN);  
    }
    elevio_motorDirection(DIRN_STOP);  
}