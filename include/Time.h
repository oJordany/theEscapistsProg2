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
        static void startTime(Routine [], int);
        static void endTime();

        // métodos inline usados para incrementar hora, minuto, contador de dias e dia atual
        inline static void incrementHour(){Time::hour++;}
        inline static void incrementMinute(){Time::minute++;}
        inline static void incrementDayCounter(){Time::dayCounter++;}
        inline static void incrementCurrentDay(){Time::currentDay++;}
        
        //gets
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
        inline static string getDAYSOFTHEWEEK(int currentDay){return Time::DAYSOFTHEWEEK[currentDay];}

    private:
        static int routinesNumber;
        static bool gameIsRunning;
        static int hour;            
        static int minute;          
        const static int MAXNUMDAYSOFTHEWEEK = 7;
        const static int MAXNUMROUTINES = 11;
        static Routine dailyRoutine[MAXNUMROUTINES];        // Array static para guardar a rotina diária na prisão
        const static string DAYSOFTHEWEEK[MAXNUMDAYSOFTHEWEEK];   // Array const static para guardar o nome de cada dia da semana
        static int dayCounter;
        static int currentDay;
        void createTimeFile() const;
};

#endif