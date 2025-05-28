// Tommy Yasi/toya1800
// Header för ellok som är en typ av lok
//

#ifndef PROJECT_OB_ELECTRICLOCOMOTIVE_H
#define PROJECT_OB_ELECTRICLOCOMOTIVE_H

#include "locomotive.h"

class ElectricLocomotive : public Locomotive {
private:
    int effectKw;
public:
    ElectricLocomotive(int pIdNum, int pMaxSpeed, int pEffectKw);
    ~ElectricLocomotive() = default;

    int getEffectKw() const override {return this->effectKw;}
    int getIdNum() const override;
    string getType() const override;
    int getMaxSpeed() const override;
};

#endif //PROJECT_OB_ELECTRICLOCOMOTIVE_H
