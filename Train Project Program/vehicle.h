// Tommy Yasi/toya1800
// Lok, vagn är typ av fordon

#ifndef PROJECT_OB_VEHICLE_H
#define PROJECT_OB_VEHICLE_H

#include <string>
#include <memory>
using namespace std;

class Vehicle {
private:
    int idNum;
    string type; // Typ av fordon
public:
    Vehicle();
    Vehicle(int pIdNum, string pType);
    ~Vehicle(); // Default destructor

    virtual int getIdNum() const {return idNum;}
    virtual string getType() const {return type;}

    virtual int getSeats() const {return 0;}
    virtual bool getInternet() const {return false;}

    virtual int getBeds() const {return 0;}

    virtual double getMaxWeight() const {return 0;}
    virtual double getArea() const {return 0;}

    virtual double getLoadSize() const {return 0;}

    virtual int getEffectKw() const {return 0;}
    virtual int getMaxSpeed() const {return 0;}

    virtual int getFuelKm() const {return 0;}
 };

#endif //PROJECT_OB_VEHICLE_H
