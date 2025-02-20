#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef enum { //prioritert på opp eller ned
  PRIORITY_UP = 1,
  PRIORITY_DOWN = -1
} priority;

typedef struct { //Bestillinger fra innsiden
  bool floorButtonOne;
  bool floorButtonTwo;
  bool floorButtonThree;
  bool floorButtonFour;
} ElevatorButtons;

ElevatorButtons elevatorButtons = {false, false, false, false}; //Definerer global variabel

typedef struct { //struct for hver bestiling fra utsiden
  int direction; 
  int currentFloor;
} orderFromOutside;

typedef struct Node{ //Lenket liste for utsiden
  orderFromOutside order;
  struct Node *next; 
} Node_t;

void removeFromInsideList();

void addToInsideList(int targetFloor);

void listenForInput();



