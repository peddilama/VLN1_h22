#include "notendaui.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

NotendaUI::NotendaUI()
{

}



bool check = true;

void NotendaUI::keyra()
{

    vector<tolvufolk> data = _service.getTolvufolk();



    skrifaUt();

    do
        {
        check = true;
        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            skrifaUt();
            printList(data);
            continueUI();
        }
        else if (skipun == "sort"|| skipun == "so")
        {
            skrifaUt();
            sortOptions(data);
            continueUI();
        }
        else if (skipun == "add" || skipun == "a")
        {
            skrifaUt();
            addPerson(data);
            printList(data);
            continueUI();

        }
        else if (skipun == "delete" || skipun == "d")
        {
            skrifaUt();
            printList(data);
            continueUI();

        }

        else if (skipun == "update" || skipun == "u")
        {

            skrifaUt();
            updatePerson(data);
            continueUI();
        }

        else if (skipun == "search" || skipun == "s")
        {
            skrifaUt();
            searchName(data);
            continueUI();
        }

        else if (skipun == "purge" || skipun == "p")
        {
            skrifaUt();
            cout << "By the Emperor, are you sure? (Y/N): ";
            cin >> skipun;

            if (skipun == "Y" || skipun == "y")
            {
                cout << "Are you really sure? This will EXTERMINATE ALL ENTRIES. (Y/N): ";
                cin >> skipun;

                if (skipun == "Y" || skipun == "y")
                {
                    cout << "Acknowledged, by your will, all ENTRIES will be EXTERMINATED.";
                    // TODO; Erase everything
                    continueUI();

                }
                else
                {
                    cout << "Purge canceled." << endl;
                    continueUI();
                }

            }
            else
            {
                cout << "Purge canceled." << endl;
                continueUI();
            }


        }

        else if (skipun == "quit" || skipun == "q")
        {
            check = true;
        }

        else
        {
            skrifaUt();
            cerr << "Input not valid, try again: ";
            check = false;
        }
    } while (check == false);
}

void NotendaUI::skrifaUt()
{
    system("cls");

    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following commands                       ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||list - Shows a list of all known entries in the database.     ||*" << endl;
    cout << "*||add - Add a new entry into the database.                      ||*" << endl;
    cout << "*||delete - Removes an entry from the database.                  ||*" << endl;
    cout << "*||update - Updates an entry from the database.                  ||*" << endl;
    cout << "*||search - Search for an entry from the database.               ||*" << endl;
    cout << "*||purge - Removes every entry from the database.                ||*" << endl;
    cout << "*||quit - Exits/quits the program                                ||*" << endl;
    cout << "*==================================================================*" << endl;
}
void NotendaUI::updatePerson(vector<tolvufolk>& data)
{
    system("cls");
    printList(data);
    int persNR;
    string skipunin;
    cout << "Update scientist number: ";
    cin >> persNR;
    persNR --;

    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command*                       ||*" << endl;
    cout << "*=================================================================*" << endl;
    cout << "*||name - update name, please write 'name'                       ||*" << endl;
    cout << "*||gender - update gender, please write 'gender'                 ||*" << endl;
    cout << "*||birth - update year of birth, please write 'birth'            ||*" << endl;
    cout << "*||death - update year of death, please write 'deat'             ||*" << endl;
    cout << "*==================================================================*" << endl;
    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        string nafn;
        cout << "Enter updated name for " << data[persNR].getNafn() << ": ";
        cin.ignore();
        getline(cin,nafn);
        data[persNR].updNafn(nafn);
    }

    else if (skipunin == "gender" || skipunin == "g")
    {
        string newgend;
        cout << "Enter updated gender for " << data[persNR].getNafn() << ": ";
        cin >> newgend;
        while (newgend != "kk" && newgend != "kvk")
        {
            cerr << "Input not valid, try again: ";
            cin >> newgend;
        }
        data[persNR].updGender(newgend);
    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        int nytt;
        cout << "Enter updated year of birth for " << data[persNR].getNafn() << ": ";
        cin >> nytt;
        data[persNR].updFaedingarar(nytt);
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        int nytt;
        cout << "Enter updated year of death for " << data[persNR].getNafn() << ": ";
        cin >> nytt;
        data[persNR].updDanarar(nytt);
    }

    _service.deleteTolvufolk();
    for(size_t i = 0; i < data.size(); i++)
    {
         _service.addTolvufolk(data[i]);
    }

}
void NotendaUI::searchOptions()
{
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command                        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name  - Search by name, please write 'name'                   ||*" << endl;
    cout << "*||age   - Search by age, please write 'age'                     ||*" << endl;
    cout << "*||birth - Search by year of birth, please write 'birth'         ||*" << endl;
    cout << "*||death - Search by year of death, please write 'death'         ||*" << endl;
    cout << "*==================================================================*" << endl;
}

