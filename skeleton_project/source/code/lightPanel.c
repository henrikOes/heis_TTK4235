#include "lightPanel.h"
#include "../driver/elevio.h"

void setCurrentFloorLight(int floor){
    elevio_floorIndicator(floor);
}



