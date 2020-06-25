#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <clocale>

using namespace std;
string path; 
size_t cursor_index;
bool is_edit = false;

const string menu[] = { "Open", "Save", "Edit", "Close" };
uint8_t INDEX = 0;
string text = "";
bool is_work = true;

void draw() {
    system("cls");
   // cout << cursor_index << endl;
    for (size_t i = 0; i < menu->size(); ++i) {
        if (INDEX == i) cout << "*";
        cout << menu[i] << "        ";
    }
    cout << endl << "-----------------------------------------------------------------------------------------\n";
    for (int j = 0; j <= text.length(); ++j)
    {
        cout << text[j];
        if (j % 200 == 0 && j != 0) cout << endl;
        if (j == cursor_index && is_edit) cout << "_";
    }
}

void nextMenuItem(const string& text) {
    ++INDEX;
    if (INDEX == menu->size())INDEX = 0;
    draw();
}

void open() {
    string path;
    cout << "path to file:";
    cin >> path;
    ifstream input(path);
    if (input.good()) {
        string buffer;
        while (getline(input, buffer)) {
            text += buffer;
            text += " ";
        }
    }
    else {
        text = "";
    }
    input.close();
}

void save()
{
    system("cls");
    string p;
    cout << "save to: ";
    cin >> p;

    ofstream output;
    output = ofstream(p);
    output.write(text.data(), text.size());


    output.close();
}

void addchar(int x)
{
    if (x == 224)
    {
        return;
    }
    string s;
    s.push_back(static_cast<char>(x));
    text.insert(cursor_index + 1, s);
    cursor_index++;
    draw();
    //cout << s << endl;
}

void deletechar()
{
    text.erase(cursor_index);
    if (cursor_index > 0)
    {
        cursor_index--;
    }
    draw();
}

void edit()
{
    cursor_index = text.length();
    is_edit = true;
    draw();
    while (is_edit)
        if (_kbhit())
        {
            int t = _getch();
           //cout << t << endl;
            switch (t)
            {
            case 75:
                if (cursor_index > 0)
                {
                    cursor_index--;
                    draw();
                }
                break;
            case 77:
                if (cursor_index < text.length())
                {
                    cursor_index++;
                    draw();
                }
                break;
            case 38:
                cursor_index += 200;
            case 8:
                deletechar();
                break;
            case 27:
                is_edit = false;
                break;
            default:
                addchar(t);
                break;
            }
        }
}



void enterHandle() {
    switch (INDEX) {
    case 0:
        system("cls");
        open();
        draw();
        break;
    case 3:
        is_work = false;
        save();
        break;
    case 1:
        save();
        break;
    case 2:
        edit();
        break;
    }
}

int main() {
    //setlocale()
    string path;

    ofstream output;

    draw();

    while (is_work) {
        if (_kbhit()) {
            switch (_getch()) {
            case 9:
                nextMenuItem(text);
                break;
            case 13:
                enterHandle();
                break;
            }
        }
    }

    output = ofstream(path);
    output.write(text.data(), text.size());


    output.close();
    return 0;
}