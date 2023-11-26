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

#include <map>
using std::map;
using std::advance;

#include <thread>
using std::thread;
using std::this_thread::sleep_for;

#include <chrono>
using std::chrono::milliseconds;


#define UNDERLINED "\x1b[4m"
#define RESETSTYLE "\x1b[0m"
#define RESET   "\033[0m"
#define BLUE    "\033[34m"    

#include "Prison.h"

Prison::Prison(string prisonName, const JobBoard &jobBoard)
:dailyRoutinePtr(0), level(0), prisonDate(), stopBotInmates(false), playerInmatePtr(0)
{   
    prisonJobBoardPtr = new JobBoard(jobBoard);
    dailyRoutineSize = 0;
    // locationsSize = 0;
    nextEntrieInDailyRoutine = 0;
    // nextEntrieInLocations = 0;
    this->prisonName = prisonName;
    prisonTimePtr = new Time("Time_" + prisonName);
}

Prison::Prison( string prisonName, 
                int level,
                const JobBoard &jobBoard, 
                const Data &date
                )
:prisonDate(date), dailyRoutinePtr(0), stopBotInmates(false), playerInmatePtr(0){
    setLevel(level);
    prisonJobBoardPtr = new JobBoard(jobBoard);
    dailyRoutineSize = 0;
    // locationsSize = 0;
    nextEntrieInDailyRoutine = 0;
    // nextEntrieInLocations = 0;
    // nextEntrieInRegisteredInmates = 0;
    this->prisonName = prisonName;
    prisonTimePtr = new Time("Time_" + prisonName);
}

Prison::Prison(const Prison &other)
:level(other.level), prisonDate(other.prisonDate), stopBotInmates(other.stopBotInmates), playerInmatePtr(0)
{   
    prisonJobBoardPtr = new JobBoard(*other.prisonJobBoardPtr);
    this->prisonName = other.prisonName;
    if (prisonTimePtr != 0)
        delete prisonTimePtr;
    this->prisonTimePtr = (other.prisonTimePtr == 0) ? new Time(*other.prisonTimePtr) : 0;
    this->dailyRoutineSize = other.dailyRoutineSize;
    // this->registeredInmatesSize = other.registeredInmatesSize;
    // this->locationsSize = other.locationsSize;
    this->nextEntrieInDailyRoutine = other.nextEntrieInDailyRoutine;
    // this->nextEntrieInLocations = other.nextEntrieInLocations;
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
    // this->locations = new string[this->locationsSize];
    // for (int i=0; i < nextEntrieInLocations; i++){
    //     this->locationsPtr[i] = other.locationsPtr[i];
    // }
    for (auto pair : other.locations){
        this->locations[pair.first] = pair.second; 
    }

    for (auto pair : other.routinesToLocations){
        this->routinesToLocations[pair.first] = pair.second;
    }
    
    for (auto otherItem : other.items){
        this->items.push_back(new Item(*otherItem));
    }

    for (auto otherRegisteredBotInmate : other.registeredBotInmates){
        registerBotInmateInPrison(*otherRegisteredBotInmate);
    }

    registerPlayerInmateInPrison(*other.playerInmatePtr);
}

