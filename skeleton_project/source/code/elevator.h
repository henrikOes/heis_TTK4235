#pragma once
#include <stdbool.h>
#include "../driver/elevio.h"


int floorFinderUp(int prevFloor);
int floorFinderDown(int prevFloor);

void emptyList();

void setCurrentFloorLight(int floor);

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