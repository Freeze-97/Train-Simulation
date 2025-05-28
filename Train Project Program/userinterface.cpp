// Tommy Yasi/toya1800
// Definitionsfil för userinterface där allt mellan användare och program sker
//
#include "userInterface.h"

UserInterface::UserInterface() {
    timeInterval = TIME_INTERVAL;
    startTime = 0;
    endTime = SIM_TIME;
}

void UserInterface::run() {
    // Användarens val
    int choice;
    cin >> choice;

    // Alternativ för användaren
    bool go = true;
    do {
        // Utskrift till användaren
        cout << "--Start Menu--" << endl;
        cout << "1. Change start time [" << convertIntToString(startTime) << "]" << endl;
        cout << "2. Change end time [" << convertIntToString(endTime) << "]" << endl;
        cout << "3. Start simulation" << endl;
        cout << "0. Exit program" << endl;

        switch (choice) {
            case 1:
                changeStartTime();
                break;
            case 2:
                changeEndTime();
                break;
            case 3: startSimulation();
                    simulationMenu();
                    go = false;
                break;
            case 0: go = false;
                break;
            default:
                cout << "Invalid input!" << endl;
        }
    } while(go);
}

void UserInterface::changeStartTime() {
    cout << "Input time in format [hh:mm]:" << endl;
    string time;
    cin >> time;

    // Konvertera till int minuter
    startTime = convertStringtoInt(time);
}

void UserInterface::changeEndTime() {
    cout << "Input time in format [hh:mm]:" << endl;
    string time;
    cin >> time;

    // Konvertera till int minuter
    endTime = convertStringtoInt(time);
}

int UserInterface::convertStringtoInt(string &time) {
    auto splitPos = time.find(':'); // Hitta det som separerar timme och minut

    string hour = time.substr(0, splitPos);
    string min = time.substr(splitPos + 1);

    int intHour = stoi(hour); // Konvertera till int
    int intMin = stoi(min);

    return (intHour*60) + (intMin);
}

void UserInterface::startSimulation() {
    trainControl.reset(new TrainController);
    trainControl->readStationsFromFile();
    trainControl->readTrainMapFromFile();
    trainControl->readTrainsFromFile();

    // Löp igenom alla tåg för event
    for(auto &train : trainControl->getTrains()) {
        sim->scheduleEvent(new AssembleEvent(sim.get(), train.get(), trainControl.get(), train->getStartTime() - 30));
    }

    // Slutevent
    sim->scheduleEvent(new EndEvent(sim.get(), trainControl.get(), endTime));
}

void UserInterface::simulationMenu() {
    // Användarens val
    int choice;
    cin >> choice;

    // Alternativ för användaren
    bool go = true;
    do {
        cout << "--Simulation Menu :  Current time [" << convertIntToString(sim->getTime()) << "]" << endl;
        cout << "1. Change interval [" << convertIntToString(timeInterval) << "]" << endl;
        cout << "2. Run next interval" << endl;
        cout << "3. Next event" << endl;
        cout << "4. Finish (Complete simulation)" << endl;
        cout << "5. Change log level [" << trainControl->getLogLevel() << "]" << endl;
        cout << "6. Train Menu" << endl;
        cout << "7. Station Menu" << endl;
        cout << "8. Vehicle Menu" << endl;
        cout << "0 Return" << endl;

        switch (choice) {
            case 1: changeInterval();
                break;
            case 2: runNextInterval();
                break;
            case 3: runNextEvent();
                break;
            case 4: completeSimulation();
                break;
            case 5: logMenu();
                break;
            case 6: trainMenu();
                break;
            case 7: stationMenu();
                break;
            case 8: vehicleMenu();
                break;
            default:
                cout << "Invalid input" << endl;
        }
    } while(go);

}

