#pragma once

extern int directionPriority;

extern int *upList[4];
extern int *downList[4];
extern int *insideList[4];

void addToUpList(int floor);

void addToDownList(int floor);

void addToInsideList(int floor);

void listenForInput(int state);
