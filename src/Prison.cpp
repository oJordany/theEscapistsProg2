#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
using std::setfill;
using std::left;
using std::right;

#include <cmath>
using std::ceil;

#include "Prison.h"

Prison::Prison()
:dailyRoutinePtr(0), registeredInmatesPtr(0), locationsPtr(0), level(0)
{
    dailyRoutineSize = 0;
    registeredInmatesSize = 0;
    locationsSize = 0;
    nextEntrieInDailyRoutine = 0;
    nextEntrieInLocations = 0;
    nextEntrieInRegisteredInmates = 0;
}

Prison::Prison(int level, int dailyRoutineSize, int registeredInmatesSize, int locationsSize)
{
    setLevel(level);
    setDailyRoutineSize(dailyRoutineSize);
    setRegisteredInmatesSize(registeredInmatesSize);
    setLocationsSize(locationsSize);
    nextEntrieInDailyRoutine = 0;
    nextEntrieInLocations = 0;
    nextEntrieInRegisteredInmates = 0;
}

Prison::Prison(const Prison &other)
:level(other.level)
{   
    this->dailyRoutineSize = other.dailyRoutineSize;
    this->registeredInmatesSize = other.registeredInmatesSize;
    this->locationsSize = other.locationsSize;
    this->nextEntrieInDailyRoutine = other.nextEntrieInDailyRoutine;
    this->nextEntrieInLocations = other.nextEntrieInLocations;
    this->nextEntrieInRegisteredInmates = other.nextEntrieInRegisteredInmates;
    //PASSAR OS PONTEIROS ...
    this->dailyRoutinePtr = new Routine[this->dailyRoutineSize];
    for (int i=0; i < nextEntrieInDailyRoutine; i++){
        this->dailyRoutinePtr[i] = other.dailyRoutinePtr[i];
    }
    this->registeredInmatesPtr = new string[this->registeredInmatesSize];
    for (int i=0; i < nextEntrieInRegisteredInmates; i++){
        this->registeredInmatesPtr[i] = other.registeredInmatesPtr[i];
    }
    this->locationsPtr = new string[this->locationsSize];
    for (int i=0; i < nextEntrieInLocations; i++){
        this->locationsPtr[i] = other.locationsPtr[i];
    }
}

int Prison::searchInsertIndex(Routine routine){
    int insertIndex = 0;
    while (insertIndex < nextEntrieInDailyRoutine && 
        dailyRoutinePtr[insertIndex].startHour < routine.startHour){
        insertIndex++;
    }
    while (insertIndex < nextEntrieInDailyRoutine && 
        dailyRoutinePtr[insertIndex].startMinute < routine.startMinute){
        insertIndex++;
    }
    return insertIndex;
}

void Prison::registerDailyPrisonRoutine(Routine routine){
    if (nextEntrieInDailyRoutine < dailyRoutineSize){
        int insertIndex = searchInsertIndex(routine);

        for (int i = nextEntrieInDailyRoutine; i > insertIndex; i--){
            dailyRoutinePtr[i] = dailyRoutinePtr[i-1];  
        }

        dailyRoutinePtr[insertIndex] = routine;
        nextEntrieInDailyRoutine++;
        return;
    }

    if (dailyRoutineSize == 0){
        dailyRoutineSize = 1;
        dailyRoutinePtr = new Routine[dailyRoutineSize];
        dailyRoutinePtr[ nextEntrieInDailyRoutine++ ] = routine;
        return;
    }

    allocateDailyPrisonRoutine( routine );
}

void Prison::allocateDailyPrisonRoutine( Routine routine ){
    Routine *dailyRoutineTempPtr = new Routine[dailyRoutineSize];

    for (int i = 0; i < nextEntrieInDailyRoutine; i++){
        dailyRoutineTempPtr[i] = dailyRoutinePtr[i];
    }
    
    delete [] dailyRoutinePtr;

    dailyRoutineSize = int(ceil(dailyRoutineSize * 1.5));

    dailyRoutinePtr = new Routine[dailyRoutineSize];

    for (int i = 0; i < nextEntrieInDailyRoutine; i++){
        dailyRoutinePtr[i] = dailyRoutineTempPtr[i];
    }

    int insertIndex = searchInsertIndex(routine);

    for (int i = nextEntrieInDailyRoutine; i > insertIndex; i--){
        dailyRoutinePtr[i] = dailyRoutinePtr[i-1];  
    }
    dailyRoutinePtr[insertIndex] = routine;
    // displayDailyRoutine();
    nextEntrieInDailyRoutine++;
    delete [] dailyRoutineTempPtr;
}