Prison::Prison(const json &savedDatasJson)
:prisonDate(Data(savedDatasJson["prisonDate"]["dia"], savedDatasJson["prisonDate"]["mes"], savedDatasJson["prisonDate"]["ano"])), playerInmatePtr(0){
    Task tasks[savedDatasJson["prisonJobBoard"].size()];
    for (int i=0; i < savedDatasJson["prisonJobBoard"].size(); i++){
        tasks[i].taskName = savedDatasJson["prisonJobBoard"][i]["taskName"];
        tasks[i].taskDetails = savedDatasJson["prisonJobBoard"][i]["taskDetails"];
        tasks[i].inmate = 0;
    }

    prisonJobBoardPtr = new JobBoard(tasks, savedDatasJson["prisonJobBoard"].size());

    prisonName = savedDatasJson["prisonName"];
    level = savedDatasJson["level"];

    stopBotInmates = false;
    dailyRoutineSize = 0;
    // locationsSize = 0;
    nextEntrieInDailyRoutine = 0;
    // nextEntrieInLocations = 0;

    Routine routineAux;

    for (auto routine : savedDatasJson["dailyRoutinePtr"]){
        routineAux.startHour = routine["startHour"];
        routineAux.startMinute = routine["startMinute"];
        routineAux.endHour = routine["endHour"];
        routineAux.endMinute = routine["endMinute"];
        routineAux.routineName = routine["routineName"];
        registerDailyPrisonRoutine(routineAux);
    }
    
    prisonTimePtr = new Time("Time_" + prisonName);

    for (auto location : savedDatasJson["locations"]){
        for (auto infoLocation: location.items()){
            registerLocationInPrison(infoLocation.key(), infoLocation.value());
        }
    }

    for (auto routineToJson: savedDatasJson["routinesToLocations"]){
        for (auto infoRoutineToLocation : routineToJson.items()){
            registerRoutineToLocation(infoRoutineToLocation.key(), infoRoutineToLocation.value());
        }
    }

    for (auto inmate : savedDatasJson["registeredInmates"]){
        registerInmateInPrison(Inmate(inmate["name"],
                                      inmate["health"],
                                      inmate["energy"],
                                      inmate["strength"],
                                      inmate["speed"],
                                      inmate["intelligence"],
                                      inmate["money"]));
    }

    for (auto botInmate : savedDatasJson["registeredBotInmates"]){
        BotInmate botInmateAux( botInmate["name"],
                                botInmate["health"],
                                botInmate["energy"],
                                botInmate["strength"],
                                botInmate["speed"],
                                botInmate["intelligence"],
                                botInmate["money"]);
        Request requestAux = {
            botInmate["request"]["description"],
            botInmate["request"]["itemName"],
            botInmate["request"]["status"],
        };
        botInmateAux.setRequest(requestAux);
        registerBotInmateInPrison(botInmateAux);
    }

    PlayerInmate playerInmateAux(savedDatasJson["playerInmatePtr"]["name"],
                                 savedDatasJson["playerInmatePtr"]["health"],
                                 savedDatasJson["playerInmatePtr"]["energy"],
                                 savedDatasJson["playerInmatePtr"]["strength"],
                                 savedDatasJson["playerInmatePtr"]["speed"],
                                 savedDatasJson["playerInmatePtr"]["intelligence"],
                                 savedDatasJson["playerInmatePtr"]["money"]);

    playerInmateAux.setOutfit(Item( savedDatasJson["playerInmatePtr"]["outfit"]["itemName"],
                                    savedDatasJson["playerInmatePtr"]["outfit"]["ownerName"],
                                    savedDatasJson["playerInmatePtr"]["outfit"]["currentLocation"]));

    for (const auto& item : savedDatasJson["playerInmatePtr"]["storedItems"]){
        playerInmateAux.addItem(Item(item["itemName"],
                                     item["ownerName"],
                                     item["currentLocation"]
                                    ));
    }

    for (const auto& acceptedRequest : savedDatasJson["playerInmatePtr"]["acceptedRequests"]){
        BotInmate botInmateAux2( acceptedRequest["name"],
                                acceptedRequest["health"],
                                acceptedRequest["energy"],
                                acceptedRequest["strength"],
                                acceptedRequest["speed"],
                                acceptedRequest["intelligence"],
                                acceptedRequest["money"]);
        Request requestAux2 = {
            acceptedRequest["request"]["description"],
            acceptedRequest["request"]["itemName"],
            acceptedRequest["request"]["status"],
        };
        botInmateAux2.setRequest(requestAux2);
        playerInmateAux.acceptRequest(botInmateAux2);
    }
    playerInmateAux.moveTo(savedDatasJson["playerInmatePtr"]["currentLocation"]);
    registerPlayerInmateInPrison(playerInmateAux);
    drawItems();
}

