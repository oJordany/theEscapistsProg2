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

#include "Time.h"

bool Time::gameIsRunning = false;
int Time::hour = 0;
int Time::minute = 0;
int Time::dayCounter = 0;
int Time::currentDay = 0;
int Time::routinesNumber = MAXNUMROUTINES;
const string Time::DAYSOFTHEWEEK[MAXNUMDAYSOFTHEWEEK] = { 
                                                    "Sunday", 
                                                    "Monday", 
                                                    "Tuesday", 
                                                    "Wednesday", 
                                                    "Thursday", 
                                                    "Friday", 
                                                    "Saturday" 
                                                  };
Routine Time::dailyRoutine[MAXNUMROUTINES] = {
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            {0, 0, 0, 0, ""},
                                            };

Time::Time(){
    createTimeFile();
    sleep_for(seconds(2));
}

Time::Time(const Time& other){
    other.createTimeFile();
    sleep_for(seconds(2));
}

void Time::endTime(){
    Time::gameIsRunning= false;
    sleep_for(seconds(1)); // Esse sleep_for é para garantir que o programa apague os arquivos .txt de tempo criados antes de finalizar
}

void Time::createTimeFile() const{
    string timeFileName = "Time_" + to_string(hour) + to_string(minute) + to_string(dayCounter) + ".txt"; 
    thread clockThread([timeFileName](){
        bool isRoutine = false;
        while (gameIsRunning)
        {   
            // cout << timeFileName;
            ofstream file(timeFileName, ios::out);
            if (!file.is_open()){
                cout << "Erro ao tentar abrir o arquivo\n";
                return;
            }
            isRoutine = false;
            for (int i = 0; i <= routinesNumber; i++){
                if (hour >= dailyRoutine[i].startHour && hour <= dailyRoutine[i].endHour &&
                    minute >= dailyRoutine[i].startMinute && minute <= dailyRoutine[i].endMinute){
                    file << DAYSOFTHEWEEK[currentDay] << " - " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << " ( Day " << dayCounter << " ) - [ " << Time::dailyRoutine[i].routineName << " ] \n";
                    isRoutine = true;
                    break;
                }
            }
            if (!isRoutine){
                file << Time::DAYSOFTHEWEEK[currentDay] << " - " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << " ( Day " << dayCounter << " )\n";
            }
            file.flush();
            sleep_for(seconds(1));
            file.close();
        }
        if (remove(timeFileName.c_str()) != 0) {
            cout << "Erro ao deletar o arquivo\n";
        } else {
            cout << "Arquivo deletado com sucesso!\n";
        }
    });
    clockThread.detach();
}

void Time::displayTime(){ 
    for (int i = 0; i <= routinesNumber; i++){
        if  (hour >= dailyRoutine[i].startHour && hour <= dailyRoutine[i].endHour &&
            minute >= dailyRoutine[i].startMinute && minute <= dailyRoutine[i].endMinute){
            cout << DAYSOFTHEWEEK[currentDay] << " - ";
            cout << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
            cout << " ( Day " << dayCounter << " ) - [ " << dailyRoutine[i].routineName << " ] \n";
            return;
        }
    }
    cout << DAYSOFTHEWEEK[currentDay] << " - ";
    cout << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
    cout << " ( Day " << dayCounter << " ) \n";
}

void Time::startTime(Routine dailyRoutine[], int routinesNumber){
    if (routinesNumber <= MAXNUMROUTINES && routinesNumber > 0){
        Time::routinesNumber = routinesNumber;
        Time::gameIsRunning = true;
        if (routinesNumber > 0){
            Time::hour = dailyRoutine[0].startHour;
            Time::minute = dailyRoutine[0].startMinute;
        }
        // loop for usando para iterar sobre o array de Routine
        // Ele faz a cópia do array dailyRoutine (parâmetro) para o array Time::dailyRoutine (atributo) 
        for (int i = 0; i < routinesNumber; i++){
            Time::dailyRoutine[i].startHour = dailyRoutine[i].startHour;
            Time::dailyRoutine[i].startMinute = dailyRoutine[i].startMinute;
            Time::dailyRoutine[i].endHour = dailyRoutine[i].endHour; 
            Time::dailyRoutine[i].endMinute = dailyRoutine[i].endMinute;
            Time::dailyRoutine[i].routineName = dailyRoutine[i].routineName;
        }
        // cout << routinesNumber << "\n";
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
                        if (currentDay >= 6){
                            Time::currentDay = 0;
                        }
                    }
                }
                // sleep_for(seconds(1));
            }
        });
        clockThread.detach();
    } else {
        cout << "Quantidade de rotinas fora do intervalo permitido!\n";
    }
}

Time::~Time(){

}