#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
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
    // Initializing tasks
    // tasks[0] = {"Laundry position", "Your criminal attitude stinks, and so do your overalls! Phew! The only thing I want to smell on you inmates is the fresh scent of justice.Take dirty outfits from the bin and place them into the washer. Once spun, take them out and put them into the clean outfit container.The washing machines flash a yellow colour and make a noise when they have finished washing the outfit you put in.", ""};
    // tasks[1] = {"Janitor position", "Clean up your act and clean up our floors whilst you're at it! I want you to make those floors, the foundations of YOUR reform, look the best", ""};
    // tasks[2] = {"Mail man position", "I hate to be the bearer of bad news, which is why I'm asking you to do it for me. Collect mail from the mail room and deliver it to the inmates it's addressed to.", ""};
    // tasks[3] = {"Metal shop position", "The automotive industry is booming! The only booming you will hear is the sound of license plates being pressed. The harder you work, the sooner I get my sporty little convertible.Take metal sheets from the container in the metalshop and use them on the presses to create license plates. Put the finished plates in the relevant container.", ""};
    // tasks[4] = {"Kitchen position", "The inspectors call it hazardous, I call it \"rustic\". A sense of taste and/or smell is not essential. Don't worry about washing your hands.Take uncooked food from the freezer in the kitchen and place them in the ovens. Once cooked, take them out and put them on the serving trays in the diner.", ""};
}

JobBoard::JobBoard(Task tasks[], int size)
:nextEntrieInTasks(0), tasksSize(size), isAvailable(false){
    tasksPtr = new Task[tasksSize];
    for (int i = 0; i < size; i++){
        tasksPtr[i].taskName = tasks[i].taskName;
        tasksPtr[i].taskDetails = tasks[i].taskDetails;
        if (!isAvailable && tasks[i].inmate->isNull())
            isAvailable = true;
        tasksPtr[i].inmate = tasks[i].inmate;
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
    int taskIndex = findNextAvailableTasks();
    if (taskIndex != -1){
        tasksPtr[taskIndex].inmate = &other;
    }else{
        setIsAvailable(false);
    }
}

void JobBoard::unassignTaskTo(const Inmate& other){
    for (int i = 0; i < nextEntrieInTasks; i++){
        if (tasksPtr[i].inmate == &other){
            // delete tasksPtr[i].inmate;
            tasksPtr[i].inmate = nullptr;
        }
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
            cout << "   | |" << RED << "  " << i << "." << left << setw(19) << tasksPtr[i].taskName << ": " << left << setw(11);
            if (!tasksPtr[i].inmate->isNull())
                cout << tasksPtr[i].inmate->getName();
            else
                cout << "";
        }else if((i+1)%2 == 0){
            cout << i << "." << left << setw(19) << tasksPtr[i].taskName << ": " << left << setw(13);
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
    }

    this->isAvailable = true;
}

bool JobBoard::getIsAvailable() const {
    return this->isAvailable;
}

ostream & operator<<(ostream &out, const JobBoard &jobBoard){
    for (int i=0; i < jobBoard.nextEntrieInTasks; i++){
        out << "Task name: " << jobBoard.tasksPtr[i].taskName << "\n";
        out << "Assigned prisoner: " << jobBoard.tasksPtr[i].inmate->getName() << "\n"; 
    }
    return out;
}

const JobBoard &JobBoard::operator=(const JobBoard &jobBoard){
    this->isAvailable = jobBoard.isAvailable;
    this->tasksSize = jobBoard.tasksSize;
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
    
    for (int i=0; i < nextEntrieInTasks; i++){
        if (this->tasksPtr[i].taskName != jobBoard.tasksPtr[i].taskName)
            return false;

        if (this->tasksPtr[i].taskDetails != jobBoard.tasksPtr[i].taskDetails)
            return false;

        if (this->tasksPtr[i].inmate != jobBoard.tasksPtr[i].inmate)
            return false;
    }
    return true;
}

bool JobBoard::operator!=(const JobBoard &jobBoard) const{
    return !(*this == jobBoard);
}

bool JobBoard::operator!() const{
    return tasksSize != 0;
}

JobBoard::~JobBoard(){
    delete [] tasksPtr;
}