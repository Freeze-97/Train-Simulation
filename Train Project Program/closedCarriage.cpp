// Tommy Yasi/toya1800
// Definitionsfil för stängdgodssvagn som är en typ av vagn
//
#include "closedCarriage.h"

ClosedCarriage::ClosedCarriage(int pIdNum, double pLoadSize)
: Carriage(pIdNum, "ClosedCarriage") { }

double ClosedCarriage::getLoadSize() const {
    return this->loadSize;
}

int ClosedCarriage::getIdNum() const {
    return Carriage::getIdNum();
}

string ClosedCarriage::getType() const {
    return Carriage::getType();
}

