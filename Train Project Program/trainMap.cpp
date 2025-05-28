// Tommy Yasi/toya1800
// Definitionsfil för stationer
//

#include "trainMap.h"

TrainMap::TrainMap() {
    stationName1 = nullptr;
    stationName2 = nullptr;
    distance = 0;
}

TrainMap::TrainMap(Station *pStationName1, Station *pStationName2, int pDistance) {
    stationName1 = pStationName1;
    stationName2 = pStationName2;
    distance = pDistance;
}

void TrainMap::setStationName1(Station *pStationName1) {
    stationName1 = pStationName1;
}

void TrainMap::setStationName2(Station *pStationName2) {
    stationName2 = pStationName2;
}

void TrainMap::setDistance(int pDistance) {
    distance = pDistance;
}
