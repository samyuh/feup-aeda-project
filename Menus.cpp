#include <iostream>
#include <string>
#include "Menus.h"
#include "Team.h"

using namespace std;

int test(){

    Team b("init.txt");
    for (int i = 0; i< b.getPlayers().size(); i++){
        b.getPlayers()[i]->info();
        cout << endl;
    }

    vector<Game *> a = b.getCompetion()[0]->getGames();

    cout << a[0]->getCity() <<" " << a[0]->getCountry() << " " << a[0]->getStadium() << endl;
    cout << a[1]->getCity() <<" " << a[1]->getCountry() << " " << a[1]->getStadium() << endl;
    return 1;
}

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

    cout <<  "Staff Menu " << endl << endl;

    cout << "1. insert stuff " << endl;
    cout << "0. Return to Main Menu " << endl;

    cin.clear();
    cin >> menu;

    switch(menu)
    {
        case '1':    //View player info
            // do stuff
            return 0;//remove this line after inserting stuff
            break;
        case '0':    //Exit function
            return 1;
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

    cout <<  "Player Menu " << endl << endl;

    cout << "1. View All Players " << endl;
    cout << "0. Return to Main Menu " << endl;

    cin.clear();
    cin >> menu;

    switch(menu)
    {
        case '1':    //View player info
            while(!test());

            return 0;//remove this line after inserting stuff
            break;
        case '0':    //Exit function
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

    cout <<  "Tournament Menu " << endl << endl;

    cout << "1. Create a new f " << endl;
    cout << "0. Return to Main Menu " << endl;

    cin.clear();
    cin >> menu;

    switch(menu)
    {
        case '1':    //View player info
            // do stuff
            return 0;//remove this line after inserting stuff
            break;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            cin.ignore(1000,'\n');
            return 0;
    }
}
int mainMenu()
{
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "          National Football Team          " << endl;
    cout << "========================================= \n" << endl;
    cout << "1. View player info" << endl;
    cout << "2. View staff info" << endl;
    cout << "3. View app info" << endl;
    cout << "4. Tournaments" << endl;
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
            while(!info_app());
            break;
        case '4':    //View app info
            //while(!menu_tournaments());
            break;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            cin.ignore(1000,'\n');
            return 0;
    }
}


