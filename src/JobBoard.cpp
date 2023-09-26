#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
using std::left;
using std::right;

#include "JobBoard.h"

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
    tasks[0] = {"Laundry position", "Sua atitude criminosa fede, e seu macacão também! ...", ""};
    tasks[1] = {"Janitor position", "Limpe seu ato e limpe nossos pisos enquanto você faz isso! ...", ""};
    tasks[2] = {"Mail man position", "Odeio ser portador de más notícias, e é por isso que estou pedindo que você faça isso por mim. ...", ""};
    tasks[3] = {"Metal shop position", "A indústria automotiva está crescendo! O único estrondo que você ouvirá é o som das placas sendo pressionadas. ...", ""};
    tasks[4] = {"Kitchen position", "Os inspetores chamam de perigoso, eu chamo de ‘rústico’. O sentido do paladar e/ou olfato não é essencial. ...", ""};
}

JobBoard::JobBoard(const JobBoard& other)
:NUMTASKS(other.NUMTASKS){
    this->tasks = other.tasks;
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
        tasks[taskIndex].inmateName = other.name;
    }
}

void JobBoard::repeatCharacter(string character, int amount) const{
    for (int i = 0; i < amount; i++){
        cout << character;
    }
}

void JobBoard::displayTasks() const{
    repeatCharacter("-", 57);

    
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
_|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|__
}