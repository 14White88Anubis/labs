#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;
int INDEX=0;
void stroki();

void newwindow()
{
    system("cls");
    switch (INDEX)
    {
    case 0:
            cout << "it's first string" << "\n";
            break;
    case 1:
        cout << "it's second string" << "\n";
        break;
    case 2:
        cout << "it's third string" << "\n";
        break;
    case 3:
        cout << "Do you really want to exit? yes / no" << "\n";
        string answer;
        cin >> answer;
        if (answer == "yes")
        {
            exit (0);
        }
        else
        {
            system("cls");
            stroki();
        }
    }
}

void stroki()
{
    if (INDEX == 0)
    {
        cout << "*";
    }
    cout << "stroka1" << endl;
    if (INDEX == 1)
    {
        cout << "*";
    }
    cout << "stroka2" << endl;
    if (INDEX == 2)
    {
        cout << "*";
    }
    cout << "stroka3" << "\n";
    if (INDEX == 3)
    {
        cout << "*";
    }
    cout << "Exit" << "\n";
}

void step(int x)
{
    INDEX += x;
    if (INDEX > 3)
    {
        INDEX = 0;
    }
    else if (INDEX < 0)
    {
        INDEX = 3;
    }
    system("cls");
    stroki();
}

int main()
{
    stroki();
    while (true) 
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 27:
                system("cls");
                stroki();
                break;
            case 13:
                newwindow();
                break;
            case 72:
                step(-1);
                break;
            case 80:
                step(1);
                break;
            }
        }
    }
    return 0;
}
