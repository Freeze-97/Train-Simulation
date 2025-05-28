// Tommy Yasi/toya1800
// Funktionsdefinition för train, som skapas av att sätta ihop lok och vagn
//
#include "train.h"

Train::Train() {
    trainNum = 0;
    startTime = 0;
    startTimeLate = 0;
    stopTime = 0;
    stopTimeLate = 0;
    distance = 0;
    speed = 0;
    maxSpeed = 0;
    status = NOT_ASSEMBLED;
    departureStation = nullptr;
    arrivalStation = nullptr;
}

Train::Train(int pTrainNum, int pStartTime, int pStopTime, int pDistance, int pSpeed, int pMaxSpeed,
             Station *pDepartureStation, Station *pArrivalStation) {
    trainNum = pTrainNum;
    startTime = pStartTime;
    startTimeLate = 0; // Om tåget är sent så ändras det senare
    stopTime = pStopTime;
    stopTimeLate = 0;
    distance = pDistance;
    speed = pSpeed;
    maxSpeed = pMaxSpeed;
    departureStation = pDepartureStation;
    arrivalStation = pArrivalStation;
    status = NOT_ASSEMBLED; // Ändras senare
}

Train::~Train() {
    vehicles.clear();
}

void Train::setTrainNum(int pTrainNum) {
    trainNum = pTrainNum;
}

void Train::setStartTime(int pStartTime) {
    startTime = pStartTime;
}

void Train::setStartTimeLate(int pStartTimeLate) {
    startTimeLate = pStartTimeLate;
}

void Train::setStopTime(int pStopTime) {
    stopTime = pStopTime;
}

void Train::setStopTimeLate(int pStopTimeLate) {
    stopTimeLate = pStopTimeLate;
}

void Train::setDitance(int pDistance) {
    distance = pDistance;
}

void Train::setSpeed(int pSpeed) {
    speed = pSpeed;
}

void Train::setMaxSpeed(int pMaxSpeed) {
    maxSpeed = pMaxSpeed;
}

void Train::setTrainState(trainState pStatus) {
    status = pStatus;
}

void Train::addVehicle(Vehicle *pVehicle) {
    vehicles.push_back(pVehicle);
}

void Train::deleteVehicle(Vehicle *pVehicle) {
    auto result = find_if(vehicles.begin(), vehicles.end(),
            [pVehicle] (Vehicle* &tmpVehicle)
            {return tmpVehicle->getIdNum() == pVehicle->getIdNum();});
    if(result != vehicles.end()) {
        vehicles.erase(result);
    }
}

void Train::setTypeOfVehicle(string pType) {
    typeOfVehicle.push_back(pType);
}
