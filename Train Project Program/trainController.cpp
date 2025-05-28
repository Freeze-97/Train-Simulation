// Tommy Yasi/toya1800
// Definitionsfil för trainController som tar hand om tåg, stationer, läser från fil och skriver ut för användaren
//

#include "trainController.h"

// Använder endast default constructor för TrainMap
TrainController::TrainController() = default;
TrainController::~TrainController() = default;


void TrainController::readTrainMapFromFile() {
    string tmpStationName1, tmpStationName2;
    int tmpDistance = 0;

    ifstream inFile("TrainMap.txt");
    if(inFile.is_open()){ // Öppna filen
        while(inFile){
            inFile >> tmpStationName1 >> tmpStationName2 >> tmpDistance;

            // Hitta rätt position i listan över stationer
            auto stationName1 = find_if(stations.begin(), stations.end(), [tmpStationName1](unique_ptr<Station>& station) {
                return station->getStationname() == tmpStationName1;
            }
            );

            auto stationName2 = find_if(stations.begin(), stations.end(), [tmpStationName2](unique_ptr<Station>& station) {
                return station->getStationname() == tmpStationName2;
            }
            );

            // Tilldela position i nummer
            auto station_name1 = stationName1 - stations.begin();
            auto station_name2 = stationName2 - stations.begin();

            //Ny pekare för trainMap
            unique_ptr<TrainMap> tmpTrainMap(new TrainMap(stations[station_name1].get(), stations[station_name2].get(),
                    distance));
            trainMap.push_back(tmpTrainMap); // Placera i vectorn
        }
        inFile.close(); // Stäng filen
    }
}

void TrainController::readTrainsFromFile() {
    string tmpDepStation, tmpArrStation, convertDepTime, convertArrTime;
    int tmpId = 0, tmpDepTimeInt = 0, tmpArrTimeInt = 0, tmpMaxSpeed = 0;

    ifstream inFile("Trains.txt");
    if(inFile.is_open()) { // Öppna filen
        while(inFile) {
            inFile >> tmpId >> tmpDepStation >> tmpArrStation >> convertDepTime >> convertArrTime >> tmpMaxSpeed;

            // Konvertera
            tmpDepTimeInt = convertStringtoInt(convertDepTime);
            tmpArrTimeInt = convertStringtoInt(convertArrTime);

            // Hitta positionen i vectorn stations
            auto depatureStationPosition = find_if(stations.begin(), stations.end(), [tmpDepStation](unique_ptr<Station>& station) {
                return station->getStationname() == tmpDepStation;
            }
            );

            auto arrivalStationPosition = find_if(stations.begin(), stations.end(), [tmpArrStation](unique_ptr<Station>& station) {
                return station->getStationname() == tmpArrStation;
            }
            );

            // Tilldela position i listan
            auto depStation = depatureStationPosition - stations.begin();
            auto arrStation = arrivalStationPosition - stations.begin();

            // Nytt tåg med all info
            auto tmpTrain = unique_ptr<Train>(new Train(tmpId, tmpDepTimeInt, tmpDepTimeInt,
                    0, 0, tmpMaxSpeed, stations[depStation].get(), stations[arrStation].get()));

            vector<string> typeOfVehicleList; // Fånga typerna
            while(inFile){
                int vehicleType;
                inFile >> vehicleType;
                if (vehicleType == 0){
                    tmpTrain->setTypeOfVehicle("PeopleCarriage");
                }
                else if (vehicleType == 1) {
                    tmpTrain->setTypeOfVehicle("SleepCarriage");
                }
                else if(vehicleType == 2) {
                    tmpTrain->setTypeOfVehicle("OpenCarriage");
                }
                else if(vehicleType == 3) {
                    tmpTrain->setTypeOfVehicle("ClosedCarriage");
                }
                else if(vehicleType == 4) {
                    tmpTrain->setTypeOfVehicle("ElectricLoc");
                }
                else if(vehicleType == 5) {
                    tmpTrain->setTypeOfVehicle("DieselLoc");
                }
            }
            trains.push_back(tmpTrain); // Lägg till tåg i vector
        }
    }
    inFile.close();

}

