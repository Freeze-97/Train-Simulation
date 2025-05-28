// Tommy Yasi/toya1800
// Header för öppenvagn
//

#ifndef PROJECT_OB_OPENCARRIAGE_H
#define PROJECT_OB_OPENCARRIAGE_H

#include "carriage.h"

class OpenCarriage : public Carriage {
private:
    double maxWeight; // I ton
    double area; // I Kvadrat meter
public:
    OpenCarriage(int pIdNum, double pMaxWeight, double pArea);
    ~OpenCarriage() = default;

    double getMaxWeight() const override;
    double getArea() const override;
    int getIdNum() const override;
    string getType() const override;
};

#endif //PROJECT_OB_OPENCARRIAGE_H
