#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
using std::setfill;
using std::left;
using std::right;

#include <cmath>
using std::ceil;

#include "JobBoard.h"

#define UNDERLINED "\x1b[4m"
#define RESETSTYLE "\x1b[0m"
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m" 

JobBoard::JobBoard()
:nextEntrieInTasks(0), tasksSize(0), tasksPtr(0){
}

JobBoard::JobBoard(Task tasks[], int size)
:nextEntrieInTasks(0), tasksSize(size), isAvailable(false){
    tasksPtr = new Task[tasksSize];
    for (int i = 0; i < size; i++){
        tasksPtr[i].taskName = tasks[i].taskName;
        tasksPtr[i].taskDetails = tasks[i].taskDetails;
        if (!isAvailable && tasks[i].inmate->isNull())
            isAvailable = true;
        tasksPtr[i].inmate = (tasks[i].inmate->isNull()) ? 0 : new Inmate(*tasks[i].inmate);
        nextEntrieInTasks++;
    }
}

JobBoard::JobBoard(const JobBoard& other)
:nextEntrieInTasks(0), tasksSize(other.tasksSize), isAvailable(other.isAvailable){
    tasksPtr = new Task[tasksSize];
    for (int i = 0; i < other.nextEntrieInTasks; i++) {
        this->tasksPtr[i].taskName = other.tasksPtr[i].taskName;
        this->tasksPtr[i].taskDetails = other.tasksPtr[i].taskDetails;
        this->tasksPtr[i].inmate = other.tasksPtr[i].inmate;
        nextEntrieInTasks++;
    }
}


int JobBoard::findNextAvailableTasks() const{
    for (int i = 0; i < nextEntrieInTasks; i++){
        if(tasksPtr[i].inmate->isNull()){
            return i;
        }
    }
    return -1;
}

void JobBoard::assignTaskTo(const Inmate& other){
    if (other.isNull())
        return;

    int taskIndex = findNextAvailableTasks();
    if (taskIndex != -1){
        for (int i = 0; i < nextEntrieInTasks; i++){
            if(tasksPtr[i].inmate != 0 && *tasksPtr[i].inmate == other){
                return;}
        }
        if (tasksPtr[taskIndex].inmate != 0) {
            delete tasksPtr[taskIndex].inmate; // Libera a memória do objeto Inmate anterior
        }
        tasksPtr[taskIndex].inmate = new Inmate(other);
    }else{
        setIsAvailable(false);
    }
}

void JobBoard::unassignTask(int taskIndex){
    if (taskIndex >= 0 && taskIndex < tasksSize) {
        if (tasksPtr[taskIndex].inmate != 0) {
            delete tasksPtr[taskIndex].inmate;
            tasksPtr[taskIndex].inmate = 0; // Define o ponteiro como nulo após a desalocação
            setIsAvailable(true);
        }
    } else {
        cout << RED << "non-existent task index" << RESET << "\n";
    }
}

void JobBoard::registerTask(Task task){
    if (nextEntrieInTasks < tasksSize){
        tasksPtr[nextEntrieInTasks].taskName = task.taskName;
        tasksPtr[nextEntrieInTasks].taskDetails = task.taskDetails;
        tasksPtr[nextEntrieInTasks].inmate = task.inmate;
        nextEntrieInTasks++;
        return;
    }

    if (tasksSize == 0){
        tasksSize = 1;
        tasksPtr = new Task[tasksSize];
        tasksPtr[nextEntrieInTasks].taskName = task.taskName;
        tasksPtr[nextEntrieInTasks].taskDetails = task.taskDetails;
        tasksPtr[nextEntrieInTasks].inmate = task.inmate;
        nextEntrieInTasks++;
        return;
    }

    allocateTask(task);
}