void Prison::registerPlayerInmateInPrison(const PlayerInmate &player){
    if (playerInmatePtr != 0){
        delete playerInmatePtr;
        playerInmatePtr = 0;
        playerInmatePtr = new PlayerInmate(player);
        return;
    }
    playerInmatePtr = new PlayerInmate(player);
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
    moveBotInmates();
}

void Prison::assignTasksToInmates(){
    for (int i = 0; i < prisonJobBoardPtr->getNextEntrieInTasks(); i++){
        prisonJobBoardPtr->unassignTask(i);
    }

    if (!*prisonJobBoardPtr > registeredInmates.size()){
        prisonJobBoardPtr->setTasksSize(registeredInmates.size());
    }

    int randomIndex;

    while (prisonJobBoardPtr->getIsAvailable()){
        // Gera um índice aleatório do vetor de Inmates
        randomIndex = rand() % registeredInmates.size();
        // cout << "ri: " << randomIndex << "\n" << *registeredInmates[randomIndex];
        prisonJobBoardPtr->assignTaskTo(*registeredInmates[randomIndex]);
    }
}

void Prison::displayPrisonJobBoard() const{
    prisonJobBoardPtr->displayTasks();
}

void Prison::viewPrisonTaskDetails(int taskIndex) const{
    prisonJobBoardPtr->viewTasksDetails(taskIndex);
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
    setfill(' ');
    for (int i = 0; i < nextEntrieInDailyRoutine; i++){
        cout << setfill('0') << setw(2) << dailyRoutinePtr[ i ].startHour << ":" << setfill('0') << setw(2) << dailyRoutinePtr[ i ].startMinute << " - ";
        cout << setfill('0') << setw(2) << dailyRoutinePtr[ i ].endHour << ":" << setfill('0') << setw(2) << dailyRoutinePtr[ i ].endMinute << " | ";
        cout << dailyRoutinePtr[ i ].routineName << "\n"; 
    }
    setfill(' ');
}

void Prison::registerInmateInPrison(const Inmate &inmate){
    string inmateName = inmate.getName();
    string inmateRoomName = inmateName + "'s" + " room";
    bool roomAlreadyExists = false;
    for (auto pair : locations){
        if (pair.first == inmateRoomName){
            roomAlreadyExists = true;
            break;
        }
    }
    if (!roomAlreadyExists)
        registerLocationInPrison(inmateRoomName, true);
    registeredInmates.push_back(new Inmate(inmate));
}

void Prison::registerBotInmateInPrison(const BotInmate &botInmate){
    registeredBotInmates.push_back(new BotInmate(botInmate));
}

void Prison::viewAllBotInmates() const{
    for (auto registeredBotInmate : registeredBotInmates){
        cout << *registeredBotInmate << "\n";
    }
}

void Prison::viewRoutinesToLocationsMap() const{
    for (auto routine : routinesToLocations){
        cout << routine.first << ": " << routine.second << "\n";
    }    
}

void Prison::viewLocationInformation(string locationName) const{
    string botCurrentLocation;
    int botID = 0;
    if (locations.find(locationName) != locations.end()){
        cout << setw(15) << UNDERLINED << locationName << RESET << "\n";
        cout << "+" << setw(15) << setfill('-') << "+" << setfill(' ') << "\n";
        cout << "|" << left << setw(14) << "Local Inmates" << "|" << "\n";
        cout << "+" << right << setw(15) << setfill('-') << "+" << setfill(' ') << "\n";

        for (auto registeredBotInmate : registeredBotInmates){
            botCurrentLocation = registeredBotInmate->getCurrentLocation();
            if (botCurrentLocation == locationName){
                cout << "| Bot ID: " << botID << left << setw(14) << registeredBotInmate->getName() << "|" << "\n";
                botID++;
            }
        }
        cout << "+" << right << setw(15) << setfill('-') << "+" << setfill(' ') << "\n";

        for (auto item : items){
            if (item->getCurrentLocation() == locationName){
                item->viewInfos();
            }
        }
    }else{
        cout << "non-existent location\n";
    }
    
}

