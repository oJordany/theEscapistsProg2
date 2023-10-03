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
const string Time::daysOfWeek[MAXNUMDAYSOFWEEK] = { 
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
    Time::setGameIsRunning(false);
    sleep_for(seconds(1)); // Esse sleep_for é para garantir que o programa apague os arquivos .txt de tempo criados antes de finalizar
}

void Time::createTimeFile() const{
    string timeFileName = "Time_" + to_string(Time::getHour()) + to_string(Time::getMinute()) + to_string(Time::getDayCounter()) + ".txt"; 
    thread clockThread([timeFileName](){
        bool isRoutine = false;
        while (Time::getGameIsRunning())
        {   
            // cout << timeFileName;
            ofstream file(timeFileName, ios::out);
            if (!file.is_open()){
                cout << "Erro ao tentar abrir o arquivo\n";
                return;
            }
            isRoutine = false;
            for (int i = 0; i <= Time::getRoutinesNumber(); i++){
                if (Time::getHour() >= Time::getRoutineStartHour(i) && Time::getHour() <= Time::getRoutineEndHour(i) &&
                    Time::getMinute() >= Time::getRoutineStartMinute(i) && Time::getMinute() <= Time::getRoutineEndMinute(i)){
                    file << Time::getDayOfWeek(Time::getCurrentDay()) << " - " << setfill('0') << setw(2) << Time::getHour() << ":" << setfill('0') << setw(2) << Time::getMinute() << " ( Day " << Time::getDayCounter() << " ) - [ " << Time::getRoutineName(i) << " ] \n";
                    isRoutine = true;
                    break;
                }
            }
            if (!isRoutine){
                file << Time::getDayOfWeek(Time::getCurrentDay()) << " - " << setfill('0') << setw(2) << Time::getHour() << ":" << setfill('0') << setw(2) << Time::getMinute() << " ( Day " << Time::getDayCounter() << " )\n";
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
    for (int i = 0; i <= Time::getRoutinesNumber(); i++){
        if  (Time::getHour() >= Time::getRoutineStartHour(i) && Time::getHour() <= Time::getRoutineEndHour(i) &&
            Time::getMinute() >= Time::getRoutineStartMinute(i) && Time::getMinute() <= Time::getRoutineEndMinute(i)){
            cout << Time::getDayOfWeek(Time::getCurrentDay()) << " - ";
            cout << setfill('0') << setw(2) << Time::getHour() << ":" << setfill('0') << setw(2) << Time::getMinute();
            cout << " ( Day " << Time::getDayCounter() << " ) - [ " << Time::getRoutineName(i) << " ] \n";
            return;
        }
    }
    cout << Time::getDayOfWeek(Time::getCurrentDay()) << " - ";
    cout << setfill('0') << setw(2) << Time::getHour() << ":" << setfill('0') << setw(2) << Time::getMinute();
    cout << " ( Day " << Time::getDayCounter() << " ) \n";
}

void Time::startTime(Routine dailyRoutine[], int routinesNumber){
    if (routinesNumber <= Time::getMAXNUMROUTINES() && routinesNumber > 0){
        Time::setRoutinesNumber(routinesNumber);
        Time::setGameIsRunning(true);
        if (routinesNumber > 0){
            Time::setHour(dailyRoutine[0].startHour);
            Time::setMinute(dailyRoutine[0].startMinute);
        }
        // loop for usando para iterar sobre o array de Routine
        // Ele faz a cópia do array dailyRoutine (parâmetro) para o array Time::dailyRoutine (atributo) 
        for (int i = 0; i < Time::getRoutinesNumber(); i++){
            Time::setRoutineStartHour(i, dailyRoutine[i].startHour); 
            Time::setRoutineStartMinute(i, dailyRoutine[i].startMinute); 
            Time::setRoutineEndHour(i, dailyRoutine[i].endHour); 
            Time::setRoutineEndMinute(i, dailyRoutine[i].endMinute); 
            Time::setRoutineName(i, dailyRoutine[i].routineName); 
        }
        // cout << Time::getRoutinesNumber() << "\n";
        thread clockThread([](){
            // usando loop while que fica rodando enquanto o jogo estiver rodando
            // esse loop é responsável por incrementar o tempo do jogo em uma thread que opera em segundo plano
            while (Time::getGameIsRunning()){
                sleep_for(seconds(1));
                // método inline para incrementar os minutos
                Time::incrementMinute();
                if (Time::getMinute() >= 60){
                    Time::setMinute(0);
                    // método inline para incrementar as horas
                    Time::incrementHour();
                    if (Time::getHour() >= 24){
                        Time::setHour(0);
                        // Avanca para o proximo dia
                        // método inline para incrementar o contador de dias
                        Time::incrementDayCounter();
                        // método inline para incrementar o dia atual (dia da semana)
                        Time::incrementCurrentDay();
                        if (Time::getCurrentDay() >= 6){
                            Time::setCurrentDay(0);
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