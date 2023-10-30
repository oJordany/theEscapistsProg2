#ifndef TIME_H
#define TIME_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "Data.h"

#include <iostream>
using std::ostream;

struct Routine {
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    string routineName;
};

class Time{
    friend ostream &operator<<(ostream &, const Time &);

    public:
        Time();
        Time(string);
        Time(const Time &);
        ~Time();

        static void displayTime();
        static void startTime(Routine [], int, const Data &);
        static void skipTime(int, int);
        static void useTime(const Time &);
        static void releaseTime(string);
        static void releaseAllTimes();
        static void endTime();

        // métodos inline usados para incrementar hora, minuto, contador de dias e dia atual
        inline static void incrementHour(){Time::hour++;}
        inline static void incrementMinute(){Time::minute++;}
        inline static void incrementDayCounter(){Time::dayCounter++;}
        inline static void incrementCurrentDay(){Time::currentDay++;}
        
        //gets
        inline string getFileName(){return timeName;}
        inline static int getHour(){return hour;}
        inline static int getMinute(){return minute;}
        inline static bool getCurrentDay(){return currentDay;}
        inline static bool getDayCounter(){return dayCounter;}
        inline static bool getGameIsRunning(){return gameIsRunning;}
        inline static int getRoutinesNumber(){return routinesNumber;}
        inline static int getRoutineStartHour(int routineID){return dailyRoutinePtr[routineID].startHour;}
        inline static int getRoutineStartMinute(int routineID){return dailyRoutinePtr[routineID].startMinute;}
        inline static int getRoutineEndHour(int routineID){return dailyRoutinePtr[routineID].endHour;}
        inline static int getRoutineEndMinute(int routineID){return dailyRoutinePtr[routineID].endMinute;}
        inline static string getRoutineName(int routineID){return dailyRoutinePtr[routineID].routineName;}
        inline static string getDAYSOFTHEWEEK(int currentDay){return Time::DAYSOFTHEWEEK[currentDay];}

        //Operadores
        const Time & operator=(const Time &);
        bool operator==(const Time &) const;   
        bool operator!=(const Time &) const;   
        bool operator!() const;   

    private: 
        string timeName;
        static Routine *dailyRoutinePtr;                             // Array static para guardar a rotina diária na prisão
        static int routinesNumber;
        static Data *prisonDatePtr;
        static vector<string> createdTimes;
        static vector<string> filesInUse;
        static bool gameIsRunning;
        static int hour;            
        static int minute;          
        const static int MAXNUMDAYSOFTHEWEEK = 7;
        const static string DAYSOFTHEWEEK[MAXNUMDAYSOFTHEWEEK];   // Array const static para guardar o nome de cada dia da semana
        static int dayCounter;
        static int currentDay;
        void createTimeFile() const;
};

#endif //TIME_H