void TrainController::readStationsFromFile() {
    ifstream inFile("TrainStations.txt");
    const char DELIM = '(';
    while(inFile){
        string tmpStationName;
        getline(inFile, tmpStationName, DELIM); // Fånga namn på stationen
        Station tmpStation(tmpStationName); // Skapar station

        string vehicleInfo; // Läs innanför "( )"
        while(getline(inFile, vehicleInfo, DELIM)){
            const char DELIM_2 = ')';

            int tmpId = 0, tmpType = 0, tmpPara0 = 0, tmpPara1;
            istringstream readPara{vehicleInfo}; // Ändra så att den kan läsa in
             readPara >> tmpId >> tmpType;

            // Kolla vilken typ av fordon det är (0 - 5)
            if(tmpType == 0) {
                readPara >> tmpPara0;
                readPara >> tmpPara1;

                unique_ptr<Vehicle> tmpVehicle = unique_ptr<PeopleCarriage>(new PeopleCarriage(tmpId, tmpPara0,
                        static_cast<bool>(tmpPara1)));
                tmpStation.addVehicle(tmpVehicle.get());
                vehicles.push_back(tmpVehicle);
            }
            else if(tmpType == 1) {
                readPara >> tmpPara0;

                unique_ptr<Vehicle> tmpVehicle = unique_ptr<SleepCarriage>(new SleepCarriage(tmpId, tmpPara0));
                tmpStation.addVehicle(tmpVehicle.get());
                vehicles.push_back(tmpVehicle);
            }
            else if(tmpType == 2) {
                readPara >> tmpPara0;
                readPara >> tmpPara1;

                unique_ptr<Vehicle> tmpVehicle = unique_ptr<OpenCarriage>(new OpenCarriage(tmpId, tmpPara0, tmpPara1));
                tmpStation.addVehicle(tmpVehicle.get());
                vehicles.push_back(tmpVehicle);
            }
            else if(tmpType == 3) {
                readPara >> tmpPara0;

                unique_ptr<Vehicle> tmpVehicle = unique_ptr<ClosedCarriage>(new ClosedCarriage(tmpId, tmpPara0));
                tmpStation.addVehicle(tmpVehicle.get());
                vehicles.push_back(tmpVehicle);
            }
            else if(tmpType == 4) {
                readPara >> tmpPara0;
                readPara >> tmpPara1;

                unique_ptr<Vehicle> tmpVehicle = unique_ptr<ElectricLocomotive>(new ElectricLocomotive(tmpId, tmpPara0, tmpPara1));
                tmpStation.addVehicle(tmpVehicle.get());
                vehicles.push_back(tmpVehicle);
            }
            else if(tmpType == 5) {
                readPara >> tmpPara0;
                readPara >> tmpPara1;

                unique_ptr<Vehicle> tmpVehicle = unique_ptr<DieselLocomotive>(new DieselLocomotive(tmpId, tmpPara0, tmpPara1));
                tmpStation.addVehicle(tmpVehicle.get());
                vehicles.push_back(tmpVehicle);
            }
            stations.push_back(unique_ptr<Station>(new Station(tmpStation))); // Lägg till alla stationer
            // Lägg till station och antal fordon
            countVehiclesFromStart();
            inFile.close(); // Stäng filen
        }
    }
}

void TrainController::printTracksClosed() {
    cout << "Tracks are now closed. No more trains available." << endl;
}

void TrainController::printVehicle(Vehicle *pVehicle) {
    if(pVehicle->getType() == "PeopleCarriage"){
        cout << "--People Carriage--" << endl;
        cout << "Id: " << pVehicle->getIdNum() << " Seats: " << pVehicle->getSeats()
        << " Internet: " << pVehicle->getInternet() << endl << endl;
    }
    if(pVehicle->getType() == "SleepCarriage"){
        cout << "--Sleep Carriage--" << endl;
        cout << "Id: " << pVehicle->getIdNum() << " Beds: " << pVehicle->getBeds() << endl << endl;
    }
    if(pVehicle->getType() == "OpenCarriage") {
        cout << "--Open Carriage--" << endl;
        cout << "Id: " << pVehicle->getIdNum() << " Loading capacity: " << pVehicle->getMaxWeight() << " ton"
        << " Loading area: " << pVehicle->getArea() << endl << endl;
    }
    if(pVehicle->getType() == "ClosedCarriage"){
        cout << "--Closed Carriage--" << endl;
        cout << "Id: " << pVehicle->getIdNum() << " Load size: " << pVehicle->getLoadSize() << " (m3)"
        << endl << endl;
    }
    if(pVehicle->getType() == "ElectricLoc"){
        cout << "--Electric Locomotive--" << endl;
        cout << "Id: " << pVehicle->getIdNum() << " Max speed: " << pVehicle->getMaxSpeed()
        << " KM/H " << "Power consumption: " << pVehicle->getEffectKw() << " (KW/h)" << endl << endl;
    }
    if(pVehicle->getType() == "DieselLoc"){
        cout << "--Diesel Locomotive--" << endl;
        cout << "Id: " << pVehicle->getIdNum() << " Max speed: " << pVehicle->getMaxSpeed()
        << " Fuel consumption: " << pVehicle->getFuelKm() << " (L/h)" << endl << endl;
    }
}

