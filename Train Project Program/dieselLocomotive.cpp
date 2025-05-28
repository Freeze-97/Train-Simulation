// Tommy Yasi/toya1800
// Definitionsfil för Diesellok som är en typ av lok
//

#include "dieselLocomotive.h"

DieselLocomotive::DieselLocomotive(int pIdNum, int pMaxSpeed, int pFuelKm)
  : Locomotive(pIdNum, "DieselLoc", pMaxSpeed) {
    fuelKm = pFuelKm;
}

int DieselLocomotive::getMaxSpeed() const {
    return Locomotive::getMaxSpeed();
}

int DieselLocomotive::getIdNum() const {
    return Locomotive::getIdNum();
}

string DieselLocomotive::getType() const {
    return Locomotive::getType();
}
