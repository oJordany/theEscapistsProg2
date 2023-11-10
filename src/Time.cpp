#include <iostream>
using std::cout;

#include <fstream>
using std::ios;
using std::ofstream;
using std::remove;

#include <chrono>
using std::chrono::seconds;

#include <thread>
using std::this_thread::sleep_for;
using std::thread;

#include <iomanip>
using std::setw;
using std::setfill;
using std::to_string;

#include <algorithm>
using std::for_each;

#include "Time.h"

bool Time::gameIsRunning = false;
int Time::hour = 0;
int Time::minute = 0;
int Time::dayCounter = 0;
int Time::currentDay = 0;
int Time::routinesNumber = 0;
const string Time::DAYSOFTHEWEEK[MAXNUMDAYSOFTHEWEEK] = { 
                                                    "Sunday", 
                                                    "Monday", 
                                                    "Tuesday", 
                                                    "Wednesday", 
                                                    "Thursday", 
                                                    "Friday", 
                                                    "Saturday" 
                                                  };
Routine *Time::dailyRoutinePtr = 0;
vector<string> Time::createdTimes;
vector<string> Time::filesInUse;
Data *Time::datePtr = 0;

Time::Time(){
    timeName = "Time_" + to_string(hour) + to_string(minute) + to_string(dayCounter);
    int differentiator = 0;
    for (auto createdTimeName : createdTimes){
        if (timeName == createdTimeName){
            differentiator++;
            timeName += to_string(differentiator);
        }
    }
    createdTimes.push_back(timeName);
    createTimeFile();
}

Time::Time(string timeName){
    this->timeName = timeName;
    int differentiator = 0;
    for (auto createdTimeName : createdTimes){
        if (this->timeName == createdTimeName){
            differentiator++;
            this->timeName += to_string(differentiator);
        }
    }
    createdTimes.push_back(this->timeName);
    createTimeFile();
}

Time::Time(const Time& other){
    timeName = other.timeName + "_copy";
    int differentiator = 0;
    for (auto createdTimeName : createdTimes){
        if (timeName == createdTimeName){
            differentiator++;
            timeName += to_string(differentiator);
        }
    }
    createdTimes.push_back(timeName);
    createTimeFile();
}

void Time::endTime(){
    Time::gameIsRunning = false;
    Time::hour = 0;
    Time::minute = 0;
    Time::dayCounter = 0;
    Time::currentDay = 0;
    Time::routinesNumber = 0;
    Time::dailyRoutinePtr = 0;
    Time::createdTimes.resize(0);
    Time::filesInUse.resize(0);
    Time::datePtr = 0;
}

void Time::useTime(const Time &time){
    if (!(!time))
        filesInUse.push_back(time.timeName);
}

void Time::releaseTime(string timeName){
    int i = 0;
    for (auto timeNameInUse : filesInUse){
        if (timeName == timeNameInUse)
            break;
        i++;
    }
    filesInUse.erase(filesInUse.begin() + i);
}

void Time::releaseAllTimes(){
    for_each(Time::filesInUse.begin(), Time::filesInUse.end(), Time::releaseTime);
}

void Time::createTimeFile() const{ 
    gameIsRunning = true;
    string timeNameTxt = timeName + ".txt";
    thread clockThread([timeNameTxt, this](){
        bool isRoutine = false;
        while (gameIsRunning)
        {   
            ofstream file(timeNameTxt, ios::out);
            if (!file.is_open()){
                cout << "Erro ao tentar abrir o arquivo\n";
                return;
            }
            bool fileFound = false;
            for (auto fileInUse : filesInUse){
                if (timeName == fileInUse){
                    fileFound = true;
                    break;
                }
            }
            if (fileFound){
                isRoutine = false;
                for (int i = 0; i <= routinesNumber; i++){
                    if (hour >= dailyRoutinePtr[i].startHour && hour <= dailyRoutinePtr[i].endHour &&
                        minute >= dailyRoutinePtr[i].startMinute && minute <= dailyRoutinePtr[i].endMinute){
                        file << DAYSOFTHEWEEK[currentDay] << " - " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << " ( Day " << dayCounter << " - " << *datePtr << " ) - [ " << Time::dailyRoutinePtr[i].routineName << " ] \n";
                        isRoutine = true;
                        break;
                    }
                }
                if (!isRoutine){
                    file << Time::DAYSOFTHEWEEK[currentDay] << " - " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << " ( Day " << dayCounter << " - " << *datePtr << " )\n";
                }
                setfill(' ');
            }else{
                file << " ";
            }
            file.flush();
            sleep_for(seconds(1));
            file.close();
        }
    });
    clockThread.detach();
}

