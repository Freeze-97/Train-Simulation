// Tommy Yasi/toya1800
// Definitionsfil för ellok som är en typ av lok
//

#include "electricLocomotive.h"

ElectricLocomotive::ElectricLocomotive(int pIdNum, int pMaxSpeed, int pEffectKw)
: Locomotive(pIdNum, "ElectricLoc", pMaxSpeed) {
    effectKw = pEffectKw;
}

int ElectricLocomotive::getIdNum() const {
    return Locomotive::getIdNum();
}

string ElectricLocomotive::getType() const {
    return Locomotive::getType();
}
int ElectricLocomotive::getMaxSpeed() const {
    return Locomotive::getMaxSpeed();
}