void NotendaUI::printList(const vector<tolvufolk>& data)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << "Scientist number: " << i + 1 << endl;
        cout << data[i] << endl;
    }
}

void NotendaUI::searchName(const vector<tolvufolk>& data)
{
    searchOptions();
    string skipunin;
    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        searchOptions();
        string nafn;
        cout << "Name to search: ";
        cin.ignore();
        getline(cin,nafn);
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (nafn == data[i].getNafn() )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "age" || skipunin == "a")
    {
        searchOptions();
        int age;
        cout << "Age to search: ";
        cin >> age;
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (age == (data[i].getDanarar() - data[i].getFaedingarar() ) )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        searchOptions();
        int birth;
        cout << "Year of birth to search: ";
        cin >> birth;
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (birth == data[i].getFaedingarar() )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        searchOptions();
        int death;
        cout << "Year of birth to search: ";
        cin >> death;
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (death == data[i].getDanarar() )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

}

void NotendaUI::sortOptions(vector<tolvufolk>& data)
{
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command                        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name - Sort by name, please write 'name'                      ||*" << endl;
    cout << "*||age - Sort by age, please write 'age'                         ||*" << endl;
    cout << "*||birth - Sort by year of birth, please write 'birth'           ||*" << endl;
    cout << "*||death - Sort by year of death, please write 'death'           ||*" << endl;
    cout << "*==================================================================*" << endl;

    string skipunin;
    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command                        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||ascending - Sort names by ascending order                     ||*" << endl;
    cout << "*||descending - Sort names by descending order                   ||*" << endl;
    cout << "*==================================================================*" << endl;

        string skipunin;
        cin >> skipunin;

        if(skipunin == "ascending" || skipunin == "a")
        {
            //vector<tolvufolk> result;
            //result = _service.sortByName(data);
        }
    }
}

void NotendaUI::addPerson(vector<tolvufolk>& data)
{
    string nName;
    string gGender;
    int bYear;
    int dYear;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin,nName);

    cout << "Enter gender(kk/kvk) [lowercase]: ";
    cin >> gGender;

    while (gGender != "kk" && gGender != "kvk")
    {
        cerr << "Input not valid, try again: ";
        cin >> gGender;
    }

    cout << "Enter year of birth: ";
    cin >> bYear;

    while (0 > bYear)
    {
        cerr << "Input not valid, try again: ";
        cin >> bYear;
    }

    cout << "Enter year of death(-1 if still alive): ";
    cin >> dYear;

    while (-1 > dYear)
    {
        cerr << "Input not valid, try again: ";
        cin >> dYear;
        cout << endl;
    }

    tolvufolk Tempr(nName, gGender, bYear, dYear);
    data.push_back(Tempr);
    _service.addTolvufolk(Tempr);

}

void NotendaUI::continueUI()
{
    string answer;
    cout << "Continue? (Y/N): ";
    cin >> answer;
    if (answer == "Y" || answer == "y")
    {
        skrifaUt();
        check = false;
    }
    else
    {
        check = true;
    }

}
