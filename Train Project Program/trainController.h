// Tommy Yasi/toya1800
// Headerfil för trainController som tar hand om tåg, stationer, läser från fil och skriver ut för användaren
//

#ifndef PROJECT_OB_TRAINCONTROLLER_H
#define PROJECT_OB_TRAINCONTROLLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include "vehicle.h"
#include "train.h"
#include "trainMap.h"
#include "station.h"
#include "carriage.h"
#include "peopleCarriage.h"
#include "sleepCarriage.h"
#include "openCarriage.h"
#include "closedCarriage.h"
#include "locomotive.h"
#include "dieselLocomotive.h"
#include "electricLocomotive.h"

class TrainController {
private:
    // Unika pekare används med vectorer som tidigare labb, inte säker på hur shared_ptr kan användas
    vector<unique_ptr<Vehicle>> vehicles; // Vector med unik pekare för varje fordon (Delar av tåget)
    vector<unique_ptr<Train>> trains; // Vector med unik pekare för varje tåg
    vector<unique_ptr<TrainMap>> trainMap; // Unik pekare för trainMap, alla stationer
    vector<unique_ptr<Station>> stations; // Unik pekar för varje station

    // Används för statistik i slutet av körningen
    map<Station*, int> vehicleStats;

    int logLevel;

public:
    TrainController();
    ~TrainController();

    // Filhantering
    void readTrainMapFromFile();
    void readTrainsFromFile();
    void readStationsFromFile();

    // Getfunktioner för privata medlemmarna
    vector <unique_ptr<Train>> getTrains() {return trains;}
    vector <unique_ptr<Station>> getStations() {return stations;}
    vector <unique_ptr<TrainMap>> getTrainMap() {return trainMap;}
    vector <unique_ptr<Vehicle>> getVehicles() {return vehicles;}
    map<Station*, int> getVehicleStats() {return vehicleStats;}
    string getLogLevel();


    // Utskrivning av fordon/tåg/stationer
    void printTracksClosed();
    void printVehicle(Vehicle* pVehicle);
    void printStation(Station* pStation);
    void printTrain(Train* pTrain);
    void printAllVehicles();
    void printAllStationNames();
    void printAllTrains();
    void printAllStations();
    void printStats();
    void printLogMessage(Train* &pTrain, int &pTime);

    // Konvertera från int till string
    string convertIntToString(int min);
    int convertStringtoInt(string &time);

    // Sök på stationer, tåg och fordon
    void searchStation(); // Sök genom att skriva in string
    void searchTrainByID(); // Sök på tåg genom att sktiva in tåg-ID
    void searchVehicleByID(); // Sök via fordons-id
    void searchTrainByVehicleID(); // Hitta ett tåg via ett fordons-id

    // Sätt/Get loglevel
    void setLogLevel(int pLogLevel);

    // Missingvehicle, bygga/avställa tåg osv
    map<int, string> allMissingVehicles(Train* pTrain); // Är inte säker på om detta är korrekt
    bool buildTrain(Train* pTrain);
    void dissembleTrain(Train* pTrain);

    // Räkna antal fordon i början
    void countVehiclesFromStart();
};


#endif //PROJECT_OB_TRAINCONTROLLER_H
