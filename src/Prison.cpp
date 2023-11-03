#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
using std::setfill;
using std::left;
using std::right;

#include <cmath>
using std::ceil;

#include <cstdlib>
using std::srand;
using std::rand;

#include <ctime>
using std::time;

#define UNDERLINED "\x1b[4m"
#define RESETSTYLE "\x1b[0m"
#define RESET   "\033[0m"
#define BLUE    "\033[34m"    

#include "Prison.h"

Prison::Prison(string prisonName, const JobBoard &jobBoard)
:dailyRoutinePtr(0), locationsPtr(0), level(0), prisonDate(), prisonJobBoard(jobBoard)
{
    dailyRoutineSize = 0;
    locationsSize = 0;
    nextEntrieInDailyRoutine = 0;
    nextEntrieInLocations = 0;
    this->prisonName = prisonName;
    prisonTimePtr = new Time("Time_" + prisonName);
}

Prison::Prison( string prisonName, 
                int level,
                const JobBoard &jobBoard, 
                const Data &date
                )
:prisonDate(date), prisonJobBoard(jobBoard), dailyRoutinePtr(0), locationsPtr(0){
    setLevel(level);
    dailyRoutineSize = 0;
    locationsSize = 0;
    nextEntrieInDailyRoutine = 0;
    nextEntrieInLocations = 0;
    // nextEntrieInRegisteredInmates = 0;
    this->prisonName = prisonName;
    prisonTimePtr = new Time("Time_" + prisonName);
}

Prison::Prison(const Prison &other)
:level(other.level), prisonDate(other.prisonDate), prisonJobBoard(other.prisonJobBoard)
{   
    this->prisonName = other.prisonName;
    if (prisonTimePtr != 0)
        delete prisonTimePtr;
    this->prisonTimePtr = (other.prisonTimePtr == 0) ? new Time(*other.prisonTimePtr) : 0;
    this->dailyRoutineSize = other.dailyRoutineSize;
    // this->registeredInmatesSize = other.registeredInmatesSize;
    this->locationsSize = other.locationsSize;
    this->nextEntrieInDailyRoutine = other.nextEntrieInDailyRoutine;
    this->nextEntrieInLocations = other.nextEntrieInLocations;
    // this->nextEntrieInRegisteredInmates = other.nextEntrieInRegisteredInmates;
    //PASSAR OS PONTEIROS ...
    this->dailyRoutinePtr = new Routine[this->dailyRoutineSize];
    for (int i=0; i < nextEntrieInDailyRoutine; i++){
        this->dailyRoutinePtr[i] = other.dailyRoutinePtr[i];
    }
    this->registeredInmates.resize(other.registeredInmates.size());
    for (int i=0; i < registeredInmates.size(); i++){
        this->registeredInmates[i] = new Inmate(*other.registeredInmates[i]);
    }
    this->locationsPtr = new string[this->locationsSize];
    for (int i=0; i < nextEntrieInLocations; i++){
        this->locationsPtr[i] = other.locationsPtr[i];
    }
}

void Prison::startPrisonTime(const Data &startDate, int startHour, int startMinute, int dayCounter, int currentDay){
    Time::releaseAllTimes();
    Time::useTime(*prisonTimePtr);
    Time::startTime(dailyRoutinePtr, 
                    dailyRoutineSize, 
                    startDate, 
                    startHour, 
                    startMinute, 
                    dayCounter, 
                    currentDay);
}

void Prison::assignTasksToInmates(){
    // Inicializa a semente para a função rand()
    srand(time(0));

    for (int i = 0; i < prisonJobBoard.getNextEntrieInTasks(); i++){
        prisonJobBoard.unassignTask(i);
    }

    if (!prisonJobBoard > registeredInmates.size()){
        prisonJobBoard.setTasksSize(registeredInmates.size());
    }

    int randomIndex;

    while (prisonJobBoard.getIsAvailable()){
        // Gera um índice aleatório do vetor de Inmates
        randomIndex = rand() % registeredInmates.size();
        // cout << "ri: " << randomIndex << "\n" << *registeredInmates[randomIndex];
        prisonJobBoard.assignTaskTo(*registeredInmates[randomIndex]);
    }
}

