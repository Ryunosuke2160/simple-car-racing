#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class ConsoleManager {
private:
    HANDLE consoleHandle;
    CONSOLE_CURSOR_INFO cursorInfo;

public:
    ConsoleManager() {
        this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    void setCursorPosition(short x, short y) {
        COORD position = {x, y};
        SetConsoleCursorPosition(consoleHandle, position);
    }

    void hideCursor() {
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    void showCursor() {
        cursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }
};

class Car {
public:
    string name;
    int distance;
};

class RacingGame {
private:
    vector<Car> cars;
    ConsoleManager cm;
    int totalPlayers;
    int maxPlayers;
    int maxDistance;

public:
    RacingGame() {
        srand(time(0));
        this->maxPlayers = 3;
        this->maxDistance = 80; // Track length. My default: 80
    }

    int random() {
        return rand();
    }

    int rangedRandom(int min, int max) {
        return (min + std::rand() % (max - min + 1));
    }

    string formBorder() {
        string border = "";
        for(int i = 0; i < this->maxDistance + 13; i++) {
            border += "=";
        }
        return border;
    }

    void startGame() {
        // Request user input
        bool step1 = true;
        while (step1) {
            cout << "\nRandom Racing Game\n" << endl;
            cout << "Enter the amount of players (max 3 for now)" << endl;
            cout << "->: ";
            string totalPlayers;
            getline(cin, totalPlayers);

            bool isDigit = true;
            for(char c : totalPlayers) {
                if (!isdigit(c)) {
                    isDigit = false;
                    break;
                }
            }

            cm.hideCursor();
            if (!isDigit || (isDigit && (stoi(totalPlayers) < 2 || stoi(totalPlayers) > 3))) {
                system("cls");
                cm.setCursorPosition(0, 6);
                cout << "\nInvalid input. Must be a number from 2--3.\n\n" << endl;
                cm.setCursorPosition(0, 0);
            }
            else {
                this->totalPlayers = stoi(totalPlayers);

                system("cls");
                cout << "\nRandom Racing Game\n" << endl;
                cout << "Enter the amount of players (max 3 for now)" << endl;
                cout << "->: " << this->totalPlayers << endl;
                cout << endl;

                step1 = false;
            }
            cm.showCursor();
        }

        cout << endl;
        for (int i = 0; i < this->totalPlayers; i++) {
            string carName;
            cout << "Enter car " << i + 1 << "'s name: ";
            getline(cin, carName);
            Car newCar;
            newCar.name = carName;
            newCar.distance = 0;
            this->cars.push_back(newCar);
        }

        // Display cars
        cm.hideCursor();
        bool step2 = true;
        while (step2) {
            system("cls");
            cout << "\n\n" << formBorder() << endl;
            for (int i = 0; i < this->totalPlayers; i++) {
                cout << this->cars[i].name << endl;
                cout << "  ______" << endl;
                cout << " /|_||_\\`.__" << endl;
                cout << "(   _    _ _\\" << endl;
                cout << "=`-(_)--(_)-'" << endl;
                cout << formBorder() << endl;
            }
            cout << endl;

            this_thread::sleep_for(chrono::milliseconds(500));
            cout << "3";
            for (int i = 0; i < 2; i++) {
                this_thread::sleep_for(chrono::milliseconds(333));
                cout << ".";
            }

            this_thread::sleep_for(chrono::milliseconds(334));
            cout << " 2";
            for (int i = 0; i < 2; i++) {
                this_thread::sleep_for(chrono::milliseconds(333));
                cout << ".";
            }

            this_thread::sleep_for(chrono::milliseconds(334));
            cout << " 1";
            for (int i = 0; i < 2; i++) {
                this_thread::sleep_for(chrono::milliseconds(333));
                cout << ".";
            }

            this_thread::sleep_for(chrono::milliseconds(334));
            cout << " Go!" << endl;

            step2 = false;
        }

        // Move the cars
        int carNumWinner;
        bool step3 = true;
        while (step3) {
            this_thread::sleep_for(chrono::milliseconds(250));
            cm.setCursorPosition(0, 0);
            cout << "\n\n" << formBorder() << endl;
            for (int i = 0; i < this->totalPlayers; i++) {
                int movement = rangedRandom(1, 3);
                this->cars[i].distance += movement;

                string distanceDisplay(this->cars[i].distance, ' ');

                cout << this->cars[i].name << endl;
                cout << distanceDisplay << "  ______" << endl;
                cout << distanceDisplay << " /|_||_\\`.__" << endl;
                cout << distanceDisplay << "(   _    _ _\\" << endl;
                cout << distanceDisplay << "=`-(_)--(_)-'" << endl;
                cout << formBorder() << endl;

                // Check if a car has reached the maximum distance
                if (this->cars[i].distance >= this->maxDistance) {
                    carNumWinner = i;
                    step3 = false;
                }
            }
        }
        cout << endl;
        cout << "===== ";
        cout << this->cars[carNumWinner].name << " has won the race! =====" << endl;
    }
};

int main()
{
    RacingGame* rg = new RacingGame();
    rg->startGame();

    cout << "\nPress any key to continue..." << endl;
    getchar();
    return 0;
}
