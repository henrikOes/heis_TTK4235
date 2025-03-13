#include "security.h"
#include "startPhase.h"
#include "queue.h"
#include "../driver/elevio.h"
#include <time.h>

extern int stopButton;

//Starter heisen på nytt
void resetElevator(){
    startup();
}

//Venter i x antall nanosekunder, kjører while loop i main for å sjekke etter bestillinger underveis
void wait(){
    nanosleep(&(struct timespec){0, 10000000}, NULL);
}

//Tømmer listene og skrur av lys, kalles etter stoppkanppen er tastet inn
void deleteOrders(){
    for(int floor=0;floor<=N_FLOORS-1;floor++){
        *upList[floor]=0;
        *downList[floor]=0;
        *insideList[floor]=0;
        elevio_buttonLamp(floor, BUTTON_HALL_UP, 0);
        elevio_buttonLamp(floor, BUTTON_CAB, 0);
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, 0);
    }
}


//Stopper heisen, tømmer listene og lukker døra 
void stopElevator(){
    elevio_motorDirection(DIRN_STOP);
    deleteOrders();
    elevio_stopLamp(1);
    if(elevio_floorSensor()!=-1){
        elevio_doorOpenLamp(1);
    }
    while (elevio_stopButton())
    {
        wait();
    }
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);
}