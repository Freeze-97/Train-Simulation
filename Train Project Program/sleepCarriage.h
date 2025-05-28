// Tommy Yasi/toya1800
// Header för sovvagn
//

#ifndef PROJECT_OB_SLEEPCARRIAGE_H
#define PROJECT_OB_SLEEPCARRIAGE_H

#include "carriage.h"

class SleepCarriage : public Carriage {
private:
    int beds;
public:
    SleepCarriage(int pIdNum, int pBeds);
    ~SleepCarriage() = default;

    int getBeds() const override;
    int getIdNum() const override;
    string getType() const override;
};

#endif //PROJECT_OB_SLEEPCARRIAGE_H
