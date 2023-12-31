#ifndef PRISON_H
#define PRISON_H 

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "Time.h"
#include "Inmate.h"
#include "JobBoard.h"
#include "Data.h"
#include "BotInmate.h"
#include "Item.h"
#include "PlayerInmate.h"

#include <iostream>
using std::ostream;

#include <map>
using std::map;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Prison{
    friend ostream &operator<<(ostream &, const Prison&);

    public:
        Prison(string, const JobBoard &);
        Prison( string, 
                int, 
                const JobBoard &, 
                const Data & = Data(29, 10, 2023));
        Prison(const Prison &);
        Prison(const json &);
        ~Prison();

        json toJson(string) const;

        void registerDailyPrisonRoutine(Routine);
        void registerInmateInPrison(const Inmate &);
        void registerBotInmateInPrison(const BotInmate &);
        void registerPlayerInmateInPrison(const PlayerInmate &);
        void registerLocationInPrison(string, bool);
        void registerRoutineToLocation(string, string);

        void displayDailyRoutine() const;
        void displayAllRegisteredInmates() const;
        void displayAllPrisonLocations() const;

        void setLevel(int);
        void setDailyRoutineSize(int);
        void setRegisteredInmatesSize(int);
        // void setLocationsSize(int);

        void startPrisonTime(const Data &, int, int, int=0, int=0);
        void assignTasksToInmates();
        void displayPrisonJobBoard() const;
        void viewPrisonTaskDetails(int) const;
        
        void viewLocationInformation(string) const;
        void viewAllLocationInformation() const;
        void viewRoutinesToLocationsMap() const;
        void viewAllBotInmates() const;
        void moveBotInmates();
        double giveItemToBotInmate(const Item&, string);
        void showBotInmateRequestByName(string) const;
        void controlPlayerInmateCell();
        BotInmate getBotInmateByName(string) const;
        inline void showBotInmateItemForSale(const BotInmate&botInmateSeller) const{botInmateSeller.showItemForSale();}

        Item getItemFromPlayerInmateLocation(string);
        bool requestWasAcceptedByPlayerInmate(const BotInmate& botInmate){return playerInmatePtr->requestWasAccepted(botInmate);}
        void movePlayerInmate(string);
        void makePlayerInmateBuyItemFromBotInmate(string);
        void addItemToPlayerInmateInventory(const Item&);
        void putPlayerInmateToSleep();
        bool makePlayerInmateAcceptRequest(const BotInmate&);
        void dropItemFromPlayerInmateInventory(int);
        void showPlayerInmateInventory() const;
        Item makePlayerInmateGiveItemTo(int, const BotInmate&);
        void showAcceptedRequestsFromPlayerInmate() const;
        inline string getPlayerInmateName(){return playerInmatePtr->getName();}
        inline string getCurrentLocationPlayerInmate() { return playerInmatePtr->getCurrentLocation();}
        inline void makePlayerInmateBathe(){playerInmatePtr->bathe();};
        inline void makePlayerInmateWorkOut(){playerInmatePtr->workOut();};
        inline void makePlayerInmateReadBook(){playerInmatePtr->readBook();};
        inline void showPlayerInmateProfile(){playerInmatePtr->viewPlayerInmateProfile();}
        inline void giveRewardToPlayerInmate(double reward) { playerInmatePtr->setMoney(reward + playerInmatePtr->getMoney());}

        Routine getDailyRoutineAtIndex(int) const;
        inline int getNextEntrieInDailyRoutine() const {return nextEntrieInDailyRoutine;}
        void drawItems(int=40);

        const Prison & operator=(const Prison &);
        bool operator==(const Prison &) const;
        bool operator!=(const Prison &) const;
        bool operator!() const;

    private:
        bool stopBotInmates;
        bool stopControlPlayerInmateCell;
        string prisonName; 
        Routine *dailyRoutinePtr;
        vector <Inmate *> registeredInmates;
        vector <BotInmate *> registeredBotInmates;
        vector <Item *> items;
        map <string, bool> locations;
        map <string, string> routinesToLocations;
        PlayerInmate *playerInmatePtr;

        Time *prisonTimePtr;
        Data prisonDate;
        JobBoard *prisonJobBoardPtr;

        int level;

        int dailyRoutineSize;
        int nextEntrieInDailyRoutine;

        // int locationsSize;
        // int nextEntrieInLocations;

        void allocateDailyPrisonRoutine(Routine);
        // void allocateLocationInPrison(string);
        int searchInsertIndex(Routine);
        void runAnimation(string, string) const;
};

#endif //PRISON_H