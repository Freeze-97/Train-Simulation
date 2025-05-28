// Tommy Yasi/toya1800
// Headerfil för konstanter under simuleringen, tillstånd tåg befinner sig i
//

#ifndef PROJECT_OB_SIMCONST_H
#define PROJECT_OB_SIMCONST_H

// Tilltånd som tåg kan befinna sig i under simulationen
enum trainState {NOT_ASSEMBLED, INCOMPLETE, ASSEMBLED, READY, RUNNING, ARRIVED, FINISHED};


// Antal mintuer det tar för de olika tilltånden och simulationstiden
const int TIME_INTERVAL = 10; // Användaren kan stega fram tiden 10 min
const int BUILD = 30; // 30 min för att bygga ihop ett tåg
const int ASSEMBLED_TO_READY = 10; // 10 min före avgångstid ändras det till ready
const int ARRIVED_TO_FINISHED = 20; // Efter 20 min som arrived övergår tillståndet till finished
const int SIM_TIME = 1439; // 1439 mintuer under ett dygn, minus 1 för 00:00
const int INCOMPLETE_TO_ASSEMBLED = 10; // Om den är incomplete läggs 10 min extra

#endif //PROJECT_OB_SIMCONST_H