void JobBoard::allocateTask(Task task){
    Task *tasksTempPtr = new Task[tasksSize];

    for (int i = 0; i < nextEntrieInTasks; i++){
        tasksTempPtr[i].taskName = tasksPtr[i].taskName;
        tasksTempPtr[i].taskDetails = tasksPtr[i].taskDetails;
        tasksTempPtr[i].inmate = tasksPtr[i].inmate;
    }

    delete [] tasksPtr;

    tasksSize = int(ceil(tasksSize * 1.5));

    tasksPtr = new Task[tasksSize];

    for (int i=0; i < nextEntrieInTasks; i++){
        tasksPtr[i].taskName = tasksTempPtr[i].taskName;
        tasksPtr[i].taskDetails = tasksTempPtr[i].taskDetails;
        tasksPtr[i].inmate = tasksTempPtr[i].inmate;
    }

    delete [] tasksTempPtr;
}

void JobBoard::repeatCharacter(string character, int amount) const{
    for (int i = 0; i < amount; i++){
        cout << character;
    }
}

void JobBoard::displayTasks() const{
    setfill(' ');
    cout << " __| |";
    repeatCharacter("_", 72);
    cout << "| |__\n";
    cout << "(__ X ";      
    repeatCharacter("_", 30);
    cout << BLUE << UNDERLINED <<" JOB BOARD " << RESET << RESETSTYLE;
    repeatCharacter("_", 31);
    cout << " X __)\n";
    cout << "   | |";
    repeatCharacter(" ", 72);
    cout << "| |\n";
    int i;
    for (i = 0; i < nextEntrieInTasks; i++){
        if ((i+1)%2 != 0){
            cout << "   | |" << RED << "  " << i+1 << "." << left << setw(19) << tasksPtr[i].taskName << ": " << left << setw(11);
            if (!tasksPtr[i].inmate->isNull())
                cout << tasksPtr[i].inmate->getName();
            else
                cout << "";
        }else if((i+1)%2 == 0){
            cout << i+1 << "." << left << setw(19) << tasksPtr[i].taskName << ": " << left << setw(13);
            if (!tasksPtr[i].inmate->isNull())
                cout << tasksPtr[i].inmate->getName() << RESET <<"| |\n";
            else
                cout << "" << RESET << "| |\n";
            
            if (i+1 != nextEntrieInTasks){
                cout << "   | |";
                repeatCharacter(" ", 72);
                cout << "| |\n";
            }
        }
    }
    if ((i)%2 != 0){
        cout << RESET;
        repeatCharacter(" ", 36);
        cout << "| |\n";
    }
    cout << " __| |";
    repeatCharacter("_", 72);
    cout << "| |__\n";
    cout << "(__ X ";
    repeatCharacter("_", 72);
    cout << " X __)\n";
    cout << "   | |";
    repeatCharacter(" ",72);
    cout << "| |\n";

}

void JobBoard::printFormatted(  string text, 
                                string prefix, 
                                string suffix,
                                int width, 
                                int marginLeft
                                ) const 
{
    int start = 0;
    string lineText;
    while (start < text.length()) {
        int end = start + width;
        if (end > text.length()) {
            end = text.length();
        }
        lineText = text.substr(start, end - start);
        if (lineText[0] == ' '){
            lineText = text.substr(start+1, end - start);
        }
        cout << right << setw(marginLeft) << prefix << left << setw(width) << lineText << suffix << "\n";
        start = end;
    }
}


void JobBoard::viewTasksDetails(int taskIndex) const{
    setfill(' ');
    if (taskIndex > nextEntrieInTasks){
        cout << RED << "non-existent task index" << RESET << "\n";
        return;
    }

    cout << right << setw(62) << "   __________________________________\n";
    cout << right << setw(64) << "/ \\                                 \\.\n";
    cout << right << setw(35) << "|   |      ";
    cout << BLUE << left << setw(19) << tasksPtr[taskIndex-1].taskName << RESET << "       |.\n";
    cout << right << setw(64) << " \\_ |                                |.\n";
    printFormatted(tasksPtr[taskIndex-1].taskDetails, "    | ",  " |.", 30, 30);
    cout << right << setw(66) << "    |   _____________________________|___\n";
    cout << right << setw(67) << "    |  /                                /.\n";
    cout << right << setw(66) << "    \\_/________________________________/.\n";
}

void JobBoard::setIsAvailable(bool state){
    int taskIndex = findNextAvailableTasks();
    if (taskIndex == -1 && state == false){
        this->isAvailable = state;
        return;
    }

    this->isAvailable = true;
}

