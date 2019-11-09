#include <iostream>
#include <string>
#include "Menus.h"
#include "Team.h"
#include "fstream"

using namespace std;
extern Team *national_team;
int info_app()
{
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "This app was created by :" << endl << endl;
    cout << "Diogo Samuel Fernandes" << endl;
    cout << "Hugo Guimaraes" << endl;
    cout << "Joao Pires" << endl << endl;

    cout << "Press [1] to go back to the main menu" << endl;
    cin.clear();
    cin >> menu;
    if (menu == '1') {cin.ignore(1000,'\n'); return 1;}
    else
    {
        cin.ignore(1000,'\n');
        return 0;
    }

}



int menu_staff() {
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "               Staff Menu                 " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View Staff Members " << endl;
    cout << "2. Search Staff Members " << endl;
    cout << "3. Add Staff Members " << endl;
    cout << "0. Return to Main Menu " << endl;

    cin.clear();
    cin >> menu;

    switch(menu)
    {
        case '1':    //View player info
            for(int i = 0; i < (national_team->getStaff()).size(); i++){
                (national_team->getStaff())[i]->info();
                cout << endl;
            }
            cout << "0. Return to Main Menu " << endl;
            cin >> menu;
            return 0;
        case '2':
            return 0;
        case '0':    //Exit function
            return 1;
        case '3':
            return national_team->addStaff();
        default:     //Invalid input
            cin.ignore(1000,'\n');
            return 0;
    }
    return 1;
}
int menu_players()
{
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "               Player Menu                " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View all Players " << endl;
    cout << "2. Search Players " << endl;
    cout << "3. Add Player " << endl;
    cout << "0. Return to Main Menu " << endl;

    cin.clear();
    cin >> menu;

    switch(menu)
    {
        case '1':    //View player info
            for(int i = 0; i < (national_team->getPlayers()).size(); i++){
                (national_team->getPlayers())[i]->info();
                cout << endl;
            }
            cout << "Press any key to go back to Player Menu: " << endl;
            cin >> menu;
            cin.ignore(1000,'\n');
            return 0;//remove this line after inserting stuff
        case '2':    //Exit function
            cout << "Write the name of the Player you want to search: " << endl;
            cout << "0. Return to Player Menu" << endl;
            try {
                string name;
                cin >> name;
                if(name == "0") return 0;
                cin.ignore(1000, '\n');
                national_team->findPlayer(name)->info();
            }
            catch(PlayerNotFound & er) {
                cout << "Player " << er.getName() << " not found" << endl;
            }
            return 0;
        case '3':
            return national_team->addPlayer();
        case '0':
            return 1;
        default:     //Invalid input
            cin.ignore(1000,'\n');
            return 0;
    }
}
int menu_tournaments()
{
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "            Competitions Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all competitions " << endl;
    cout << "2. Pay competitions fees" << endl;
    cout << "0. Return to Main Menu " << endl;

    cin.clear();
    cin >> menu;

    switch(menu)
    {
        case '1':    //View player info
            for(int i = 0; i < (national_team->getCompetion()).size(); i++){
                cout << (*(national_team->getCompetion()[i]));
            }
            return 0;//remove this line after inserting stuff
        case '2':
            cout << "National Football Team Competitions - VERIFICAR ERRO DEPOIS" << endl;
            for(int i = 0; i < (national_team->getCompetion()).size(); i++){
                cout << i << ". " << national_team->getCompetion()[i]->getCompetitionName() << " - Paid: " << national_team->getCompetion()[i]->getPaid() << endl;
            }
            int index;
            cin >> index; // VERIFICAR ERRO DEPOIS
            try {
                national_team->getCompetion()[index]->payPlayers();
                cout << "Competition successfully paid!" << endl;
            }
            catch(AlreadyPaid &er) {
                cout << "The " << er.getName() << " has already been paid to players." << endl;
            }
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            cin.ignore(1000,'\n');
            return 0;
    }
}

int team_information()
{
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "            Team Information             " << endl;
    cout << "========================================= \n" << endl;

    cout << "Team Name: " << national_team->getTeamName() << endl;
    cout << "Number of Competitions: " << national_team->getCompetion().size() << endl;
    cout << "Number of Players: " << national_team->getPlayers().size() << endl;
    cout << "Money spent with players in competitions: " << national_team->getMoneyPlayers() << endl;
    cout << "Money spent with staff per month: " << national_team->getMoneyStaff() << endl;
    cout << "0. Return to Main Menu " << endl;

    cin.clear();
    cin >> menu;


    return 1;

}
int mainMenu()
{
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "          National Football Team          " << endl;
    cout << "                Main Menu                 " << endl;
    cout << "========================================= \n" << endl;
    cout << "1. Player Menu" << endl;
    cout << "2. Staff Menu" << endl;
    cout << "3. Tournaments Menu" << endl;
    cout << "4. Games Menu" << endl;
    cout << "5. View app info" << endl;
    cout << "6. Team Information" << endl;
    cout << "0. Exit" << endl;

    cin.clear();
    cin >> menu;

    switch(menu)
    {
        case '1':    //View player info
            while(!menu_players());
            break;
        case '2':    //View staff info
            while(!menu_staff());
            break;
        case '3':    //View app info
            while(!menu_tournaments());
            break;
        case '5':    //View app info
            while(!info_app());
            break;
        case '6':    //View app info
            while(!team_information());
            break;
        case '0':    //Exit function
            exit(0);
        default:     //Invalid input
            cin.ignore(1000,'\n');
            return 0;
    }
}
int fileMenu(){
    ifstream teamFile;
    string filename;

    cout << "Write the filename you wish to read: " << endl;
    cout << "0. Go back to the previous menu" << endl;
    cin.clear();
    cin >> filename;
    teamFile.open(filename);

    if(filename == "0") return 1;

    while (teamFile.fail())
    {
        cin.clear();
        cout << "Incorrect filename, please enter again: " << endl;
        cin >> filename;
        teamFile.open(filename);

        if(filename == "0") return 1;
    }
    national_team = new Team(filename);
    while(!mainMenu());
    return 1;
}

int firstMenu(){
    char menu;

    cout << "========================================= " << endl;
    cout << "          National Football Team          " << endl;
    cout << "========================================= \n" << endl;
    cout << "Choose and option:" << endl;
    cout << "1. Select the Team File to read " << endl;
    cout << "2. Create a new Team File " << endl;
    cout << "0. Exit Program" << endl;

    cin.clear();
    cin >> menu;

    switch(menu){
        case '1': //Select the Team File to read
            while(!fileMenu());
            break;
        case '2': //Create a new Team File
            return 0;
            break;
        case '0': //Exits program
            return 1;
        default:  //
            cin.ignore(1000,'\n');
            return 0;
    }
}

