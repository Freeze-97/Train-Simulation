// Tommy Yasi/toya1800
// Header för Diesellok som är en typ av lok
//

#ifndef PROJECT_OB_DIESELLOCOMOTIVE_H
#define PROJECT_OB_DIESELLOCOMOTIVE_H

#include "locomotive.h"

class DieselLocomotive : public Locomotive {
private:
    int fuelKm; // Bränsleförbrukning, Liter/KM
public:
    DieselLocomotive(int pIdNum, int pMaxSpeed, int pFuelKm);
    ~DieselLocomotive() = default;

    int getFuelKm() const override {return this->fuelKm;}
    int getMaxSpeed() const override;
    int getIdNum() const override;
    string getType() const override;
};

#endif //PROJECT_OB_DIESELLOCOMOTIVE_H
