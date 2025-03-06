#include "queue.h"
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"
#include "../driver/elevio.h"

int directionPriority = 1;

int *upList[4];
int *downList[4];
int *insideList[4];

void addToUpList(int floor){
    *upList[floor]=1;
}

void addToDownList(int floor){
    *downList[floor]=1;
}
void addToInsideList(int floor){
    *insideList[floor]=1;
}

void listenForInput(int state){
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
                /*else{ //Legger til i nedoverkø
                    addToList(&downList, floor);
                }*/
            }
        }
    }
}





/*
extern ElevatorButtons elevatorButtons;
void removeFromInsideList(){
    switch (elevio_floorSensor()){
        case 0:
            elevatorButtons.floorButtonOne = false;
            break;
        case 1:
            elevatorButtons.floorButtonTwo = false;
            break;
        case 2:
            elevatorButtons.floorButtonThree = false;
            break;
        case 3: 
            elevatorButtons.floorButtonFour = false;
        default:
            printf("Invalid floor sensor\n");
            return;
    }
}

void addToInsideList(int targetFloor){
    switch (targetFloor) {
        case 0:
            elevatorButtons.floorButtonOne = true;
            break;
        case 1:
            elevatorButtons.floorButtonTwo = true;
            break;
        case 2:
            elevatorButtons.floorButtonThree = true;
            break;
        case 3: 
            elevatorButtons.floorButtonFour = true;
        default:
            printf("Invalid floor button\n");
            return;
    }
};

Node_t *upList = NULL;
Node_t *downList = NULL;

void removeFromOutsideList(Node_t **head){
    int currentFloor = elevio_floorSensor();

    Node_t *current = *head;
    Node_t *prev = NULL;

    //Itererer structen
    while (current != NULL) {
        if (current->order.floorNumber == currentFloor) {
            //Om det er første i listen
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;  //Skip noden
            }
            
            free(current);  //Frigjør minne
            return;  //Bryter når noden er fjernet
        }
        prev = current;
        current = current->next;
    }

}

void addToOutsideList(Node_t **head, int floorNumber, ButtonType b){ //Tror man kan legge til flere bestillinger fra samme etsaje nå
    Node_t *newNode = malloc(sizeof(Node_t)); //Frigjør plass

    newNode->order.floorNumber = floorNumber;
    if(b == BUTTON_HALL_UP){
        newNode->order.direction = 1;
    } else {
        newNode->order.direction = -1;
    }

    newNode->next = NULL;

    if (*head == NULL) { //Setter newNode som head om den ikke eksisterer fra før
        *head = newNode;
    } else {
        Node_t *current = *head; //Ittererer frem til siste og setter next som newNode;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void listenForInput(){ //Itererer over alle knappene og lytter etter input
    for (int floor = 0; floor <4; floor++){ //Usikker på om den skal gå fra 0-3 eller 1-4
        for (int buttonType = BUTTON_HALL_UP; buttonType <= BUTTON_CAB; buttonType++){
            if (elevio_callButton(floor, (ButtonType)buttonType)){
                if(buttonType == BUTTON_CAB){ //Om input er fra innsiden legges den til
                    addToInsideList(floor);
                }
                else if (buttonType == BUTTON_HALL_UP) { //Legger til i oppoverkø
                    addToOutsideList(&upList, floor, buttonType);
                }
                else{ //Legger til i nedoverkø
                    addToOutsideList(&downList, floor, buttonType);
                }
            }
        } 
    }
}
*/
