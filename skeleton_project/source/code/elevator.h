#pragma once
#include <stdbool.h>
#include "../driver/elevio.h"


int floorFinderUp();
int floorFinderDown();

void emptyUpList();
void emptyDownList();

void goToCallUp();
void goToCallDown();

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