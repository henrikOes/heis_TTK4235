#pragma once

extern int directionPriority;

extern int upList[3];
extern int downList[3];
extern int insideList[4];

void removeFromInsideList();

void addToInsideList(int floor);

void removeFromOutsideList(int directionPriority);

void addToOutsideList(int floor, int direction);

void listenForInput();