void TrainController::printStation(Station *pStation) {
    cout << "Station: " << pStation->getStationname() << endl;
    cout << "Amount of trains: " << pStation->getTrain().size() << endl; // Antal tåg i vector

    for(auto e : pStation->getTrain()){ // Kolla igenom alla tåg
        cout << "Id: " << e->getTrainNum() << endl;
    }
    cout << endl << endl;

    // Gå igenon alla stationer i trainmap, använd objektet Station för att hitta namnet och distans mellan stationer
    for_each(trainMap.begin(),trainMap.end(), [pStation](unique_ptr<TrainMap> tmpTrainMap) {
        if (tmpTrainMap->getStationName1() == pStation->getStationname()
            or tmpTrainMap->getStationName2() == pStation->getStationname()) {
            cout << "Distance between " << tmpTrainMap->getStationName1()
                 << " and " << tmpTrainMap->getStationName2() << " is: " << tmpTrainMap->getDistance();
            cout << endl;
        }
        cout << endl;
    }
    );

    // Skriver ut alla fordon (id och typ)
    cout << "Amount of vehicles: " << pStation->getVehicle().size() << endl;
    for(auto e : pStation->getVehicle()) {
        cout << "Id: " << e->getIdNum()
        << " Type of vehicle: " << e->getType() << endl;
    }
    cout << endl << endl; // Extra space
}

void TrainController::printTrain(Train *pTrain) {
    cout << "Train nummer: " << pTrain->getTrainNum() << endl;

    // Skriv ut tågets tillstånd
    if(pTrain->getState() == NOT_ASSEMBLED){
        cout << "State: Not assembled." << endl;
    }
    if(pTrain->getState() == INCOMPLETE){
        cout << "State: Incomplete." << endl;
    }
    if(pTrain->getState() == ASSEMBLED){
        cout << "State: Assembled." << endl;
    }
    if(pTrain->getState() == READY){
        cout << "State: Ready." << endl;
    }
    if(pTrain->getState() == RUNNING){
        cout << "State: Running." << endl;
    }
    if(pTrain->getState() == ARRIVED){
        cout << "State: Arrived." << endl;
    }
    if(pTrain->getState() == FINISHED){
        cout << "State: Finished." << endl;
    }
    cout << endl; // Extra space

    // Skriv ut typer av fordon som tåget består av
    cout << "Type of vehicles for this train: " << endl;
    for(const auto &e : pTrain->getTypeOfVehicle()){
        cout << e << endl;
    }
    cout << endl; // Extra space

    // Skriver ut info om alla fordon
    cout << "Info on all vehicles: " << endl;
    for_each(pTrain->getVehicles().begin(), pTrain->getVehicles().end(), [this](Vehicle* tmpVehicle) {
        printVehicle(tmpVehicle);
    }
    );
    cout << endl; // Extra space

    // Skriv ut information om tåget som station, hastighet
    cout << "Depature station: " << pTrain->getDepartureStation()->getStationname() << endl;
    cout << "Arrival station: " << pTrain->getArrivalStation()->getStationname() << endl;
    cout << "Planned depature time: " << convertIntToString(pTrain->getStartTime()) << endl; // Ändra från int till string
    cout << "Planned arrival time: " << convertIntToString(pTrain->getStopTime()) << endl;

    // Planerad tid plus eventuell försening
    cout << "Real depature time: " << convertIntToString(pTrain->getStartTime() + pTrain->getStartTimeLate()) << endl;
    cout << "Real arrival time: " << convertIntToString(pTrain->getStopTime() + pTrain->getStopTimeLate()) << endl;

    // Hur försenad tåget är
    cout << "Amount of delay time from depature station: " << convertIntToString(pTrain->getStartTimeLate());
    cout << "Amount of delay time to arrival station: " << convertIntToString(pTrain->getStopTimeLate());

    // Hastighet
    cout << "Current speed: " << pTrain->getSpeed() << " (KM/H)" << endl;
    cout << "Max speed: " << pTrain->getMaxSpeed() << "(KM/H)" << endl;

    cout << endl;
}

