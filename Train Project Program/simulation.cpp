// Tommy Yasi/toya1800
// Definitionsfilför simulation
//
#include "simulation.h"

Simulation::Simulation(int pStartTime, int pEndTime) {
    currentTime = pStartTime;
    startTime = pStartTime;
    endTime = pEndTime;
}

void Simulation::scheduleEvent(Event *newEvent) {
    eventQueue.push(newEvent);
}

void Simulation::run() {
    while(!eventQueue.empty()) {
        Event *nextEvent = eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent->getTime();
        nextEvent->processEvent();
        delete nextEvent;
    }
}

bool Simulation::runNextEvent() {
    if (!eventQueue.empty() && eventQueue.top()->getTime() < endTime) {
        Event *nextEvent= eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent->getTime(); // Ändra tid
        nextEvent->processEvent();  // kör nästa event
        return true;
    }
    else {
        return false;
    }
}

void Simulation::runNextInterval(int intervalTime) {
    int fullTime = currentTime + intervalTime;

    // Kör om den ej är tom och tidigare än sluttid
    if(!eventQueue.empty() && eventQueue.top()->getTime() < fullTime){
        Event* nextEvent = eventQueue.top(); // Nästa event från kön
        eventQueue.pop(); // Ta bort eventet
        currentTime = nextEvent->getTime(); // Ändra tiden
        nextEvent->processEvent(); // Kör nästa event
    }
}
