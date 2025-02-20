#include "queue.h"

void removeFromQueue(){
    
};

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


void listenForInput(){ //Itererer over alle knappene og lytter etter input
    for (int floor = 0; floor <4; floor++){ //Usikker på om den skal gå fra 0-3 eller 1-4
        for (int buttonType = BUTTON_HALL_UP; buttonType < BUTTON_CAB; buttonType++){
            if (elevator_callButton(floor, buttonType == 1)){
                if(buttonType == BUTTON_CAB){ //Om input er fra innsiden legges den til
                    addToInsideList(floor);
                }
                else if (buttonType == BUTTON_HALL_UP) { //Legger til i oppoverkø
                    addToOutsideList();
                }
                else{ //Legger til i nedoverkø
                    addToOutsideList()
                }
            }
        } 
    }
}