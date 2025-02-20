#include "elevator.h"

/*
void stop(){

};

void move(){
    
};

void openDoor(){

};
*/

void elevatorStateMachine(){
    switch (*elevatorState){
        case STATE_IDLE:

            break;
        case STATE_UP:

            break;

        case STATE_DOWN:

            break;

        case STATE_DOWN:

            break;
        default:
            *elevatorState = STATE_IDLE;
            break;
    }

}