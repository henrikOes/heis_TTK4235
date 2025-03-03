#include "queue.h"
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"
#include "../driver/elevio.h"

int directionPriority = 1;

int *upList[4];
int *downList[4];
int *insideList[4];

void removeToUpList(int floor){
    *upList[floor]=0;
    *insideList[floor]=0;
}

void removeToDownList(int floor){
    *downList[floor]=0;
    *insideList[floor]=0;
}

void addToUpList(int floor){
    *upList[floor]=1;
}

void addToDownList(int floor){
    *downList[floor]=1;
}

void addToInsideList(int floor){
    *insideList[floor]=1;
}

void listenForInput(int prevFloor){
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int buttonType = 0; buttonType < N_BUTTONS; buttonType++){
            if (elevio_callButton(floor, (ButtonType)buttonType)){
                elevio_buttonLamp(floor, buttonType, 1);
                if (buttonType == BUTTON_HALL_UP) { //Legger til i oppoverkø
                    addToUpList(floor);
                }
                else if (buttonType == BUTTON_HALL_DOWN) {
                    addToDownList(floor);
                }
                else if(buttonType == BUTTON_CAB){
                    addToInsideList(floor);
                }
            }
        }
    }
}