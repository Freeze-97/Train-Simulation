// Tommy Yasi/toya1800
// Header för vagn, det finns  olika typer av vagnar
//

#ifndef PROJECT_OB_CARRIAGE_H
#define PROJECT_OB_CARRIAGE_H

#include "vehicle.h"

class Carriage : public Vehicle {
public:
    Carriage(int pIdNum, string pType); // Constructor
    ~Carriage() = default;

    int getIdNum() const override;
    string getType() const override;
};

#endif //PROJECT_OB_CARRIAGE_H
