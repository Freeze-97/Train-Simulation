// // Tommy Yasi/toya1800
// Tåg består av lok och vagnar
//

#ifndef PROJECT_OB_TRAIN_H
#define PROJECT_OB_TRAIN_H

#include <string>
#include "vehicle.h"
#include "station.h"
#include "simConst.h"
using namespace std;

class Train {
private:
    int trainNum; // Unikt nummer/Id
    int startTime; // Starttid
    int startTimeLate; // Om tåget är sen
    int stopTime; // Stoppttid
    int stopTimeLate; // Om tåget är sen
    int distance; // Distans mellan stationer
    int speed; // Visar hastighet, inte max
    int maxSpeed; // Maxhastighet
    trainState status; // Tågets tillstånd

    // Stationer (Från och till)
    Station* departureStation;
    Station* arrivalStation;

    vector<Vehicle*> vehicles;	// Vilka fordon som finns
    vector<string> typeOfVehicle; // Typ av fordon

public:
    Train();
    Train(int pTrainNum, int pStartTime, int pStopTime, int pDistance, int pSpeed, int pMaxSpeed,
            Station* pDepartureStation, Station* pArrivalStation);
    ~Train();

    // Setfunktioner
    void setTrainNum(int pTrainNum);
    void setStartTime(int pStartTime);
    void setStartTimeLate(int pStartTimeLate);
    void setStopTime(int pStopTime);
    void setStopTimeLate(int pstopTimeLate);
    void setDitance(int pDistance);
    void setSpeed(int pSpeed);
    void setMaxSpeed(int pMaxSpeed);
    void setTrainState(trainState pStatus); // Sätt status på tåget

    // Lägg till/ta bort fordon och tilldela typ av fordon
    void addVehicle(Vehicle* pVehicle);
    void deleteVehicle(Vehicle* pVehicle);
    void setTypeOfVehicle(string pType);


    // Getfunktioner
    int getTrainNum() const {return trainNum;}
    int getStartTime() const {return startTime;}
    int getStartTimeLate() const {return startTimeLate;}
    int getStopTime() const {return stopTime;}
    int getStopTimeLate() const {return stopTimeLate;}
    int getDistance() const {return distance;}
    int getSpeed() const {return speed;}
    int getMaxSpeed() const {return maxSpeed;}
    vector<Vehicle*> getVehicles() const {return vehicles;}
    vector<string> getTypeOfVehicle() const {return typeOfVehicle;}


    trainState getState() const {return status;}
    Station* getDepartureStation () const {return departureStation;}
    Station* getArrivalStation() const {return arrivalStation;}
};

#endif //PROJECT_OB_TRAIN_H
