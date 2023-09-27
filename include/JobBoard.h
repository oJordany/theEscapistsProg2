#ifndef JOB_BOARD_H
#define JOB_BOARD_H

#include "Inmate.h"
#include <string>

using std::string;


class JobBoard
{
public:
    JobBoard();
    JobBoard(const JobBoard &);
    ~JobBoard();

    void displayTasks() const;
    void viewTasksDetails(int) const;
    void assignTask(const Inmate &);
    bool getIsAvailable() const;
    void setIsAvailable(bool);

private:
    struct Task
    {
        string taskName;
        string taskDetails;
        string inmateName;
    };

    static const int NUMTASKS = 5;
    Task tasks[NUMTASKS];
    bool isAvailable;

    void repeatCharacter(string, int) const;
    void printFormatted(string, string, string, int=26, int=60) const;
    int findNextAvailableTasks() const;
};

#endif