void Time::displayTime(){ 
    setfill(' ');
    for (int i = 0; i <= routinesNumber; i++){
        if  (dailyRoutinePtr != 0 && hour >= dailyRoutinePtr[i].startHour && hour <= dailyRoutinePtr[i].endHour &&
            minute >= dailyRoutinePtr[i].startMinute && minute <= dailyRoutinePtr[i].endMinute){
            cout << DAYSOFTHEWEEK[currentDay] << " - ";
            cout << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
            cout << " ( Day " << dayCounter << " - " << *datePtr << " ) - [ " << dailyRoutinePtr[i].routineName << " ] \n" << setfill(' ');
            return;
        }
    }
    if (datePtr != 0){
        cout << DAYSOFTHEWEEK[currentDay] << " - ";
        cout << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
        cout << " ( Day " << dayCounter << " - " << *datePtr << " ) \n" << setfill(' ');
        return;
    }
    cout << DAYSOFTHEWEEK[currentDay] << " - ";
    cout << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
    cout << " ( Day " << dayCounter << " ) \n" << setfill(' ');
}

void Time::startTime(Routine dailyRoutinePtr[], 
                    int routinesNumber, 
                    const Data &startDate,
                    int startHour,
                    int startMinute, 
                    int dayCounter, 
                    int currentDay){
    if (routinesNumber > 0){
        datePtr = new Data(startDate);
        Time::dayCounter = dayCounter;
        Time::currentDay = currentDay;
        Time::routinesNumber = routinesNumber;
        Time::dailyRoutinePtr = new Routine[routinesNumber]; 
        Time::gameIsRunning = true;
        Time::hour = (startHour < 0) ? dailyRoutinePtr[0].startHour : startHour;
        Time::minute = (startMinute < 0) ? dailyRoutinePtr[0].startMinute : startMinute;

        // loop for usando para iterar sobre o array de Routine
        // Ele faz a cópia do array dailyRoutine (parâmetro) para o array Time::dailyRoutine (atributo) 
        for (int i = 0; i < routinesNumber; i++){
            Time::dailyRoutinePtr[i].startHour = dailyRoutinePtr[i].startHour;
            Time::dailyRoutinePtr[i].startMinute = dailyRoutinePtr[i].startMinute;
            Time::dailyRoutinePtr[i].endHour = dailyRoutinePtr[i].endHour; 
            Time::dailyRoutinePtr[i].endMinute = dailyRoutinePtr[i].endMinute;
            Time::dailyRoutinePtr[i].routineName = dailyRoutinePtr[i].routineName;
        }

        thread clockThread([](){
            // usando loop while que fica rodando enquanto o jogo estiver rodando
            // esse loop é responsável por incrementar o tempo do jogo em uma thread que opera em segundo plano
            while (gameIsRunning){
                sleep_for(seconds(1));
                // método inline para incrementar os minutos
                Time::incrementMinute();
                if (minute >= 60){
                    Time::minute = 0;
                    // método inline para incrementar as horas
                    Time::incrementHour();
                    if (hour >= 24){
                        Time::hour = 0;
                        // Avanca para o proximo dia
                        // método inline para incrementar o contador de dias
                        Time::incrementDayCounter();
                        // método inline para incrementar o dia atual (dia da semana)
                        Time::incrementCurrentDay();
                        if (Time::currentDay >= 6){
                            Time::currentDay = 0;
                        }
                        datePtr->incrementaData();
                    }
                }
            }
        });
        clockThread.detach();
    } else {
        cout << "Quantidade de rotinas fora do intervalo permitido!\n";
    }
}

