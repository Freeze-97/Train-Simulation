// Tommy Yasi/toya1800
// Header för Lok, sedan komemr diesel och ellok att finnas
//

#ifndef PROJECT_OB_LOCOMOTIVE_H
#define PROJECT_OB_LOCOMOTIVE_H

#include "vehicle.h"

class Locomotive : public Vehicle{
private:
    int maxSpeed;
public:
    Locomotive(int pIdNum, string pType, int pMaxSpeed);
    ~Locomotive() = default;

    int getMaxSpeed() const override {return this->maxSpeed;}
    int getIdNum() const override;
    string getType() const override;
};

#endif //PROJECT_OB_LOCOMOTIVE_H
