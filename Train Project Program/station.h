// Tommy Yasi/toya1800
// Headerfil för stationer
//

#ifndef PROJECT_OB_STATION_H
#define PROJECT_OB_STATION_H

#include "vehicle.h" // Se vilka fordon som befinner sig i vilka stationer
#include "train.h"
#include <vector>
#include <algorithm>

class Train;

class Station {
private:
    string name;
    vector<Train*> trains; // Pekare för varje tåg
    vector<Vehicle*> vehicles;

public:
    Station();
    explicit Station(string pName);
    ~Station();

    // Getfunktioner
    string getStationname() const;
    vector<Vehicle*> getVehicle() const;
    vector<Train*> getTrain() const;
    Vehicle* findVehicle(string pType);

    // Lägg till och ta bort fordon/tåg
    void addTrains(Train* ptrain);
    void addVehicle(Vehicle* pVehicles);
    void deleteTrains(Train* pTrains);
    void deleteVehicle(Vehicle* pVehicles);

};

#endif //PROJECT_OB_STATION_H
