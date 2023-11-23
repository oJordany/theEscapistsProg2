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

        json toJson(string objectName) const;

        void registerDailyPrisonRoutine(Routine);
        void registerInmateInPrison(const Inmate &);
        void registerBotInmateInPrison(const BotInmate &);
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
        void viewAllBotInmates() const;
        void viewRoutinesToLocationsMap() const;
        void moveBotInmates();

        Routine getDailyRoutineAtIndex(int) const;
        inline int getNextEntrieInDailyRoutine() const {return nextEntrieInDailyRoutine;}

        const Prison & operator=(const Prison &);
        bool operator==(const Prison &) const;
        bool operator!=(const Prison &) const;
        bool operator!() const;

    private:
        bool stopBotInmates;
        string prisonName; 
        Routine *dailyRoutinePtr;
        vector <Inmate *> registeredInmates;
        vector <BotInmate *> registeredBotInmates;
        map <string, bool> locations;
        map <string, string> routinesToLocations;

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
};

#endif //PRISON_H