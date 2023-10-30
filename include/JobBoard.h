#ifndef JOB_BOARD_H
#define JOB_BOARD_H

#include "Inmate.h"
#include <string>

using std::string;

#include <iostream>
using std::cout;
using std::ostream;

struct Task
{
    string taskName;
    string taskDetails;
    Inmate *inmate;
};

class JobBoard
{
    friend ostream & operator<<(ostream &, const JobBoard &);
    public:
        JobBoard();
        JobBoard(Task [], int);
        JobBoard(const JobBoard &);
        ~JobBoard();

        void displayTasks() const;
        void viewTasksDetails(int) const;
        void assignTaskTo(const Inmate &);
        void unassignTask(int);
        bool getIsAvailable() const;
        inline int getNextEntrieInTasks() const{return this->nextEntrieInTasks;}
        void setIsAvailable(bool);
        void setTasksSize(int);
        void registerTask(Task);

        const JobBoard & operator=(const JobBoard &);
        bool operator==(const JobBoard &) const;
        bool operator!=(const JobBoard &) const;
        int operator!() const;

    private:
        Task *tasksPtr;
        int tasksSize;
        int nextEntrieInTasks;
        bool isAvailable;

        void repeatCharacter(string, int) const;
        void printFormatted(string, string, string, int=26, int=60) const;
        int findNextAvailableTasks() const;
        void allocateTask(Task);
};

#endif