Item Prison::getItemFromPlayerInmateLocation(string itemName){
    for (int i=0; i < items.size(); i++){
        if (playerInmatePtr->getCurrentLocation() == items[i]->getCurrentLocation()){
            Item returnedItem(itemName, playerInmatePtr->getName(), playerInmatePtr->getCurrentLocation());
            delete items[i];
            items.erase(items.begin() + i);
            return returnedItem;
        }
    }
    throw std::out_of_range("🚫 \033[31m\x1b[1;4mInvalid Item Name!\033[m\x1b[0m 🚫 Item name not found with name: " + itemName);
}

BotInmate Prison::getBotInmateByName(string name) const{
    for (auto registeredBotInmate : registeredBotInmates){
        if (name == registeredBotInmate->getName() && 
            registeredBotInmate->getCurrentLocation() == playerInmatePtr->getCurrentLocation()){
            BotInmate returnedBotInmate(*registeredBotInmate);
            return returnedBotInmate;
        }
    }

    throw std::out_of_range("🚫 \033[31m\x1b[1;4mInvalid Inmate Name!\033[m\x1b[0m 🚫 Inmate not found with name: " + name);
}

void Prison::viewAllLocationInformation() const{
    string botCurrentLocation;
    string locationName;;
    for (auto location : locations){
        locationName = location.first;
        cout << setw(15) << UNDERLINED << locationName << RESET << "\n";
        cout << "+" << setw(15) << setfill('-') << "+" << setfill(' ') << "\n";
        cout << "|" << left << setw(14) << "Local Inmates" << "|" << "\n";
        cout << "+" << right << setw(15) << setfill('-') << "+" << setfill(' ') << "\n";

        for (auto registeredBotInmate : registeredBotInmates){
            botCurrentLocation = registeredBotInmate->getCurrentLocation();
            if (botCurrentLocation == locationName)
                cout << "|" << left << setw(14) << registeredBotInmate->getName() << "|" << "\n";
        }
        cout << "+" << right << setw(15) << setfill('-') << "+" << setfill(' ') << "\n";
        for (auto item : items){
            if (item->getCurrentLocation() == locationName){
                item->viewInfos();
            }
        }
    }
}

void Prison::moveBotInmates(){
    // cout << (Time::getGameIsRunning()) << "\n";
    thread moveBotInmatesThread([this](){
        map <string, bool> releasedLocations;
        for (auto location: locations){
            if (location.second == true){
                releasedLocations[location.first] = location.second;
            }
        }
        srand(time(0));
        int randomIndex;
        string destination = routinesToLocations[Time::getCurrentRoutineName()];
        string lastDestination = "";
        bool random;
        while (!stopBotInmates){
            destination = routinesToLocations[Time::getCurrentRoutineName()];
            if (Time::getCurrentRoutineName() == "Lights Out")
                random = false;
            if (destination != "" && destination != lastDestination){
                random = false;
                for (auto botInmate : registeredBotInmates){
                    botInmate->moveTo(destination);
                    locations[botInmate->getName()+"'s" + " room"] = 1;
                    // cout << *botInmate << "\n";
                }
                lastDestination = destination;
            }else if (destination == "" && !random){
                random = true;
                if (Time::getCurrentRoutineName() != "Lights Out"){
                    for (auto botInmate : registeredBotInmates){
                        auto it = releasedLocations.begin();
                        advance(it, rand() % releasedLocations.size());
                        destination = it->first;
                        botInmate->moveTo(destination);
                        locations[botInmate->getName()+"'s" + " room"] = 1;
                        // cout << *botInmate << "\n";
                    }
                } else {
                    for (auto botInmate : registeredBotInmates){
                        botInmate->moveTo(botInmate->getName()+"'s" + " room");
                        locations[botInmate->getName()+"'s" + " room"] = 0;
                    }
                }
                lastDestination = destination;
            }
        }
    });
    moveBotInmatesThread.detach();
}

void Prison::displayAllRegisteredInmates() const {
    for (int i=0; i < registeredInmates.size(); i++){
        cout << "Inmate " << i << ": " << registeredInmates[i]->getName() << "\n";
    }
}

