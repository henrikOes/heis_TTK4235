#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include "../driver/elevio.h"

/*
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

extern ElevatorButtons elevatorButtons;


typedef struct { //struct for hver bestiling fra utsiden
  int direction; 
  int floorNumber;
} orderFromOutside;

typedef struct Node{ //Lenket liste for utsiden
  orderFromOutside order;
  struct Node *next; 
} Node_t;

void removeFromInsideList();

void addToInsideList(int targetFloor);

void removeFromOutsideList(Node_t **head);

void addToOutsideList(Node_t **head, int floorNumber, ButtonType b);

void listenForInput();
*/



