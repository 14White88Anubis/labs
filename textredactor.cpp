#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <clocale>
#include <tchar.h>
#include <wincon.h>
#include <string.h>

using namespace std;

HANDLE s_in = GetStdHandle(STD_INPUT_HANDLE);
DWORD dr;
INPUT_RECORD rec;

bool is_upper_case = false;

string path;
size_t cursor_index;
bool is_edit = false;

const string menu[] = { "Open", "Save", "Edit", "Close" };
uint8_t INDEX = 0;
string text = "";
bool is_work = true;

void draw() {
    system("cls");

    //cout << text << text.length() << endl;
    for (size_t i = 0; i < menu->size(); ++i) {
        if (INDEX == i) cout << "*";
        cout << menu[i] << "        ";
    }
    cout << endl << "--------------------------------------------------------------------------\n";
    for (int j = 0; j <= text.length(); ++j) {
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

void save() {
    system("cls");
    string p;
    cout << "save to: ";
    cin >> p;

    ofstream output;
    output = ofstream(p);
    output.write(text.data(), text.size());


    output.close();
}

void addchar(char x) {
    if (!is_upper_case && x >= 65 && x <= 90) { x += 32; }

    if (cursor_index == text.length()) text.push_back(x);
    else text.insert(cursor_index + 1, string(&x));
    cursor_index++;
    draw();
    is_upper_case = false;
}

void deletechar() {
    text.erase(cursor_index);
    if (cursor_index > 0) {
        cursor_index--;
    }
    draw();
}

void edit() {
    cursor_index = text.length();
    is_edit = true;
    draw();


    while (is_edit) {
        ReadConsoleInput(s_in, &rec, sizeof(INPUT_RECORD), &dr);
        FlushConsoleInputBuffer(s_in);
        if (rec.EventType == KEY_EVENT) {
            if (rec.Event.KeyEvent.bKeyDown) {
                int t = rec.Event.KeyEvent.wVirtualKeyCode;
                switch (t) {
                case VK_LEFT:
                    if (cursor_index > 0) {
                        cursor_index--;
                        draw();
                    }
                    break;
                case VK_RIGHT:
                    if (cursor_index < text.length()) {
                        cursor_index++;
                        draw();
                    }
                    break;
                case VK_BACK:
                    deletechar();
                    break;
                case VK_TAB:
                    is_edit = false;
                    draw();
                    break;
                case VK_SHIFT:
                    is_upper_case = true;
                    break;
                default:
                    addchar((char)t);
                    break;
                }
            }
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

    ofstream output;

    draw();


    while (is_work) {
        ReadConsoleInput(s_in, &rec, sizeof(INPUT_RECORD), &dr);
        FlushConsoleInputBuffer(s_in);
        if (rec.EventType == KEY_EVENT) {
            if (rec.Event.KeyEvent.bKeyDown) {
                switch (rec.Event.KeyEvent.wVirtualKeyCode) {
                case VK_TAB:
                    nextMenuItem(text);
                    break;
                case VK_RETURN:
                    enterHandle();
                    break;
                }
            }
        }
    }

    output = ofstream(path);
    output.write(text.data(), text.size());


    output.close();
    return 0;
}