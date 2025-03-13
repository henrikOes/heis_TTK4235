#pragma once
#include <stdbool.h>
#include "../driver/elevio.h"


int floorFinderUp(int prevFloor);
int floorFinderDown(int prevFloor);

void emptyList();

void setCurrentFloorLight(int floor);