void Time::skipTime(int hour, int minute){
    if (hour >= 0 && hour < 24){
        if (Time::hour < hour){
            Time::hour = hour;
        }else{
            Time::hour = hour;
            Time::incrementDayCounter();
            Time::incrementCurrentDay();
            datePtr->incrementaData();
        }        
    }
    if (minute >= 0 && minute <= 60){
        Time::minute = minute;
    }
}

json Time::toJson(){
    json timeJson;
    json dateJson;
    dateJson["dia"] = datePtr->getDia();
    dateJson["mes"] = datePtr->getMes();
    dateJson["ano"] = datePtr->getAno();
    timeJson["startDate"] = dateJson;
    timeJson["startHour"] = Time::hour;
    timeJson["startMinute"] = Time::minute;
    timeJson["dayCounter"] = Time::dayCounter;
    timeJson["currentDay"] = Time::currentDay;

    return timeJson;
}

ostream &operator<<(ostream &out, const Time &time){
    out << setfill('-') << setw(36) << time.timeName << setfill('-') << setw(36) << "\n";

    for (int i = 0; i <= Time::routinesNumber; i++){
        if  (Time::hour >= Time::dailyRoutinePtr[i].startHour && Time::hour <= Time::dailyRoutinePtr[i].endHour &&
            Time::minute >= Time::dailyRoutinePtr[i].startMinute && Time::minute <= Time::dailyRoutinePtr[i].endMinute){
            out << Time::DAYSOFTHEWEEK[Time::currentDay] << " - ";
            out << setfill('0') << setw(2) << Time::hour << ":" << setfill('0') << setw(2) << Time::minute;
            out << " ( Day " << Time::dayCounter << " - " << *Time::datePtr<< " ) - [ " << Time::dailyRoutinePtr[i].routineName << " ] \n";
            out << "File is in use: " << !time << "\n";
            out << setfill('-') << setw(time.timeName.length() + 65) << "\n";
            return out;
        }
    }
    out << Time::DAYSOFTHEWEEK[Time::currentDay] << " - ";
    out << setfill('0') << setw(2) << Time::hour << ":" << setfill('0') << setw(2) << Time::minute;
    out << " ( Day " << Time::dayCounter << " - " << *Time::datePtr << " ) \n";

    out << setfill(' ');
    out << "File is in use: " << !time << "\n";
    return out;
}

const Time & Time::operator=(const Time &time){
    this->timeName = time.timeName;
    int differentiator = 0;
    for (auto createdTimeName : createdTimes){
        if (this->timeName == createdTimeName){
            differentiator++;
            this->timeName += to_string(differentiator);
        }
    }
    createdTimes.push_back(this->timeName);
    createTimeFile();
    if (!time)
        Time::useTime(*this);

    return *this;
}

bool Time::operator==(const Time &time) const{
    return (!*this && !time) || (!(!*this) && !(!time)); // Se e somente se (só retorna true se ambos estiverem em uso OU se ambos não tiverem em uso)
}

bool Time::operator!=(const Time &time) const{
    return !(*this == time);
}

bool Time::operator!() const{
    bool fileIsInUse = false;
    for (auto fileInUse : Time::filesInUse){
        if (fileInUse == this->timeName){
            fileIsInUse = true;
            break;
        }
    }
    return fileIsInUse;
}

Time::~Time(){
    if (Time::gameIsRunning){
        gameIsRunning = false;
        string timeNameTxt = timeName + ".txt";
        if (remove(timeNameTxt.c_str()) != 0) {
            cout << "Erro ao deletar o arquivo\n";
        } else {
            int i = 0;
            for (auto createdTimeName : createdTimes){
                if (this->timeName == createdTimeName)
                    break;
                i++;
            }
            createdTimes.erase(createdTimes.begin() + i);
            cout << "Arquivo deletado com sucesso!\n";
        }
    }

    if (!Time::gameIsRunning && createdTimes.empty()) {
        delete [] dailyRoutinePtr;
        delete datePtr;
        filesInUse.resize(0);
        createdTimes.resize(0);
    }else
        gameIsRunning = true;
}