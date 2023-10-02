#ifndef TIME_H
#define TIME_H

#include "string"
using std::string;

#include <fstream>
using std::ofstream;

struct Routine {
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    string routineName;
};

class Time{
    public:
        Time();
        Time(const Time &);
        ~Time();

        static void displayTime();
        static void startTime(const Routine (&)[], int); // Tirar duvida com prof
        static void endTime();

        inline static void incrementHour(){Time::hour++;}
        inline static void incrementMinute(){Time::minute++;}
        inline static void incrementDayCounter(){Time::dayCounter++;}
        inline static void incrementCurrentDay(){Time::currentDay++;}

        inline static void setHour(int hour){Time::hour = (hour <= 24 && hour >= 0) ? hour : 0;}
        inline static void setMinute(int minute){Time::minute = (minute <= 60 && minute >= 0) ? minute : 0;}
        inline static void setCurrentDay(int currentDay){Time::currentDay = (currentDay >= 0) ? currentDay : 0;}
        inline static void setRoutinesNumber(int routinesNumber){Time::routinesNumber = routinesNumber;}
        inline static void setGameIsRunning(bool gameIsRunning){Time::gameIsRunning = gameIsRunning;}
        inline static void setRoutineStartHour(int routineID, int startHour){Time::dailyRoutine[routineID].startHour = startHour;}
        inline static void setRoutineStartMinute(int routineID, int startMinute){Time::dailyRoutine[routineID].startMinute = startMinute;}
        inline static void setRoutineEndHour(int routineID, int endHour){Time::dailyRoutine[routineID].endHour = endHour;}
        inline static void setRoutineEndMinute(int routineID, int endMinute){Time::dailyRoutine[routineID].endMinute = endMinute;}
        inline static void setRoutineName(int routineID, string routineName){Time::dailyRoutine[routineID].routineName = routineName;}
        inline static int getHour(){return hour;}
        inline static int getMinute(){return minute;}
        inline static bool getCurrentDay(){return currentDay;}
        inline static bool getDayCounter(){return dayCounter;}
        inline static int getRoutinesNumber(){return routinesNumber;}
        inline static bool getGameIsRunning(){return gameIsRunning;}
        inline static int getMAXNUMROUTINES(){return MAXNUMROUTINES;}
        inline static int getRoutineStartHour(int routineID){return dailyRoutine[routineID].startHour;}
        inline static int getRoutineStartMinute(int routineID){return dailyRoutine[routineID].startMinute;}
        inline static int getRoutineEndHour(int routineID){return dailyRoutine[routineID].endHour;}
        inline static int getRoutineEndMinute(int routineID){return dailyRoutine[routineID].endMinute;}
        inline static string getRoutineName(int routineID){return dailyRoutine[routineID].routineName;}
        inline static string getDayOfWeek(int currentDay){return Time::daysOfWeek[currentDay];}

    private:
        static int routinesNumber;
        static bool gameIsRunning;
        static int hour;            // Usar Time::hour
        static int minute;          // Usar Time::minute
        const static int MAXNUMDAYSOFWEEK = 7;
        const static int MAXNUMROUTINES = 11;
        static Routine dailyRoutine[MAXNUMROUTINES]; 
        const static string daysOfWeek[MAXNUMDAYSOFWEEK];
        static int dayCounter;
        static int currentDay;
        void createTimeFile() const;
};

#endif