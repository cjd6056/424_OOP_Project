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
#include <cstring>   // for memset
#include <limits>    // for std::numeric_limits
using namespace std;

const int width = 60; // Width of the game area
const int height = 10; // Height of the game area

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
    fruitCordX = rand() % (width - 2) + 1; // Ensure fruit does not spawn on walls
    fruitCordY = rand() % (height - 2) + 1; // Ensure fruit does not spawn on walls
    playerScore = 0;
    snakeTailLen = 0; // Reset tail length
    memset(snakeTailX, 0, sizeof(snakeTailX)); // Initialize tail array
    memset(snakeTailY, 0, sizeof(snakeTailY)); // Initialize tail array
}

void GameRender(string playerName) {
    // Clear the console and set cursor position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

    // Draw the game area
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j <= width; j++) {
            if (i == 0 || i == height + 1) 
                cout << "-";
            else if (j == 0 || j == width)
                cout << "|";
            else if (i == y + 1 && j == x)
                cout << "0"; // Snake head
            else if (i == fruitCordY + 1 && j == fruitCordX)
                cout << "#"; // Fruit
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o"; // Snake tail
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

    // Move snake in the current direction
    switch (sDir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    // Update tail coordinates
    for (int i = snakeTailLen - 1; i > 0; i--) {
        snakeTailX[i] = snakeTailX[i - 1];
        snakeTailY[i] = snakeTailY[i - 1];
    }
    if (snakeTailLen > 0) {
        snakeTailX[0] = prevX;
        snakeTailY[0] = prevY+1; //needs to be y+1 for appearance of following head!
    }

    // Check for collision with walls (game area bounds)
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    // Check for collision with the snake's own tail
    for (int i = 0; i < snakeTailLen; i++) 
    {
        if (snakeTailX[i] == x && snakeTailY[i] == y+1) //needs to be y+1 for appearance of following head
        {
            isGameOver = true;
            break;
        }
    }

    // Check if snake eats the fruit
    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;
        snakeTailLen++; // Increment tail length when fruit is eaten

        // Generate a new position for the fruit within bounds, avoiding the walls and the snake's tail
        bool foodSpawned = false;
        int maxAttempts = 100;
        for (int attempt = 0; attempt < maxAttempts && !foodSpawned; attempt++) {
            fruitCordX = rand() % (width - 2) + 1; // Avoid walls
            fruitCordY = rand() % (height - 2) + 1; // Avoid walls

            // Ensure the new fruit position does not overlap with the snake tail
            foodSpawned = true;
            for (int i = 0; i < snakeTailLen; i++) {
                if (snakeTailX[i] == fruitCordX && snakeTailY[i] == fruitCordY) {
                    foodSpawned = false;
                    break;
                }
            }
        }
    }
}

int SetDifficulty()
{
    int choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: ";
    
    // Read input as integer
    cin >> choice;

    // Check if the input was successful
    if (cin.fail()) {
        // If input failed, clear the error flag and ignore the rest of the input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = 0; // Default case
    }

    switch (choice) 
    {
    case 1: speed_delay = 100; break; // Easy
    case 2: speed_delay = 50; break; // Medium
    case 3: speed_delay = 10; break; // Hard (very fast)
    default: speed_delay = 50; break; // Default to Medium
    }

    cout << "Speed Delay: " << speed_delay << " ms" << endl; // Debug output
    return speed_delay;
}




void UserInput() {
    while (_kbhit()) {
        switch (_getch()) {
        case 72: if (sDir != DOWN) sDir = UP; break;   // Up arrow
        case 80: if (sDir != UP) sDir = DOWN; break;   // Down arrow
        case 75: if (sDir != RIGHT) sDir = LEFT; break; // Left arrow
        case 77: if (sDir != LEFT) sDir = RIGHT; break; // Right arrow
        case 'x': isGameOver = true; break; // Exit game
        case 'p': isPaused = !isPaused; break; // Pause game
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
    srand(static_cast<unsigned int>(time(0)));
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
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 }); // Remove flickering effect
        CONSOLE_CURSOR_INFO info; // Hides cursor
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

        GameInit();
        while (!isGameOver) {
            UserInput();
            if (!isPaused) {
                UpdateGame();
                GameRender(playerName);
                Sleep(speed_delay); // Control the speed of the game
            } else {
                COORD pauseCoord = { 0, (short)(height + 1) };
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pauseCoord);
                cout << "Game Paused. Press 'p' to resume.      ";
            }
        }
        highScore = max(highScore, playerScore);
        cout << "\nGame Over! Your final score is: " << playerScore;
        cout << "\nHigh Score: " << highScore << endl;

    } while (PlayAgain());

    return 0;
}
