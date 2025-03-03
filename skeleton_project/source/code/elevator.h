#pragma once
#include <stdbool.h>
#include "../driver/elevio.h"


int floorFinderUp(int counter, int prevFloor);
int floorFinderDown(int counter, int prevFloor);

void emptyUpList();
void emptyDownList();

void goToCallUp(int counter, int prevFloor);
void goToCallDown(int counter, int prevFloor);

/*
typedef enum {
    STATE_IDLE,
    STATE_UP,
    STATE_DOWN,
    STATE_STOP,
} elevatorState;


void stop();
void move();
void openDoor();
void elevatorStateMachine();
*/