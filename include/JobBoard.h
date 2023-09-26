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

private:
    struct Task
    {
        string taskName;
        string taskDetails;
        string inmateName;
    };

    const int NUMTASKS = 5;
    Task tasks[NUMTASKS];

    void repeatCharacter(string, int) const;
    int findNextAvailableTasks() const;
};

#endif