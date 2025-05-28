// Tommy Yasi/toya1800
// Headerfil för event
//

#ifndef PROJECT_OB_EVENT_H
#define PROJECT_OB_EVENT_H

#include "trainController.h"
#include "simulation.h"
#include "simConst.h"

class Simulation;

class Event{
protected:
    int time;
public:
    explicit Event(int pTime);
    virtual ~Event() { }

    virtual void processEvent() = 0;

    int getTime() const {return time;}
};

class EventComparison : public Event {
public:
    bool operator() (Event * left, Event * right) {
        return left->getTime() > right->getTime();
    }
};

class AssembleEvent : public Event{
protected:
    // Objekt med pekare
    Simulation* simulation;
    Train* train;
    TrainController* trainController;
public:
    // Konstruktor och destruktor
    AssembleEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime);
    ~AssembleEvent() override = default;

    void processEvent() override;
};

class ReadyEvent : public Event{
protected:
    // Objekt med pekare
    Simulation* simulation;
    Train* train;
    TrainController* trainController;
public:
    // Konstruktor och destruktor
    ReadyEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime);
    ~ReadyEvent() override = default;

    void processEvent() override;
};

class RunningEvent : public Event{
protected:
    // Objekt med pekare
    Simulation* simulation;
    Train* train;
    TrainController* trainController;
public:
    // Konstruktor och destruktor
    RunningEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime);
    ~RunningEvent() override = default;

    void processEvent() override;
};

class ArrivedEvent : public Event{
protected:
    // Objekt med pekare
    Simulation* simulation;
    Train* train;
    TrainController* trainController;
public:
    // Konstruktor och destruktor
    ArrivedEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime);
    ~ArrivedEvent() override = default;

    void processEvent() override;
};

class FinishedEvent : public Event{
protected:
    // Objekt med pekare
    Simulation* simulation;
    Train* train;
    TrainController* trainController;
public:
    // Konstruktor och destruktor
    FinishedEvent(Simulation *pSimulation, Train *pTrain, TrainController *pTrainController, int pTime);
    ~FinishedEvent() override = default;

    void processEvent() override;
};

class EndEvent : public Event{
protected:
    // Objekt med pekare
    Simulation* simulation;
    Train* train;
    TrainController* trainController;
public:
    // Konstruktor och destruktor
    EndEvent(Simulation *pSimulation, TrainController *pTrainController, int pTime);
    ~EndEvent() override = default;

    void processEvent() override;
};

#endif //PROJECT_OB_EVENT_H