void Prison::displayDailyRoutine() const{
    for (int i = 0; i < nextEntrieInDailyRoutine; i++){
        cout << setfill('0') << setw(2) << dailyRoutinePtr[ i ].startHour << ":" << setfill('0') << setw(2) << dailyRoutinePtr[ i ].startMinute << " - ";
        cout << setfill('0') << setw(2) << dailyRoutinePtr[ i ].endHour << ":" << setfill('0') << setw(2) << dailyRoutinePtr[ i ].endMinute << " | ";
        cout << dailyRoutinePtr[ i ].routineName << "\n"; 
    }
}

void Prison::registerInmateInPrison(const Inmate &inmate){
    string inmateName = inmate.getName();
    string inmateRoomName = inmateName + "'s" + " room";
    registerLocationInPrison(inmateRoomName);
    if (nextEntrieInRegisteredInmates < registeredInmatesSize){
        registeredInmatesPtr[ nextEntrieInRegisteredInmates++ ] = inmateName;
        return;
    }

    if (registeredInmatesSize == 0){
        registeredInmatesSize = 1;
        registeredInmatesPtr = new string[registeredInmatesSize];
        registeredInmatesPtr[ nextEntrieInRegisteredInmates++ ] = inmateName;
        return;
    }

    allocateInmateInPrison(inmate);
}

void Prison::allocateInmateInPrison(const Inmate& inmate){
    string *registeredInmatesTempPtr = new string[registeredInmatesSize];

    for (int i = 0; i < nextEntrieInRegisteredInmates; i++){
        registeredInmatesTempPtr[i] = registeredInmatesPtr[i];
    }

    delete [] registeredInmatesPtr;

    registeredInmatesSize = int(ceil(registeredInmatesSize * 1.5));

    registeredInmatesPtr = new string[registeredInmatesSize];
    for (int i = 0; i < nextEntrieInRegisteredInmates; i++){
        registeredInmatesPtr[i] = registeredInmatesTempPtr[i];
    }
    registeredInmatesPtr[nextEntrieInRegisteredInmates++] = inmate.getName();

    delete [] registeredInmatesTempPtr;    
}

void Prison::displayAllRegisteredInmates() const{
    for (int i=0; i < nextEntrieInRegisteredInmates; i++){
        cout << "Inmate " << i << ": " << registeredInmatesPtr[i] << "\n";
    }
}

void Prison::registerLocationInPrison(string locationName){
    if (nextEntrieInLocations < locationsSize){
        locationsPtr[ nextEntrieInLocations++ ] = locationName;
        return;
    }

    if (locationsSize == 0){
        locationsSize = 1;
        locationsPtr = new string[locationsSize];
        locationsPtr[ nextEntrieInLocations++ ] = locationName;
        return;
    }

    allocateLocationInPrison(locationName);
}

void Prison::allocateLocationInPrison(string locationName){
    string *locationsTempPtr = new string[locationsSize];

    for (int i = 0; i < nextEntrieInLocations; i++){
        locationsTempPtr[i] = locationsPtr[i];
    }

    delete [] locationsPtr;

    locationsSize = int(ceil(locationsSize * 1.5));

    locationsPtr = new string[locationsSize];
    for (int i = 0; i < nextEntrieInLocations; i++){
        locationsPtr[i] = locationsTempPtr[i];
    }
    locationsPtr[nextEntrieInLocations++] = locationName;

    delete [] locationsTempPtr;    
}

void Prison::displayAllPrisonLocations() const {
    cout << "Locais da prisão: \n";
    for (int i=0; i < nextEntrieInLocations; i++){
        cout << locationsPtr[i] << "\n";
    }
}