void Prison::registerLocationInPrison(string locationName, bool access){
    locations[locationName] = access;
    // if (nextEntrieInLocations < locationsSize){
    //     locationsPtr[ nextEntrieInLocations++ ] = locationName;
    //     return;
    // }

    // if (locationsSize == 0){
    //     locationsSize = 1;
    //     locationsPtr = new string[locationsSize];
    //     locationsPtr[ nextEntrieInLocations++ ] = locationName;
    //     return;
    // }

    // allocateLocationInPrison(locationName);
}

void Prison::registerRoutineToLocation(string routineName, string locationName){
    routinesToLocations[routineName] = locationName;
}

// void Prison::allocateLocationInPrison(string locationName){
//     string *locationsTempPtr = new string[locationsSize];

//     for (int i = 0; i < nextEntrieInLocations; i++){
//         locationsTempPtr[i] = locationsPtr[i];
//     }

//     delete [] locationsPtr;

//     locationsSize = int(ceil(locationsSize * 1.5));

//     locationsPtr = new string[locationsSize];
//     for (int i = 0; i < nextEntrieInLocations; i++){
//         locationsPtr[i] = locationsTempPtr[i];
//     }
//     locationsPtr[nextEntrieInLocations++] = locationName;

//     delete [] locationsTempPtr;    
// }

