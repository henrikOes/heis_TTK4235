#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "code/startPhase.h"
#include "driver/elevio.h"
#include "code/security.h"
#include "code/queue.h"
#include "code/lightPanel.h"

int main(){

    startup();

    while(1){
        
        listenForInput();

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }

    return 0;
}