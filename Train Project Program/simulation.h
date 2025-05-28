// Tommy Yasi/toya1800
// Headerfil för simulation som används för diskret händelsestyrd simulering
//

#ifndef PROJECT_OB_SIMULATION_H
#define PROJECT_OB_SIMULATION_H

#include "event.h"
#include <queue>

class Simulation{
private:
    int currentTime, startTime, endTime;
    std::priority_queue<Event*, vector<Event*>, EventComparison> eventQueue;
public:
    Simulation(int pStartTime, int pEndTime);
    ~Simulation() = default;

    // Lägg till ny event
    void scheduleEvent (Event* newEvent);

    // Get
    int getTime() const { return currentTime;}

    // Kör
    void run();
    bool runNextEvent();
    void runNextInterval(int intervalTime);
};

#endif //PROJECT_OB_SIMULATION_H
