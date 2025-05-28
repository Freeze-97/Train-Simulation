// Tommy Yasi/toya1800
// Definitionsfil för Lok, sedan komemr diesel och ellok att finnas
//

#include "locomotive.h"

Locomotive::Locomotive(int pIdNum, string pType, int pMaxSpeed)
  : Vehicle(pIdNum, move(pType)) {
    maxSpeed = pMaxSpeed;
}

int Locomotive::getIdNum() const {
    return Vehicle::getIdNum();
}

string Locomotive::getType() const {
    return Vehicle::getType();
}
