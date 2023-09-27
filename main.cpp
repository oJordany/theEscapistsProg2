#include <iostream>
using std::cout;
using std::cin;

#include "Inmate.h"
#include "JobBoard.h"
// #include "Inmate.cpp"

int main(){
    int taskIndex;
    cout << "Utilizando Inmate definindo seus atributos\n";
    Inmate prisoner01("Lucivaldo Jr", 100, 83, 71, 48, 26, 5.50);
    cout << "Como o maximo de caracteres permitidos para o nome é 10, será usado apenas Lucivaldo\n";
    cout << "Utilizando viewProfile() para visualizar o perfil de prisoner01:\n";
    prisoner01.viewProfile();
    cout << "Utilizando setEnergy(15) para alterar a energia do prisioneiro\n";
    prisoner01.setEnergy(15);
    cout << "Utilizando readBook(30) para aumentar +30 na inteligência\n";
    prisoner01.readBook(30);

    cout << "Utilizando JobBoard para criar um quadro de trabalhos\n";
    JobBoard jobboard;
    cout << "Visualizando estado do atributo isAvailable após iniciar JobBoard\n";
    cout << jobboard.getIsAvailable();
    cout << "Designando task para o prisoner01 com assignTask()\n";
    jobboard.assignTask(prisoner01);
    cout << "Utilizando o construtor de cópia da classe Inmate 4x para designar mais tasks\n";
    const Inmate PRISONER02(prisoner01);
    const Inmate PRISONER03(prisoner01);
    const Inmate PRISONER04(prisoner01);
    const Inmate PRISONER05(prisoner01);
    cout << "Designando tasks para todos os novos prisioneiros copiados\n";
    jobboard.assignTask(PRISONER02);
    cout << "Utilizando viewProfile() para visualizar o perfil de PRISONER02:\n";
    PRISONER02.viewProfile();
    jobboard.assignTask(PRISONER03);
    cout << "Utilizando viewProfile() para visualizar o perfil de PRISONER03:\n";
    PRISONER03.viewProfile();
    jobboard.assignTask(PRISONER04);
    cout << "Utilizando viewProfile() para visualizar o perfil de PRISONER04:\n";
    PRISONER04.viewProfile();
    jobboard.assignTask(PRISONER05);
    cout << "Utilizando viewProfile() para visualizar o perfil de PRISONER05:\n";
    PRISONER05.viewProfile();
    cout << "Utilizando displayTasks() para ver as tasks do quadro de trabalho\n";
    jobboard.displayTasks();
    cout << "Selecione qual task vc deseja ver mais detalhes [digite -1 para sair]: ";
    cin >> taskIndex;
    jobboard.viewTasksDetails(taskIndex);
    cout << "Visualizando estado do atributo isAvailable após preencher todas as tasks do JobBoard:\n";
    cout << jobboard.getIsAvailable() << "\n";

    cout << "Criando um novo JobBoard com as mesmas atribuições de tasks do JobBoard anterior\n";
    const JobBoard JOBBOARD02(jobboard);
    cout << "Utilizando displayTasks() para ver as tasks do quadro de trabalho de JOBBOARD02\n";
    JOBBOARD02.displayTasks();
}