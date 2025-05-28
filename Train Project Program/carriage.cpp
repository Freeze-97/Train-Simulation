// Tommy Yasi/toya1800
// Definitionsfil för vagn, det finns  olika typer av vagnar
//

#include "carriage.h"

Carriage::Carriage(int pIdNum, string pType) : Vehicle(pIdNum, move(pType)) { }

int Carriage::getIdNum() const {
    return Vehicle::getIdNum();
}

string Carriage::getType() const {
    return Vehicle::getType();
}
