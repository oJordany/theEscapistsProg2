#ifndef TIME_H
#define TIME_H

#include "string"
using std::string;

struct Routine {
    int hour;
    int minute;
    int second;
    string routineName;
}

class Time{
    public:
        Time(const Routine& dailyRoutine[], int routineNumber);
        Time(const Time &);
        ~Time();

        inline static void incrementHour(){hour++};
        inline static void incrementMinute(){minute++};
        inline static void incrementSecond(){second++};

        void printTime() const;
        static void increaseTime();
        static void checkRoutine();
        static void startTime();

        static void setHour(int i=0);
        static void setMinute(int i=0);
        static void setMinute(int i=0);
        static int getHour() const;
        static int getMinute() const;
        static int getMinute() const;

    private:
        static int hour; // Usar Time::hour
        static int minute; // Usar Time::minute
        static int second; // Usar Time::second
        const static int MAXNUMDAYSOFWEEK = 7;
        const static int MAXNUMROUTINE = 11;
        const static Routine dailyRoutine[MAXNUMROUTINE]; 
        const static string daysOfWeek[MAXNUMDAYSOFWEEK];
        static int currentDay;
}

#endif TIME_H