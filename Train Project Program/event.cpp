// Tommy Yasi/toya1800
// Definitionsfil för event, kör alla moment i programmet
//
#include "event.h"

Event::Event(int pTime) {
    time = pTime;
}

// Assemble event
AssembleEvent::AssembleEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime)
: Event(pTime) {
    simulation = pSimulation;
    train = pTrain;
    trainController = pTrainController;
}

void AssembleEvent::processEvent() {
    // Om den inte är assembled läg till tåget
    if(train->getState() == NOT_ASSEMBLED){
        train->getDepartureStation()->addTrains(train); // Lägger till tåg
    }

    // Om det går att bygga tåget (inga fordon saknas)
    if(trainController->buildTrain(train)) {
        train->setTrainState(ASSEMBLED);

        // Nytt event från assembled till ready
        Event* e = new ReadyEvent(simulation, train, trainController,
                                  (train->getStartTime() + train->getStopTimeLate()) - ASSEMBLED_TO_READY);
        // Simulationen
        simulation->scheduleEvent(e);

        // Skriv ut tåg
        trainController->printLogMessage(train, getTime());

    } else if(!trainController->buildTrain(train)){
        train->setTrainState(INCOMPLETE);

        int tmpDelayTime = train->getStartTimeLate() + INCOMPLETE_TO_ASSEMBLED; // Lägg till incplete tid
        train->setStartTimeLate(tmpDelayTime);

        // Räkna plus 10 minuter
        int fullEventTime = getTime() + INCOMPLETE_TO_ASSEMBLED;
        Event* e = new AssembleEvent(simulation, train, trainController, fullEventTime);
        simulation->scheduleEvent(e);

        // Skriv ut tåg
        trainController->printLogMessage(train, getTime());
    }
}

// Ready event
ReadyEvent::ReadyEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime)
: Event(pTime) {
    simulation = pSimulation;
    train = pTrain;
    trainController = pTrainController;
}

void ReadyEvent::processEvent() {
    train->setTrainState(READY);
    int completeDepartureTime = train->getStartTime() + train->getStartTimeLate();

    // Ny Event
    Event* e = new RunningEvent(simulation, train, trainController, completeDepartureTime);
    simulation->scheduleEvent(e);

    // Skriv ut tåg
    trainController->printLogMessage(train, getTime());
}

// Running event
RunningEvent::RunningEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime)
: Event(pTime){
    simulation = pSimulation;
    train = pTrain;
    trainController = pTrainController;
}

void RunningEvent::processEvent() {
    train->setTrainState(RUNNING); // Ändra tillstånd

    // Räkna ut total tid för resan
    double travelTime = train->getStopTime() - train->getStartTime();
    travelTime = (travelTime - train->getStartTimeLate()) / 60; // Försening inräknat och konvertera till timmar

    // Räkna ut hastighet för tåget
    int speed = static_cast<int>(static_cast<double>(train->getDistance()) / travelTime); // Hastighet per KM

    // Om det skulle bli konstigt och hastigheten är högre än max
    if(speed > train->getMaxSpeed()){
        speed = train->getMaxSpeed(); // Tilldela direkt max
    }
    train->setSpeed(speed);

    // Tid i minuter
    double travelTimeMin = 60*(static_cast<double>(train->getDistance()) / train->getSpeed());

    // Ankomsttiden
    int stopTimeWithDelay = train->getStartTime() + train->getStartTimeLate(); // Räkna planerad plus eventuell försening
    int stopTime = static_cast<int>(stopTimeWithDelay + travelTimeMin); // Ankomst

    // Nytt event
    Event* e = new ArrivedEvent(simulation, train, trainController, stopTime);
    simulation->scheduleEvent(e);

    // Ta bort tåget från stationen
    train->getDepartureStation()->deleteTrains(train);

    // Skriv ut tåg
    trainController->printLogMessage(train, getTime());
}

// Arrived event
ArrivedEvent::ArrivedEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime)
: Event(pTime){
    simulation = pSimulation;
    train = pTrain;
    trainController = pTrainController;
}

void ArrivedEvent::processEvent() {
    train->getArrivalStation()->addTrains(train); // Lägg till tåget i slutstationen

    train->setTrainState(ARRIVED); // Ändra tillstånd

    // Räkna ut sluttid och lägg till potentiell försening
    int stopLateTime = getTime() - train->getStopTime();
    train->setStartTimeLate(stopLateTime);

    // Nytt event
    Event* e = new FinishedEvent(simulation, train, trainController,
            getTime() - ARRIVED_TO_FINISHED);
    simulation->scheduleEvent(e);

    // Skriv ut tåg
    trainController->printLogMessage(train, getTime());
}

// Finished event
FinishedEvent::FinishedEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime)
: Event(pTime){
    simulation = pSimulation;
    train = pTrain;
    trainController = pTrainController;
}

void FinishedEvent::processEvent() {
    train->setTrainState(FINISHED); // Ändra tillstånd
    trainController->dissembleTrain(train); // Aställ tåget

    // Skriv ut tåg
    trainController->printLogMessage(train, getTime());
}

// Ending event
EndEvent::EndEvent(Simulation *pSimulation, TrainController *pTrainController, int pTime)
: Event(pTime){
    simulation = pSimulation;
    trainController = pTrainController;
}

void EndEvent::processEvent() {
    // Skriv att det är slut
    trainController->printTracksClosed();
}
