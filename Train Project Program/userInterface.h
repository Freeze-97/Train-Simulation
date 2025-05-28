// Tommy Yasi/toya1800
// Headerfil för userinterface där allt mellan användare och program sker
//

#ifndef PROJECT_OB_USERINTERFACE_H
#define PROJECT_OB_USERINTERFACE_H

#include <iostream>
#include <vector>
#include "simulation.h"
#include "trainController.h"

class UserInterface{
private:
    // Alla tider
    int timeInterval, startTime, endTime;

    // Pekare
    unique_ptr<Simulation> sim;
    unique_ptr<TrainController> trainControl;

    // Menyer
    void simulationMenu();
    void logMenu();
    void trainMenu();
    void stationMenu();
    void vehicleMenu();
    void statsMenu();

    // Ändra tid
    void changeStartTime();
    void changeEndTime();
    void changeInterval();

    // Simulation ovh Event
    void startSimulation();
    void runNextInterval();
    void runNextEvent();
    void completeSimulation();

    // Ändra från string till int minutes eller tvärtom
    int convertStringtoInt(string &time);
    string convertIntToString(int min); // Samma från Traincontroller

    // Skriv ut information
    void searchTrainByID();
    void searchTrainByVehicleID();
    void printAllTrains();
    void printAllStationNames();
    void searchStation();
    void printAllStations();
    void searchVehicleById();
    void printAllVehicles();
    void printStats();

public:
    UserInterface();
    void run(); // Kör programmet
};

#endif //PROJECT_OB_USERINTERFACE_H