void TrainController::printAllVehicles() {
    // "this cannot be captured in this context" så jag la till this pointer
    for_each(vehicles.begin(), vehicles.end(), [this] (unique_ptr<Vehicle> tmpVehicle){
        printVehicle(tmpVehicle.get());
    }
    );
}

void TrainController::printAllStationNames() {
    for_each(stations.begin(), stations.end(), [](unique_ptr<Station> tmpStation) {
        cout << tmpStation->getStationname() << endl;
    }
    );
}

void TrainController::printAllTrains() {
    for_each(trains.begin(), trains.end(), [this](unique_ptr<Train> tmpTrain) {
                 printTrain(tmpTrain.get());
    }
    );
}

void TrainController::printAllStations() {
    for_each(stations.begin(), stations.end(), [this](unique_ptr<Station> tmpStation) {
        printStation(tmpStation.get());
             }
             );
}


string TrainController::convertIntToString(int min) {
    string time;
    if(static_cast<double> (min)/60 > 24){
        min -= 60*24; // Om tiden överstiger 24 timmar
    }
    // Om det är under 10 timmar
    if(min/60 < 10) {
        time = "0";
        time += to_string(min/60);
    }else {
        time += to_string(min/60); // Annars bara att lägga till timmarna
    }
    time += ":"; // urskilja tim och min
    min -= ((min/60)*60); // Lämna endast kvar återstående minuter

    if(min < 10) {
        time += "0";
        time += to_string(min);
    }else {
        time += to_string(min);
    }
    return time;
}

void TrainController::searchStation() {
    cout << "Type the name of the station: " << endl;
    string searchStation;
    getline(cin, searchStation);

    // Hitta stationen, söker igenom listan med find_if
    auto it = find_if(stations.begin(), stations.end(), [searchStation] (unique_ptr<Station> tmpStation){
        string tmpStationName = tmpStation->getStationname(); // Tilldela string variabel
        return tmpStationName == searchStation;
    }
    );

    // Om den inte "pekar" på slutet som är ett tomt element
    if(it != stations.end()){
        printStation(it->get());
    } else {
        cout << "The station does not exist in this map." << endl << endl;
    }
}

void TrainController::searchTrainByID() {
    cout << "Type train-id: " << endl;
    int searchTrainId;
    cin >> searchTrainId;
    cin.get();

    // Hitta tåget
    auto it = find_if(trains.begin(), trains.end(), [searchTrainId](unique_ptr<Train> tmpTrain){
        return searchTrainId == tmpTrain->getTrainNum();
    }
    );

    // Kolla så att numret finns
    if(it != trains.end()){
        printTrain(it->get());
    } else {
        cout << "The train-id is not in the list." << endl << endl;
    }
}

void TrainController::searchVehicleByID() {
    cout << "Type vehicle-id: " << endl;
    int searchVehicleId;
    cin >> searchVehicleId;
    cin.get();

    // Hitta fordonet
    auto it = find_if(vehicles.begin(), vehicles.end(), [searchVehicleId](unique_ptr<Vehicle> tmpVehicle){
                          return searchVehicleId == tmpVehicle->getIdNum();
    }
    );

    // Kolla så att numret finns
    if(it != vehicles.end()){
        printVehicle(it->get());
    } else {
        cout << "The vehicle-id is not in the list." << endl << endl;
    }
}

void TrainController::searchTrainByVehicleID() {
    cout << "Find train by typing vehicle-id: " << endl;
    int searchVehicleId;
    cin >> searchVehicleId;
    cin.get();

    // Hitta tåget genom fordons-id, skapa två find_if
    auto it = find_if(trains.begin(), trains.end(), [searchVehicleId] (unique_ptr<Train> tmpTrain){
        // Sök igenom alla fordon
        return find_if(tmpTrain->getVehicles().begin(), tmpTrain->getVehicles().end(), [searchVehicleId](Vehicle* tmpVec){
            return searchVehicleId == tmpVec->getIdNum();
        }
        );
    }
    );

    // Kolla så att numret finns
    if(it != trains.end()){
        printTrain(it->get());
    } else {
        cout << "The id is not in the list." << endl << endl;
    }
}