void Prison::setLevel(int level){
    if (level < 0){
        level = 0;
        return;
    } else if(level > 4){
        level = 4;
        return;
    }
    this->level = level;
}

void Prison::setDailyRoutineSize(int dailyRoutineSize){
    if (dailyRoutineSize <= 0){
        this->dailyRoutineSize = 0;
        delete [] dailyRoutinePtr;
        dailyRoutinePtr = 0;
        nextEntrieInDailyRoutine = 0;
        return;
    }

    if (this->dailyRoutineSize == 0){
        this->dailyRoutineSize = dailyRoutineSize;
        dailyRoutinePtr = new Routine[dailyRoutineSize];
        return;
    }

    Routine *dailyRoutineTempPtr = new Routine[dailyRoutineSize];

    int endOfDailyRoutine = (dailyRoutineSize < this->dailyRoutineSize) ? dailyRoutineSize : nextEntrieInDailyRoutine;

    for (int i = 0; i < endOfDailyRoutine; i++){
        dailyRoutineTempPtr[i] = dailyRoutinePtr[i];
    }
    
    delete [] dailyRoutinePtr;

    nextEntrieInDailyRoutine = endOfDailyRoutine;
    this->dailyRoutineSize = dailyRoutineSize;

    dailyRoutinePtr = new Routine[dailyRoutineSize];

    for (int i = 0; i < endOfDailyRoutine; i++){
        dailyRoutinePtr[i] = dailyRoutineTempPtr[i];
    }

    delete [] dailyRoutineTempPtr;
}

void Prison::setRegisteredInmatesSize(int registeredInmatesSize){
    if (registeredInmatesSize <= 0){
        this->registeredInmatesSize = 0;
        delete [] registeredInmatesPtr;
        registeredInmatesPtr = 0;
        nextEntrieInRegisteredInmates = 0;
        return;
    }

    if (this->registeredInmatesSize == 0){
        this->registeredInmatesSize = registeredInmatesSize;
        registeredInmatesPtr = new string[registeredInmatesSize];
        return;
    }

    string *registeredInmatesTempPtr = new string[registeredInmatesSize];

    int endOfRegisteredInmates = (registeredInmatesSize < this->registeredInmatesSize) ? registeredInmatesSize : nextEntrieInRegisteredInmates;

    for (int i = 0; i < endOfRegisteredInmates; i++){
        registeredInmatesTempPtr[i] = registeredInmatesPtr[i];
    }

    delete [] registeredInmatesPtr;

    nextEntrieInRegisteredInmates = endOfRegisteredInmates;
    this->registeredInmatesSize = registeredInmatesSize;

    registeredInmatesPtr = new string[registeredInmatesSize];

    for (int i = 0; i < endOfRegisteredInmates; i++){
        registeredInmatesPtr[i] = registeredInmatesTempPtr[i];
    }

    delete [] registeredInmatesTempPtr;    
}

void Prison::setLocationsSize(int locationsSize){
    if (locationsSize <= 0){
        this->locationsSize = 0;
        delete [] locationsPtr;
        locationsPtr = 0;
        nextEntrieInLocations = 0;
        return;
    }

    if (this->locationsSize == 0){
        this->locationsSize = locationsSize;
        locationsPtr = new string[locationsSize];
        return;
    }

    string *locationsTempPtr = new string[locationsSize];

    int endOflocations = (locationsSize < this->locationsSize) ? locationsSize : nextEntrieInLocations;

    for (int i = 0; i < endOflocations; i++){
        locationsTempPtr[i] = locationsPtr[i];
    }

    delete [] locationsPtr;

    nextEntrieInLocations = endOflocations;
    this->locationsSize = locationsSize;

    locationsPtr = new string[locationsSize];

    for (int i = 0; i < endOflocations; i++){
        locationsPtr[i] = locationsTempPtr[i];
    }

    delete [] locationsTempPtr;    
}

Routine Prison::getDailyRoutineAtIndex(int index) const{
    if (index >= 0 && index < registeredInmatesSize){
        return dailyRoutinePtr[index];
    }
    return {};
}

Prison::~Prison(){
    delete [] dailyRoutinePtr;
    delete [] registeredInmatesPtr;
    delete [] locationsPtr;
}
