#pragma once
#include <stdlib.h>
#include "../driver/elevio.h"


int directionPriority;

int upList[3] = {0, 0, 0};
int downList[3] = {0, 0, 0};
int insideList[4] = {0, 0, 0, 0};


void removeFromInsideList();

void addToInsideList(int floor);

void removeFromOutsideList(int directionPriority);

void addToOutsideList(int floor, int direction);

void listenForInput();




