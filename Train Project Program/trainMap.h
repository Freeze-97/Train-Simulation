// Tommy Yasi/toya1800
// Headerfil för trainMap
// Hanterar stationer och distans mellan dessa

#ifndef PROJECT_OB_TRAINMAP_H
#define PROJECT_OB_TRAINMAP_H

#include "station.h"
#include "train.h"

class TrainMap {
private:
    Station* stationName1;
    Station* stationName2;
    int distance;

public:
    TrainMap();
    TrainMap(Station* pStationName1, Station* pStationName2, int pDistance);
    ~TrainMap() = default;

    // Setfunktioner
    void setStationName1(Station* pStationName1);
    void setStationName2(Station* pStationName2);
    void setDistance(int pDistance);

    // Getfunktioner
    Station* getStation1() const {return stationName1;}
    Station* getStation2() const {return stationName2;}
    string getStationName1() const {return stationName1->getStationname();}
    string getStationName2() const {return stationName2->getStationname();}
    int getDistance() const {return distance;}

};

#endif //PROJECT_OB_TRAINMAP_H
