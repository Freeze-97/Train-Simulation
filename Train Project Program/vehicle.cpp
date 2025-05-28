// Tommy Yasi/toya1800
// Lok, vagn är typ av fordon
// Funktionsdefinitioner

#include "vehicle.h"

Vehicle::Vehicle(int pIdNum, string pType) {
    idNum = pIdNum;
    type = move(pType);
}

Vehicle::Vehicle() {
    idNum = 0;
    type = " ";
}

Vehicle::~Vehicle() = default;
