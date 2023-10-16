#ifndef PRISON_H
#define PRISON_H 

#include <string>
using std::string;

#include "Time.h"
#include "Inmate.h"

class Prison{
    public:
        Prison();
        Prison(int, int=11, int=10, int=24);
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

        Routine getDailyRoutineAtIndex(int) const;
        inline int getNextEntrieInDailyRoutine() const {return nextEntrieInDailyRoutine;}

    private:
        const int MAXSIZENAMELOCATION = 50;

        Routine *dailyRoutinePtr;
        string *registeredInmatesPtr;
        string *locationsPtr;
        
        int level;

        int dailyRoutineSize;
        int nextEntrieInDailyRoutine;

        int registeredInmatesSize;
        int nextEntrieInRegisteredInmates;

        int locationsSize;
        int nextEntrieInLocations;

        void allocateDailyPrisonRoutine(Routine);
        void allocateInmateInPrison(const Inmate &);
        void allocateLocationInPrison(string);

        int searchInsertIndex(Routine);
};

#endif //PRISON_H