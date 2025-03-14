#include "queue.h"
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"
#include "../driver/elevio.h"

int directionPriority = 1;

//Initsialiserer listene
int *upList[4];
int *downList[4];
int *insideList[4];


//Legger til etasjebestilling i oppverlisten
void addToUpList(int floor){
    *upList[floor]=1;
}

//Legger til etasjebestilling i nedoverlisten
void addToDownList(int floor){
    *downList[floor]=1;
}

//Legger til etasjebestilling i insidelisten
void addToInsideList(int floor){
    *insideList[floor]=1;
}

//Sjekker om knapper er trykket in og legger til i ønsket liste 
void listenForInput(int state){
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int buttonType = 0; buttonType < N_BUTTONS; buttonType++){
            if (elevio_callButton(floor, (ButtonType)buttonType)){
                elevio_buttonLamp(floor, buttonType, 1);
                if (buttonType == BUTTON_HALL_UP) { 
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