void Prison::displayAllPrisonLocations() const {
    string access;
    cout << setfill('-') << setw(45)  << "\x1b[1;4mPRISON LOCATIONS\x1b[0m" << setfill('-') << setw(20) << "\n";
    for (auto pair: locations){
        access = (pair.second) ? "🔓 \033[32mfree access\033[m" : "🔒 \033[31mrestricted access\033[m";
        cout << "\x1b[1m" << pair.first << "\x1b[0m" << ": " << access << "\n";
    }
    cout << setfill('-') << setw(55) << "\n" << setfill(' ');
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

// void Prison::setLocationsSize(int locationsSize){
//     if (locationsSize <= 0){
//         this->locationsSize = 0;
//         delete [] locationsPtr;
//         locationsPtr = 0;
//         nextEntrieInLocations = 0;
//         return;
//     }

//     if (this->locationsSize == 0){
//         this->locationsSize = locationsSize;
//         locationsPtr = new string[locationsSize];
//         return;
//     }

//     string *locationsTempPtr = new string[locationsSize];

//     int endOflocations = (locationsSize < this->locationsSize) ? locationsSize : nextEntrieInLocations;

//     for (int i = 0; i < endOflocations; i++){
//         locationsTempPtr[i] = locationsPtr[i];
//     }

//     delete [] locationsPtr;

//     nextEntrieInLocations = endOflocations;
//     this->locationsSize = locationsSize;

//     locationsPtr = new string[locationsSize];

//     for (int i = 0; i < endOflocations; i++){
//         locationsPtr[i] = locationsTempPtr[i];
//     }

//     delete [] locationsTempPtr;    
// }

Routine Prison::getDailyRoutineAtIndex(int index) const{
    if (index >= 0 && index < dailyRoutineSize){
        return dailyRoutinePtr[index];
    }
    return {};
}

json Prison::toJson(string objectName) const{
    json prisonJson;

    //Saving prisonName [string]
    prisonJson[objectName]["prisonName"] = prisonName;

    //Saving playerInmatePtr [PlayerInmate*]
    prisonJson[objectName]["playerInmatePtr"] = playerInmatePtr->toFullJson();
    
    // Saving Inmates [vector]
    for (const auto& inmate : registeredInmates) {
        prisonJson[objectName]["registeredInmates"].push_back(inmate->toJson());
    }

    // Saving BotInmates [vector]
    for (const auto& botInmate : registeredBotInmates) {
        prisonJson[objectName]["registeredBotInmates"].push_back(botInmate->toFullJson());
    } 

    // Saving locationsPtr [Map]
    for (auto pair : locations){
        json locationJson;
        locationJson[pair.first] = pair.second;
        prisonJson[objectName]["locations"].push_back(locationJson); 
    }

    //Saving dailyRoutinePtr [Array]
    json routine;
    for (int i=0; i < nextEntrieInDailyRoutine; i++){
        routine["routineName"] = dailyRoutinePtr[i].routineName;
        routine["startHour"] = dailyRoutinePtr[i].startHour;
        routine["startMinute"] = dailyRoutinePtr[i].startMinute;
        routine["endHour"] = dailyRoutinePtr[i].endHour;
        routine["endMinute"] = dailyRoutinePtr[i].endMinute;
        prisonJson[objectName]["dailyRoutinePtr"].push_back(routine);
    }

    //Saving prisonTimePtr [Time]
    if (!*prisonTimePtr)
        prisonJson[objectName]["prisonTimePtr"] = Time::toJson();
    else{
        prisonJson[objectName]["prisonTimePtr"]["currentDay"] = 0;
        prisonJson[objectName]["prisonTimePtr"]["dayCounter"] = 0;
        prisonJson[objectName]["prisonTimePtr"]["startDate"]["ano"] = prisonDate.getAno();
        prisonJson[objectName]["prisonTimePtr"]["startDate"]["mes"] = prisonDate.getMes();
        prisonJson[objectName]["prisonTimePtr"]["startDate"]["dia"] = prisonDate.getDia();
        prisonJson[objectName]["prisonTimePtr"]["startHour"] = dailyRoutinePtr[0].startHour;
        prisonJson[objectName]["prisonTimePtr"]["startMinute"] = dailyRoutinePtr[0].startMinute;
    }

    //Saving prisonDate [Data]
    json dateJson;
    dateJson["dia"] = prisonDate.getDia();
    dateJson["mes"] = prisonDate.getMes();
    dateJson["ano"] = prisonDate.getAno();
    prisonJson[objectName]["prisonDate"] = dateJson;

    //Saving prisonJobBoard [JobBoard]
    prisonJson[objectName]["prisonJobBoard"] = prisonJobBoardPtr->toJson();

    //Saving level [int]
    prisonJson[objectName]["level"] = level;
    
    //Saving routinesToLocations [Map]
    for (auto pair: routinesToLocations){
        json routinesToLocationsJson;
        routinesToLocationsJson[pair.first] = pair.second;
        prisonJson[objectName]["routinesToLocations"].push_back(routinesToLocationsJson);
    }

    return prisonJson;
}

void Prison::movePlayerInmate(string newLocation){
    bool locationIsValid = false;
    for (auto location : locations){
        if (newLocation == location.first){
            if (!location.second){
                cout << "🚧 \033[31m\x1b[1;4mRestricted Access!\033[31m\x1b[0m 🚧 This area requires a key for entry. 🔑\n";
                return ;
            }
            playerInmatePtr->moveTo(newLocation);
            playerInmatePtr->refreshStoredItemsLocations();
            playerInmatePtr->refreshOutfitLocation();
            break;
        }
    }
}

void Prison::addItemToPlayerInmateInventory(const Item &item){
    playerInmatePtr->addItem(item);
}

void Prison::putPlayerInmateToSleep(){
    playerInmatePtr->sleep();
}

void Prison::makePlayerInmateAcceptRequest(const BotInmate &botInmate){
    playerInmatePtr->acceptRequest(botInmate);
}

void Prison::dropItemFromPlayerInmateInventory(int itemID){
    try {
        items.push_back(new Item(playerInmatePtr->dropItem(itemID)));
    }catch(const std::exception& e){
        std::cerr << e.what() << "\n";
    }
}

void Prison::showPlayerInmateInventory() const{
    playerInmatePtr->showInventory();
}

Item Prison::makePlayerInmateGiveItemTo(int itemID, const BotInmate& botInmate){ /* USAR try catch*/
    try {
        return (playerInmatePtr->giveItemTo(itemID, botInmate));
    }catch (const std::exception& e){
        std::cerr << e.what() << "\n";
        throw std::out_of_range(e.what());
    }
}

void Prison::showAcceptedRequestsFromPlayerInmate() const{
    playerInmatePtr->showAcceptedRequests();
}

void Prison::drawItems(int amount){
    int randomIndex;
    for (int i = 0; i < amount; i++){
        randomIndex = rand() % locations.size();
        auto it = locations.begin();
        advance(it, randomIndex);
        items.push_back(new Item("", "", it->first));
    }
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
    this->prisonJobBoardPtr = new JobBoard(*prison.prisonJobBoardPtr);
    if (prisonTimePtr != 0)
        delete prisonTimePtr;
    this->prisonTimePtr = (prison.prisonTimePtr == 0) ? new Time(*prison.prisonTimePtr) : 0;
    this->dailyRoutineSize = prison.dailyRoutineSize;
    // this->locationsSize = prison.locationsSize;
    this->nextEntrieInDailyRoutine = prison.nextEntrieInDailyRoutine;
    // this->nextEntrieInLocations = prison.nextEntrieInLocations;
    this->dailyRoutinePtr = new Routine[this->dailyRoutineSize];
    for (int i=0; i < nextEntrieInDailyRoutine; i++){
        this->dailyRoutinePtr[i] = prison.dailyRoutinePtr[i];
    }
    for (int i=0; i < registeredInmates.size(); i++){
        delete this->registeredInmates[i];
    }
    this->registeredInmates.resize(prison.registeredInmates.size());
    for (int i=0; i < registeredInmates.size(); i++){
        if (this->registeredInmates[i] != 0)
            delete this->registeredInmates[i];
        this->registeredInmates[i] = new Inmate(*prison.registeredInmates[i]);
    }
    // this->locationsPtr = new string[this->locationsSize];
    // for (int i=0; i < nextEntrieInLocations; i++){
    //     this->locationsPtr[i] = prison.locationsPtr[i];
    // }
    for (auto pair : prison.locations){
        this->locations[pair.first] = pair.second;
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
    if (*this->prisonJobBoardPtr != *prison.prisonJobBoardPtr)
        return false;
    if ((this->prisonTimePtr == 0 && prison.prisonTimePtr != 0) || (this->prisonTimePtr != 0 && prison.prisonTimePtr == 0))
        return false;
    if (*this->prisonTimePtr != *prison.prisonTimePtr)
        return false;
    if (this->dailyRoutineSize != prison.dailyRoutineSize)
        return false;
    // if (this->locationsSize != prison.locationsSize)
    //     return false;
    if (this->nextEntrieInDailyRoutine != prison.nextEntrieInDailyRoutine)
        return false;
    // if (this->nextEntrieInLocations != prison.nextEntrieInLocations)
    //     return false;
    if (this->locations.size() != prison.locations.size()) 
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
    // for (int i=0; i < nextEntrieInLocations; i++){
    //     if (this->locationsPtr[i] != prison.locationsPtr[i])
    //         return false;
    // }
    for (auto pair : this->locations){
        if (prison.locations.find(pair.first) == prison.locations.end() || prison.locations.at(pair.first) != pair.second)
            return false;
    }
    
    return true;
}

bool Prison::operator!=(const Prison &prison) const{
    return !(*this == prison);
}

bool Prison::operator!() const{
    return ( !*this->prisonJobBoardPtr && 
            this->registeredInmates.size() &&
            this->nextEntrieInDailyRoutine &&
            this->locations.size());
}

Prison::~Prison(){
    stopBotInmates = true;
    delete [] dailyRoutinePtr;
    // delete [] locationsPtr;
    delete prisonTimePtr;
    delete playerInmatePtr;

    prisonTimePtr=0;
    delete prisonJobBoardPtr;
    for (int i=0; i < registeredInmates.size(); i++){
        delete registeredInmates[i];
    }
    for (int i=0; i < registeredBotInmates.size(); i++){
        delete registeredBotInmates[i];
    }
    for (int i=0; i < items.size(); i++){
        delete items[i];
    }
}
