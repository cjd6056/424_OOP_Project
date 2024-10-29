/*
AERSP 424 Final Project
Authors: Conor and Gabrielle Dowdell
Sources: https://www.geeksforgeeks.org/snake-code-cpp/
Video: https://www.youtube.com/watch?v=E_-lMZDi7Uw
*/ 

#include <conio.h>
#include <iostream>
#include <windows.h>
#include <algorithm> // for max function
using namespace std;

const int width = 80; // Width of the game area
const int height = 20; // Height of the game area

int x, y; // Snake head coordinates
int fruitCordX, fruitCordY; // Food coordinates
int playerScore; // Player score
int highScore = 0; // High score
int snakeTailX[100], snakeTailY[100]; // Snake tail coordinates
int snakeTailLen; // Length of the snake's tail
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDir; // Snake's direction
bool isGameOver; // Game over state
bool isPaused; // Game pause state
int speed_delay; // Speed delay factor

void GameInit() {
    isGameOver = false;
    isPaused = false;
    sDir = RIGHT;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
    snakeTailLen = 0;
}

void GameRender(string playerName) {
    //system("cls");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});

    // Draw the game area
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j <= width; j++) {
            if (i == 0 || i == height + 1) 
                cout << "-";
            else if (j == 0 || j == width)
                cout << "|";
            else if (i == y + 1 && j == x)
                cout << "0";
            else if (i == fruitCordY + 1 && j == fruitCordX)
                cout << "#";
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }
    cout << playerName << "'s Score: " << playerScore << "    ";
}

void UpdateGame() {
    int prevX = x, prevY = y;

    switch (sDir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    for (int i = snakeTailLen - 1; i > 0; i--) {
        snakeTailX[i] = snakeTailX[i - 1];
        snakeTailY[i] = snakeTailY[i - 1];
    }
    if (snakeTailLen > 0) {
        snakeTailX[0] = prevX;
        snakeTailY[0] = prevY + 1;
    }

    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y + 1) {
            isGameOver = true;
            break;
        }
    }

    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;

        bool foodSpawned = false;
        int maxAttempts = 100;
        for (int attempt = 0; attempt < maxAttempts && !foodSpawned; attempt++) {
            fruitCordX = rand() % (width - 1) + 1;
            fruitCordY = rand() % (height - 1) + 1;

            foodSpawned = true;
            for (int i = 0; i < snakeTailLen; i++) {
                if (snakeTailX[i] == fruitCordX && snakeTailY[i] == fruitCordY) {
                    foodSpawned = false;
                    break;
                }
            }
            if (x == fruitCordX && y == fruitCordY)
                foodSpawned = false;
        }
        if (!foodSpawned) {
            fruitCordX = rand() % (width - 1) + 1;
            fruitCordY = rand() % (height - 1) + 1;
        }

        snakeTailX[snakeTailLen] = prevX;
        snakeTailY[snakeTailLen] = prevY + 1;
        snakeTailLen++;

    }
}

int SetDifficulty() {
    int choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case '1': speed_delay = 150; break;
    case '2': speed_delay = 100; break;
    case '3': speed_delay = 50; break;
    default: speed_delay = 100;
    }
    return speed_delay;
}

void UserInput() {
    while (_kbhit()) {
        switch (_getch()) {
        case 72: if (sDir != DOWN) sDir = UP; break;
        case 80: if (sDir != UP) sDir = DOWN; break;
        case 75: if (sDir != RIGHT) sDir = LEFT; break;
        case 77: if (sDir != LEFT) sDir = RIGHT; break;
        case 'x': isGameOver = true; break;
        case 'p': isPaused = !isPaused; break;
        }
    }
}

bool PlayAgain() {
    char choice;
    cout << "\nPlay Again? (Y/N): ";
    cin >> choice;
    return choice == 'Y' || choice == 'y';
}

int main() {
    srand(time(0));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, width + 1, height + 2 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    COORD bufferSize = { width + 2, height + 3 };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    do {
        SetDifficulty();
        system("pause");
        system("cls");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0}); //Code I found in a comment section... Removes Flickering effect
        CONSOLE_CURSOR_INFO info; // This gets rid of the random cursors all over the screen. Super helpful!!!
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);


        GameInit();
        while (!isGameOver) {
            UserInput();
            if (!isPaused) {
                UpdateGame();
                GameRender(playerName);
            } else {
                COORD pauseCoord = { 0, (short)(height + 1) };
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pauseCoord);
                cout << "Game Paused. Press 'p' to resume.      ";
            }
        }
        highScore = max(highScore, playerScore);
        cout << "\nGame Over! Your final score is: " << playerScore;
        cout << "\nHigh Score: " << highScore << endl;

    } 
    while (PlayAgain());

    return 0;
}
