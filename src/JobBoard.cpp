#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
using std::left;
using std::right;

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

JobBoard::JobBoard(){
    // Initializing tasks
    tasks[0] = {"Laundry position", "Your criminal attitude stinks, and so do your overalls! Phew! The only thing I want to smell on you inmates is the fresh scent of justice.Take dirty outfits from the bin and place them into the washer. Once spun, take them out and put them into the clean outfit container.The washing machines flash a yellow colour and make a noise when they have finished washing the outfit you put in.", ""};
    tasks[1] = {"Janitor position", "Clean up your act and clean up our floors whilst you're at it! I want you to make those floors, the foundations of YOUR reform, look the best", ""};
    tasks[2] = {"Mail man position", "I hate to be the bearer of bad news, which is why I'm asking you to do it for me. Collect mail from the mail room and deliver it to the inmates it's addressed to.", ""};
    tasks[3] = {"Metal shop position", "The automotive industry is booming! The only booming you will hear is the sound of license plates being pressed. The harder you work, the sooner I get my sporty little convertible.Take metal sheets from the container in the metalshop and use them on the presses to create license plates. Put the finished plates in the relevant container.", ""};
    tasks[4] = {"Kitchen position", "The inspectors call it hazardous, I call it \"rustic\". A sense of taste and/or smell is not essential. Don't worry about washing your hands.Take uncooked food from the freezer in the kitchen and place them in the ovens. Once cooked, take them out and put them on the serving trays in the diner.", ""};
}

JobBoard::JobBoard(const JobBoard& other){
    for (int i = 0; i < this->NUMTASKS; i++) {
        this->tasks[i].taskName = other.tasks[i].taskName;
        this->tasks[i].taskDetails = other.tasks[i].taskDetails;
        this->tasks[i].inmateName = other.tasks[i].inmateName;
    }
}


int JobBoard::findNextAvailableTasks() const{
    for (int i = 0; i < NUMTASKS; i++){
        if(tasks[i].inmateName == ""){
            return i;
        }
    }
    return -1;
}

void JobBoard::assignTask(const Inmate& other){
    int taskIndex = findNextAvailableTasks();
    if (taskIndex != -1){
        tasks[taskIndex].inmateName = other.getName();
    }else{
        setIsAvailable(false);
    }
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
    cout << "   | |" << RED << "  1." << left << setw(19) << tasks[0].taskName << ": " << left << setw(11) << tasks[0].inmateName;
    cout << "2." << left << setw(19) << tasks[1].taskName << ": " << left << setw(13) << tasks[1].inmateName << RESET <<"| |\n";;
    cout << "   | |";
    repeatCharacter(" ", 72);
    cout << "| |\n";
    cout << "   | |" << RED << "  3." << left << setw(19) << tasks[2].taskName << ": " << left << setw(11) << tasks[2].inmateName;
    cout << "4." << left << setw(19) << tasks[3].taskName << ": " << left << setw(13) << tasks[3].inmateName << RESET << "| |\n";;
    cout << "   | |";
    repeatCharacter(" ", 72);
    cout << "| |\n";
    cout << "   | |" << RED << "  5." << left << setw(19) << tasks[4].taskName << ": " << left << setw(11) << tasks[4].inmateName << RESET;
    repeatCharacter(" ", 36);
    cout << "| |\n";
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
cout << BLUE << left << setw(19) << tasks[taskIndex-1].taskName << RESET << "       |.\n";
cout << right << setw(64) << " \\_ |                                |.\n";
printFormatted(tasks[taskIndex-1].taskDetails, "    | ",  " |.", 30, 30);
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

JobBoard::~JobBoard(){
    //...
}