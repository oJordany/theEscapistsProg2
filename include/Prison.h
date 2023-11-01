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

#include <iostream>
using std::ostream;

class Prison{
    friend ostream &operator<<(ostream &, const Prison&);

    public:
        Prison(string, const JobBoard &);
        Prison( string, 
                int, 
                const JobBoard &, 
                const Data & = Data(29, 10, 2023));
        Prison(const Prison &);
        ~Prison();

        void registerDailyPrisonRoutine(Routine);
        void registerInmateInPrison(const Inmate &);
        void registerLocationInPrison(string);

        void displayDailyRoutine() const;
        void displayAllRegisteredInmates() const;
        void displayAllPrisonLocations() const;

        void setLevel(int);
        void setDailyRoutineSize(int);
        void setRegisteredInmatesSize(int);
        void setLocationsSize(int);

        void startPrisonTime();
        void assignTasksToInmates();
        void displayPrisonJobBoard() const;
        void viewPrisonTaskDetails(int) const;

        Routine getDailyRoutineAtIndex(int) const;
        inline int getNextEntrieInDailyRoutine() const {return nextEntrieInDailyRoutine;}

        const Prison & operator=(const Prison &);
        bool operator==(const Prison &) const;
        bool operator!=(const Prison &) const;
        bool operator!() const;

    private:
        string prisonName; 
        Routine *dailyRoutinePtr;
        vector <Inmate *> registeredInmates;
        string *locationsPtr;

        Time *prisonTimePtr;
        Data prisonDate;
        JobBoard prisonJobBoard;

        int level;

        int dailyRoutineSize;
        int nextEntrieInDailyRoutine;

        // int registeredInmatesSize;
        // int nextEntrieInRegisteredInmates;

        int locationsSize;
        int nextEntrieInLocations;

        void allocateDailyPrisonRoutine(Routine);
        // void allocateInmateInPrison(const Inmate &);
        void allocateLocationInPrison(string);

        int searchInsertIndex(Routine);
};

#endif //PRISON_H