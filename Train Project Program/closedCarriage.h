// Tommy Yasi/toya1800
// Header för stängdgodsvagn
//

#ifndef PROJECT_OB_CLOSEDCARRIAGE_H
#define PROJECT_OB_CLOSEDCARRIAGE_H

#include "carriage.h"

class ClosedCarriage : public Carriage {
private:
    double loadSize; // Lastvolym i kubikmeter
public:
    ClosedCarriage(int pIdNum, double pLoadSize);
    ~ClosedCarriage() = default;

    double getLoadSize() const override;
    int getIdNum() const override;
    string getType() const override;
};


#endif //PROJECT_OB_CLOSEDCARRIAGE_H