bool JobBoard::getIsAvailable() const {
    return this->isAvailable;
}

void JobBoard::setTasksSize(int tasksSize) {
    if (tasksSize <= 0){
        this->tasksSize = 0;
        delete [] tasksPtr;
        tasksPtr = 0;
        nextEntrieInTasks = 0;
        return;
    }

    if (this->tasksSize == 0){
        this->tasksSize = tasksSize;
        tasksPtr = new Task[tasksSize];
        return;
    }

    Task *tasksTempPtr = new Task[tasksSize];

    int endOfTasks = (tasksSize < this->tasksSize) ? tasksSize : nextEntrieInTasks;

    for (int i = 0; i < endOfTasks; i++){
        tasksTempPtr[i].taskName = tasksPtr[i].taskName;
        tasksTempPtr[i].taskDetails = tasksPtr[i].taskDetails;
        tasksTempPtr[i].inmate = tasksPtr[i].inmate;
    }

    delete [] tasksPtr;

    nextEntrieInTasks = endOfTasks;
    this->tasksSize = tasksSize;

    tasksPtr = new Task[tasksSize];

    for (int i=0; i < endOfTasks; i++){
        tasksPtr[i].taskName = tasksTempPtr[i].taskName;
        tasksPtr[i].taskDetails = tasksTempPtr[i].taskDetails;
        tasksPtr[i].inmate = tasksTempPtr[i].inmate;
    }

    delete [] tasksTempPtr;
}

json JobBoard::toJson() const{
    json jobBoardJson;
    json taskJson;
    for (int i=0; i < nextEntrieInTasks; i++){
        taskJson["taskName"] = tasksPtr[i].taskName;
        taskJson["taskDetails"] = tasksPtr[i].taskDetails;
        jobBoardJson.push_back(taskJson);
    }

    return jobBoardJson;
}

ostream & operator<<(ostream &out, const JobBoard &jobBoard){
    if (!jobBoard.nextEntrieInTasks){
        out << "\n";
    } 
    for (int i=0; i < jobBoard.nextEntrieInTasks; i++){
        string assignedInmate = jobBoard.tasksPtr[i].inmate->isNull() ? "" : jobBoard.tasksPtr[i].inmate->getName();
        out << "Task name: " << jobBoard.tasksPtr[i].taskName << "\n";
        out << "Assigned inmate: " << assignedInmate << "\n\n"; 
    }
    return out;
}

const JobBoard &JobBoard::operator=(const JobBoard &jobBoard){
    this->isAvailable = jobBoard.isAvailable;
    setTasksSize(jobBoard.tasksSize);
    this->nextEntrieInTasks = jobBoard.nextEntrieInTasks;
    for (int i=0; i < jobBoard.nextEntrieInTasks; i++){
        this->tasksPtr[i].taskName = jobBoard.tasksPtr[i].taskName;
        this->tasksPtr[i].taskDetails = jobBoard.tasksPtr[i].taskDetails;
        this->tasksPtr[i].inmate = jobBoard.tasksPtr[i].inmate; 
    }
    return *this;
}

bool JobBoard::operator==(const JobBoard &jobBoard) const{
    if (jobBoard.isAvailable != this->isAvailable)
        return false;

    if (jobBoard.nextEntrieInTasks != this->nextEntrieInTasks)
        return false;

    if (jobBoard.tasksSize != this->tasksSize)
        return false;
    
    // for (int i=0; i < nextEntrieInTasks; i++){
    //     if (this->tasksPtr[i].taskName != jobBoard.tasksPtr[i].taskName)
    //         return false;

    //     if (this->tasksPtr[i].taskDetails != jobBoard.tasksPtr[i].taskDetails)
    //         return false;

    //     if (*this->tasksPtr[i].inmate != *jobBoard.tasksPtr[i].inmate)
    //         return false;
    // }
    return true;
}

bool JobBoard::operator!=(const JobBoard &jobBoard) const{
    return !(*this == jobBoard);
}

int JobBoard::operator!() const{
    return nextEntrieInTasks;
}

JobBoard::~JobBoard(){
    delete [] tasksPtr;
}