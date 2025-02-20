#pragma once
#include <stdlib.h>

int floorNumber;
int direction;

typedef struct {
  int *listStart;
  size_t capacity;  
} listUp;

typedef struct {
    int *listStart;
    size_t capacity;  
} listDown;

void removeFromQueue();

void addToQueueFloor();

void addToQueueCabin();



