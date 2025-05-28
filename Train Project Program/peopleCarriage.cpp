// Tommy Yasi/toya1800
// Definitionsfil för personvagn som är en typ av vagn
//
#include "peopleCarriage.h"


PeopleCarriage::PeopleCarriage(int pIdNum, int pSeats, bool pInternet)
: Carriage(pIdNum, "PeopleCarriage") {
    seats = pSeats;
    internet = pInternet;
}

int PeopleCarriage::getSeats() const {
    return this->seats;
}

bool PeopleCarriage::getInternet() const {
    return this->internet;
}

int PeopleCarriage::getIdNum() const {
    return Carriage::getIdNum();
}

string PeopleCarriage::getType() const {
    return Carriage::getType();
}