void Prison::displayPrisonJobBoard() const{
    prisonJobBoard.displayTasks();
}

void Prison::viewPrisonTaskDetails(int taskIndex) const{
    prisonJobBoard.viewTasksDetails(taskIndex);
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
    registeredInmates.push_back(new Inmate(inmate));
}


void Prison::displayAllRegisteredInmates() const {
    for (int i=0; i < registeredInmates.size(); i++){
        cout << "Inmate " << i << ": " << registeredInmates[i]->getName() << "\n";
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
    if (index >= 0 && index < dailyRoutineSize){
        return dailyRoutinePtr[index];
    }
    return {};
}

json Prison::toJson() const{
    json prisonJson;
    
    //Saving prisonName [string]
    prisonJson["prisonName"] = prisonName;

    // Saving Inmates [vector]
    for (const auto& inmate : registeredInmates) {
        prisonJson["registeredInmates"].push_back(inmate->toJson());
    } 

    // Saving locationsPtr [Array]
    for (int i=0; i < nextEntrieInLocations; i++){
        prisonJson["locationsPtr"].push_back(locationsPtr[i]); 
    }

    //Saving dailyRoutinePtr [Array]
    json routine;
    for (int i=0; i < nextEntrieInDailyRoutine; i++){
        routine["routineName"] = dailyRoutinePtr[i].routineName;
        routine["startHour"] = dailyRoutinePtr[i].startHour;
        routine["startMinute"] = dailyRoutinePtr[i].startMinute;
        routine["endHour"] = dailyRoutinePtr[i].endHour;
        routine["endMinute"] = dailyRoutinePtr[i].endMinute;
        prisonJson["dailyRoutinePtr"].push_back(routine);
    }

    //Saving prisonTimePtr [Time]
    prisonJson["prisonTimePtr"] = (!*prisonTimePtr) ? Time::toJson() : "";

    //Saving prisonDate [Data]
    json dateJson;
    dateJson["dia"] = prisonDate.getDia();
    dateJson["mes"] = prisonDate.getMes();
    dateJson["ano"] = prisonDate.getAno();
    prisonJson["prisonDate"] = dateJson;

    //Saving prisonJobBoard [JobBoard]
    prisonJson["prisonJobBoard"] = prisonJobBoard.toJson();

    //Saving level [int]
    prisonJson["level"] = level;
    

    return prisonJson;
}

ostream &operator<<(ostream &out, const Prison &prison){
    out << BLUE << UNDERLINED << "Prison Name:" << RESET << RESETSTYLE << " " << prison.prisonName << "\n";
    out << BLUE << UNDERLINED << "\nDaily Prison Routine:\n" << RESET << RESETSTYLE;
    prison.displayDailyRoutine();
    out << BLUE << UNDERLINED << "\nInmates Registered in Prison:\n" << RESET << RESETSTYLE;
    prison.displayAllRegisteredInmates();
    out << BLUE << UNDERLINED << "\nPrison Locations:\n" << RESET << RESETSTYLE;
    prison.displayAllPrisonLocations();
    out << BLUE << UNDERLINED << "\nPrison time:\n" << RESET << RESETSTYLE;
    prison.prisonTimePtr->displayTime();
    out << BLUE << UNDERLINED << "\nPrison Date:\n" << RESET << RESETSTYLE;
    out << prison.prisonDate << "\n";
    out << BLUE << UNDERLINED << "\nPrison Job Board:\n" << RESET << RESETSTYLE;
    prison.displayPrisonJobBoard();
    return out;
}

const Prison & Prison::operator=(const Prison &prison){
    this->prisonName = prison.prisonName;
    this->level = prison.level;
    this->prisonDate = prison.prisonDate;
    this->prisonJobBoard = prison.prisonJobBoard;
    if (prisonTimePtr != 0)
        delete prisonTimePtr;
    this->prisonTimePtr = (prison.prisonTimePtr == 0) ? new Time(*prison.prisonTimePtr) : 0;
    this->dailyRoutineSize = prison.dailyRoutineSize;
    this->locationsSize = prison.locationsSize;
    this->nextEntrieInDailyRoutine = prison.nextEntrieInDailyRoutine;
    this->nextEntrieInLocations = prison.nextEntrieInLocations;
    this->dailyRoutinePtr = new Routine[this->dailyRoutineSize];
    for (int i=0; i < nextEntrieInDailyRoutine; i++){
        this->dailyRoutinePtr[i] = prison.dailyRoutinePtr[i];
    }
    this->registeredInmates.resize(prison.registeredInmates.size());
    for (int i=0; i < registeredInmates.size(); i++){
        if (this->registeredInmates[i] != 0)
            delete this->registeredInmates[i];
        this->registeredInmates[i] = new Inmate(*prison.registeredInmates[i]);
    }
    this->locationsPtr = new string[this->locationsSize];
    for (int i=0; i < nextEntrieInLocations; i++){
        this->locationsPtr[i] = prison.locationsPtr[i];
    }
    
    return *this;
}

bool Prison::operator==(const Prison &prison) const{
    if (this->prisonName != prison.prisonName)
        return false;
    if (this->level != prison.level)
        return false;
    if (this->prisonDate != prison.prisonDate)
        return false;
    if (this->prisonJobBoard != prison.prisonJobBoard)
        return false;
    if ((this->prisonTimePtr == 0 && prison.prisonTimePtr != 0) || (this->prisonTimePtr != 0 && prison.prisonTimePtr == 0))
        return false;
    if (*this->prisonTimePtr != *prison.prisonTimePtr)
        return false;
    if (this->dailyRoutineSize != prison.dailyRoutineSize)
        return false;
    if (this->locationsSize != prison.locationsSize)
        return false;
    if (this->nextEntrieInDailyRoutine != prison.nextEntrieInDailyRoutine)
        return false;
    if (this->nextEntrieInLocations != prison.nextEntrieInLocations)
        return false;
    for (int i=0; i < this->nextEntrieInDailyRoutine; i++){
        if (this->dailyRoutinePtr[i].startHour != prison.dailyRoutinePtr[i].startHour)
            return false;
        if (this->dailyRoutinePtr[i].startMinute != prison.dailyRoutinePtr[i].startMinute)
            return false;
        if (this->dailyRoutinePtr[i].endHour != prison.dailyRoutinePtr[i].endHour)
            return false;
        if (this->dailyRoutinePtr[i].endMinute != prison.dailyRoutinePtr[i].endMinute)
            return false;
        if (this->dailyRoutinePtr[i].routineName != prison.dailyRoutinePtr[i].routineName)
            return false;
    }
    for (int i=0; i < registeredInmates.size(); i++){
        if (*this->registeredInmates[i] != *prison.registeredInmates[i] )
            return false;
    }
    for (int i=0; i < nextEntrieInLocations; i++){
        if (this->locationsPtr[i] != prison.locationsPtr[i])
            return false;
    }
        
    return true;
}

bool Prison::operator!=(const Prison &prison) const{
    return !(*this == prison);
}

bool Prison::operator!() const{
    return ( !this->prisonJobBoard && 
            this->registeredInmates.size() &&
            this->nextEntrieInDailyRoutine &&
            this->nextEntrieInLocations);
}

Prison::~Prison(){
    delete [] dailyRoutinePtr;
    delete [] locationsPtr;
    delete prisonTimePtr;
    for (int i=0; i < registeredInmates.size(); i++){
        delete registeredInmates[i];
    }
}