map<int, string> TrainController::allMissingVehicles(Train *pTrain) {
    // Lagra namn på fordon som saknas
    map<int, string> tmpMissingVehicles;

    // För varje typ av fordon
    for(const auto &e : pTrain->getTypeOfVehicle()){
        // För varje typ av string som matchar
        int matchVehicleString = count_if(pTrain->getTypeOfVehicle().begin(), pTrain->getTypeOfVehicle().end(),
                [e] (string type) {
            return e == type;
        }
        );
        // För varje fordon som amtchar
        int matchVehicle = count_if(pTrain->getVehicles().begin(), pTrain->getVehicles().end(),
                [e] (unique_ptr<Vehicle> vehicle) {
                    return e == vehicle->getType();
        }
        );
        // Placera int och string i map tmpMissingVehicle
        int range = matchVehicleString - matchVehicle;
        tmpMissingVehicles.emplace(range, e); // Placera i mappen
    }
    return tmpMissingVehicles;
}

bool TrainController::buildTrain(Train *pTrain) {
    for(auto &e : allMissingVehicles(pTrain)){
        int index = 0;
        while(index < e.first){
            auto vehicle = pTrain->getDepartureStation()->findVehicle(e.second); // Hitta fordonet
            // Kolla Så att fordonet finns i listan
            if(vehicle != nullptr){
                pTrain->addVehicle(vehicle);
                pTrain->getDepartureStation()->deleteVehicle(vehicle); // Ta bort fordonet från depaturestation
                index++;
            }
        }
    }
    // Antal fordon och antal typer ska stämma överens
    int amountOfType = pTrain->getTypeOfVehicle().size();
    int amountOfVehicles = pTrain->getVehicles().size();
    // Returnera true om det gick att bygga tåget, annars false.
    return amountOfType == amountOfVehicles;
}

void TrainController::dissembleTrain(Train *pTrain) {
    for (auto e : pTrain->getVehicles()) {
        // Lägg till tåg i slutationen först
        pTrain->getArrivalStation()->addVehicle(pTrain->getVehicles().at(0));
        // Kompilatorn tillåter endast "pTrain->getVehicles.at(0), jag vet inte varför .at(0) måste användas
        // Eller vad den gör dock

        // Ta bort fordon
        pTrain->deleteVehicle(pTrain->getVehicles().at(0));
    }
    // Ta bort tåget från slutstationen
    pTrain->getArrivalStation()->deleteTrains(pTrain);
}

void TrainController::setLogLevel(int pLogLevel) {
    logLevel = pLogLevel;
}

string TrainController::getLogLevel() {
    if(logLevel == 1) {
        return "Low";
    } else if(logLevel == 2) {
        return "Medium";
    }
    return "High";
}

void TrainController::printStats() {
    cout << "Number of vehicles at start of simulation: " << endl;
    for(auto &e : getVehicleStats()) {
        cout << e.first->getStationname() << " = " << e.first->getVehicle().size() << endl;
    }
    cout << endl; // Extra space

    // Tåg som aldrig lämnade stationen
    cout << "Trains that never left the station: " << endl;

    // SKriv ut alla som fortfarande är kvar i startstationen
    for (auto &e : getStations()) {
        for(auto &tmpTrain : e->getTrain()){
            printTrain(tmpTrain);
        }
    }
}

void TrainController::countVehiclesFromStart() {
    vehicleStats.emplace(stations.back()->getStationname(), stations.back()->getVehicle().size());
}
int TrainController::convertStringtoInt(string &time) {
    auto splitPos = time.find(':'); // Hitta det som separerar timme och minut

    string hour = time.substr(0, splitPos);
    string min = time.substr(splitPos + 1);

    int intHour = stoi(hour); // Konvertera till int
    int intMin = stoi(min);

    return (intHour*60) + (intMin);
}

void TrainController::printLogMessage(Train* &pTrain, int &pTime) {
    cout << convertIntToString(pTime) << " Train [" << pTrain->getTrainNum() << "] "
    << "(" << pTrain->getState() << ") " << "from " << pTrain->getDepartureStation()->getStationname()
    << " " << convertIntToString(pTrain->getStartTime()) << " ("
    << convertIntToString(pTrain->getStartTimeLate()) << ") "
    << "to" << endl;
    cout << pTrain->getArrivalStation()->getStationname() << " " << convertIntToString(pTrain->getStopTime())
    << " (" << convertIntToString(pTrain->getStopTimeLate()) << ") " << "Current speed " << pTrain->getSpeed()
    << "/km " << "Max speed " << pTrain->getMaxSpeed() << "/km" << endl;
}
