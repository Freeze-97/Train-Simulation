// Tommy Yasi/toya1800
// Header för personvagn
//

#ifndef PROJECT_OB_PEOPLECARRIAGE_H
#define PROJECT_OB_PEOPLECARRIAGE_H

#include "carriage.h"

class PeopleCarriage : public Carriage {
private:
    int seats;
    bool internet;
public:
    PeopleCarriage(int pIdNum, int pSeats, bool pInternet);
    ~PeopleCarriage() = default;

    int getSeats() const override;
    bool getInternet() const override;
    int getIdNum() const override;
    string getType() const override;
};


#endif //PROJECT_OB_PEOPLECARRIAGE_H