string UserInterface::convertIntToString(int min) {
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

void UserInterface::changeInterval() {

    bool validInput = false;
    do{
        cout << "Input time interval in format [hh:mm]" << endl;
        string inputInterval;
        cin >> inputInterval;

        if(convertStringtoInt(inputInterval) >= sim->getTime()){
            cout << "The time can't exceed the endtime" << endl;
        } else {
            timeInterval = convertStringtoInt(inputInterval); // Tilldela nya intervaltiden
            validInput = true;
        }

    }while(validInput);
}

void UserInterface::runNextInterval() {
    // Om tiden är slut så börja om
    if (sim->getTime() >= endTime) {
        sim.reset(new Simulation(startTime, endTime));
        startSimulation();
    }

    // Kör nästa interval
    sim->runNextInterval(timeInterval);

    if(sim->getTime() >= endTime) {
        statsMenu();
    }
}

void UserInterface::runNextEvent() {
    // Om tiden är slut så börja om
    if (sim->getTime() >= endTime) {
        sim.reset(new Simulation(startTime, endTime));
        startSimulation();
    }

    sim->runNextEvent();
    if(sim->getTime() >= endTime) {
        statsMenu();
    }
}

void UserInterface::completeSimulation() {
    // Kör klart hela simulationen på en gång
    sim->run();

    if(sim->getTime() >= endTime) {
        statsMenu();
    }
}

void UserInterface::logMenu() {
    // Användaren väljer low, medium eller high
    bool go = true;
    do {
        cout << "Choose log level: " << endl;
        cout << "1. Low" << endl;
        cout << "2. Medium" << endl;
        cout << "3. High" << endl;
        cout << "0 Return" << endl;

        int inputLogLevel;
        cin >> inputLogLevel;

        switch (inputLogLevel) {
            case 1: trainControl->setLogLevel(inputLogLevel);
                break;
            case 2: trainControl->setLogLevel(inputLogLevel);
                break;
            case 3: trainControl->setLogLevel(inputLogLevel);
                break;
            case 0: go = false; // Bara gå tillbaka
                break;
            default: cout << "Invalid input!" << endl;
        }

    }while(go);
}

void UserInterface::trainMenu() {
    // Användaren väljer alternativ
    bool go = true;
    do {
        cout << "--Train Menu--" << endl;
        cout << "1. Search train by number" << endl;
        cout << "2. Search train by vehicle-id" << endl;
        cout << "3. Show all trains" << endl;
        cout << "4. Change log level [" << trainControl->getLogLevel() << "]" << endl;
        cout << "0. Return" << endl;

        int choice;
        cin >> choice;

        switch(choice) {
            case 1: searchTrainByID();
                break;
            case 2: searchTrainByVehicleID();
                break;
            case 3: printAllTrains();
                break;
            case 4: logMenu();
                break;
            case 0: go = false;
                break;
            default: cout << "Invalid input!" << endl;
        }
    } while(go);
}

void UserInterface::searchTrainByID() {
    // Skickar användaren till funktionen som söker efter tåget i TrainController
    trainControl->searchTrainByID();
}

void UserInterface::searchTrainByVehicleID() {
    // Samma som innan, traincontroller hanterar det
    trainControl->searchTrainByVehicleID();
}

void UserInterface::printAllTrains() {
    // Skriv ut alla tåg via traincontroller
    trainControl->printAllTrains();
}

void UserInterface::stationMenu() {
    // Användaren väljer alternativ
    bool go = true;
    do{
        cout << "--Station menu--" << endl;
        cout << "1. Show station names" << endl;
        cout << "2. Show station by name" << endl;
        cout << "3. Show all stations" << endl;
        cout << "4. Change log level [" << trainControl->getLogLevel() << "]" << endl;
        cout << "0. Return" << endl;

        int choice;
        cin >> choice;

        switch(choice) {
            case 1: printAllStationNames();
                break;
            case 2: searchStation();
                break;
            case 3: printAllStations();
                break;
            case 4: logMenu();
                break;
            case 0: go = false; // Gå tillbaka i menyn
                break;
            default: cout << "Invalid input!" << endl;
        }

    }while(go);
}

void UserInterface::printAllStationNames() {
    // Sköts av traincontroller
    trainControl->printAllStationNames();
}

void UserInterface::searchStation() {
    // Sköts av traincontroller där användaren skriver info
    trainControl->searchStation();
}

void UserInterface::printAllStations() {
    // Sköts av traincontroller som skriver specifik info om varje station
    trainControl->printAllStations();
}

void UserInterface::vehicleMenu() {
    // Användaren väljer alternativ
    bool go = true;
    do{
        cout << "--Vehicle Menu--" << endl;
        cout << "1. Show vehicle by id" << endl;
        cout << "2. Show all vehicles" << endl;
        cout << "3. Change log level [" << trainControl->getLogLevel() << "]" << endl;
        cout << "0. Return" << endl;

        int choice;
        cin >> choice;

        switch(choice) {
            case 1: searchTrainByID();
                break;
            case 2: printAllVehicles();
                break;
            case 3: logMenu();
                break;
            case 0: go = false; // Gå tillbaka i menyn
                break;
            default: cout << "Invalid input!" << endl;
        }

    } while(go);
}

void UserInterface::searchVehicleById() {
    // Allt sköts i traincontroller
    trainControl->searchVehicleByID();
}

void UserInterface::printAllVehicles() {
    // Sköts av traincontroller
    trainControl->printAllVehicles();
}

void UserInterface::printStats() {
    // Sköts av traincontroller
    trainControl->printStats();
}

void UserInterface::statsMenu() {
    // Användaren väljer alternativ
    bool go = true;
    do{
        cout << "--Statistic Menu--" << endl;
        cout << "1. Change log level [" << trainControl->getLogLevel() << "]" << endl;
        cout << "2. Print statistics"  << endl;
        cout << "3. Train menu" << endl;
        cout << "4. Station menu" << endl;
        cout << "5. Vehicle menu" << endl;
        cout << "0. Return" << endl;

        int choice;
        cin >> choice;

        switch(choice) {
            case 1: logMenu();
                break;
            case 2: printStats();
                break;
            case 3: trainMenu();
                break;
            case 4: stationMenu();
                break;
            case 5: vehicleMenu();
                break;
            case 0: go = false; // Gå tillbaka
                break;
            default: cout << "Invalid input!" << endl;
        }
    }while(go);
}
