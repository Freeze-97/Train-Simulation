// Tommy Yasi/toya1800
// Definitionsfil för stationer
//
#include <utility>
#include "station.h"

Station::Station() {
    name = " ";
    trains = vector<Train*>();
    vehicles = vector<Vehicle*>();
}

Station::Station(string pName) {
    name = move(pName);
}

Station::~Station() {
    for(Vehicle* e: vehicles){
        delete e;
        e = nullptr;
    }
}

string Station::getStationname() const {
    return name;
}

vector<Vehicle*> Station::getVehicle() const {
    return vehicles;
}

vector<Train *> Station::getTrain() const {
    return trains;
}

void Station::addTrains(Train* pTrain) {
    trains.push_back(pTrain);
}

void Station::addVehicle(Vehicle* pVehicles) {
    vehicles.push_back(pVehicles);
    sort(vehicles.begin(), vehicles.end());
}

void Station::deleteTrains(Train *pTrains) {
    // Hitta tåget som matchar och finns den så raderas den
    auto result = find_if(trains.begin(), trains.end(),
            [pTrains] (Train* &tmpTrain) {return tmpTrain == pTrains;});
    if(result != trains.end()) {
        trains.erase(result);
    }
}

void Station::deleteVehicle(Vehicle *pVehicles) {
    auto result = find_if(vehicles.begin(), vehicles.end(),
                          [pVehicles] (Vehicle* &tmpVehicle) {return tmpVehicle == pVehicles;});
    if(result != vehicles.end()) {
        vehicles.erase(result);
    }
}

Vehicle *Station::findVehicle(string pType) {
    auto result = find_if(vehicles.begin(), vehicles.end(),
            [pType] (Vehicle* tmpVehicle) {return tmpVehicle->getType() == pType;});
    if(result != vehicles.end()) {
        return *result;
    }
    return nullptr;
}



