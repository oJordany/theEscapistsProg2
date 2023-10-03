#include <iostream>
using std::cout;
using std::cin;

#include "Inmate.h"
#include "JobBoard.h"
#include "Time.h"
// #include "Inmate.cpp"

int main(){
    int option = 1;

    Routine dailyRoutinePrison1[11] = {
        {5, 0, 5, 59, "Wake Up Call, Roll Call"},
        {6, 0, 6, 59, "Breakfast Time"},
        {7, 0, 8, 59, "Job Time"},
        {9, 0, 9, 59, "Exercise Time"},
        {10, 0, 11, 59, "Free Time"},
        {12, 0, 12, 59, "Lunch Time"},
        {13, 0, 13, 59, "Roll Call"},
        {14, 0, 15, 59, "Job Time"},
        {16, 0, 16, 59, "Shower Time"},
        {17, 0, 17, 59, "Dinner Time"},
        {18, 0, 18, 59, "Free Time"},
    };
    cout << "usando método static void startTime(Routine [], int) para iniciar o tempo do jogo\n";
    Time::startTime(dailyRoutinePrison1, 11);
    cout << "atributo static bool gameIsRunning: " << Time::getGameIsRunning() << "\n";
    cout << "atribuito static int hour: " << Time::getHour() << "\n";
    cout << "atribuito static int minute: " << Time::getMinute() << "\n";
    cout << "atributo const static int MAXNUMROUTINES = " << Time::getMAXNUMROUTINES() << "\n";
    cout << "método static void displayTime() para visualizar informações do tempo atual no terminal\n";
    Time::displayTime();
    cout << "instanciando objeto time_1\n*Esse objeto é um arquivo criado que fica sendo atualizado constantemente*\n";
    Time time_1;
    cout << "instanciando objeto TIME_1_COPY com construtor de cópia\n*outro arquivo criado que fica sendo atualizado constantemente\n*";
    const Time TIME_1_COPY(time_1);
    while(option != 0){
        cout << "Simulando a execução do programa...\n";
        cout << "Para sair do jogo, digite 0: ";
        cin >> option;
    }
    cout << "usando método static void endTime() para finalizar o tempo do jogo e remover os arquivos de tempo\n";
    Time::endTime();
}