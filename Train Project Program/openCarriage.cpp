// Tommy Yasi/toya1800
// Definitionsfil för öppengodsvagn som är en typ av vagn
//
#include "openCarriage.h"


OpenCarriage::OpenCarriage(int pIdNum, double pMaxWeight, double pArea)
: Carriage(pIdNum, "OpenCarriage") {
    maxWeight = pMaxWeight;
    area = pArea;
}

double OpenCarriage::getMaxWeight() const {
    return this->maxWeight;
}

double OpenCarriage::getArea() const {
    return this->area;
}

int OpenCarriage::getIdNum() const {
    return Carriage::getIdNum();
}

string OpenCarriage::getType() const {
    return Carriage::getType();
}
