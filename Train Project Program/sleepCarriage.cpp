// Tommy Yasi/toya1800
// Definitionsfil för sovvagn som är en typ av vagn
//
#include "sleepCarriage.h"


SleepCarriage::SleepCarriage(int pIdNum, int pBeds)
: Carriage(pIdNum, "SleepCarriage") {
    beds = pBeds;
}

int SleepCarriage::getBeds() const {
    return this->beds;
}

int SleepCarriage::getIdNum() const {
    return Carriage::getIdNum();
}

string SleepCarriage::getType() const {
    return Carriage::getType();
}
