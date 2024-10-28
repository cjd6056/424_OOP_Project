// AERSP 424 Final Project
// Source: https://www.geeksforgeeks.org/snake-code-cpp/


#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

const int width = 80; // Width of the game area
const int height = 20; // Height of the game area

int x, y; // Snake head coordinates
int fruitCordX, fruitCordY; // Food coordinates
int playerScore; // Player score
int snakeTailX[100], snakeTailY[100]; // Snake tail coordinates
int snakeTailLen; // Length of the snake's tail
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDir; // Snake's direction
bool isGameOver; // Game over state
bool isPaused; // Game pause state

void GameInit() {
    isGameOver = false;
    isPaused = false; // Initialize paused state
    sDir = RIGHT; // Start moving to the right
    x = width / 2; // Initial position of the snake head
    y = height / 2; // Initial position of the snake head
    fruitCordX = rand() % width; // Random position for food
    fruitCordY = rand() % height; // Random position for food
    playerScore = 0; // Initialize score
    snakeTailLen = 0; // Initialize snake tail length
}

void GameRender(string playerName) {
    // Clear the console
    system("cls");

    // Draw the game area
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j <= width; j++) {
            if (i == 0 || i == height + 1) // Top and bottom walls
                cout << "-";
            else if (j == 0 || j == width) // Side walls
                cout << "|";
            else if (i == y + 1 && j == x) // Snake head
                cout << "0"; // Change head to '0'
            else if (i == fruitCordY + 1 && j == fruitCordX) // Food
                cout << "#";
            else {
                // Check for snake tail
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o"; // Snake tail
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " "; // Empty space
            }
        }
        cout << endl;
    }

    // Display player's score
    cout << playerName << "'s Score: " << playerScore << "    "; // Added spaces to clear any previous text
}




// Function for updating the game state
void UpdateGame()
{
    // Save current head position
    int prevX = x;
    int prevY = y;

    // Move the head according to the direction
    switch (sDir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // Update each tail segment to follow the one before it
    for (int i = snakeTailLen - 1; i > 0; i--) {
        snakeTailX[i] = snakeTailX[i - 1];
        snakeTailY[i] = snakeTailY[i - 1];
    }

    // The first segment of the tail takes the previous position of the head but shifted down
    if (snakeTailLen > 0) {
        snakeTailX[0] = prevX; // The position of the first tail segment
        snakeTailY[0] = prevY; // This LINE CAUSES PROBLEMS LOL
    }

    // Check for collision with walls
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    // Check for collision with tail
    if (snakeTailLen > 0) { // Only check for collision if there's at least one tail segment
        for (int i = 0; i < snakeTailLen; i++) {
            if (snakeTailX[i] == x && snakeTailY[i] == y) {
                isGameOver = true; // End the game on tail collision
                break; // Exit loop on collision
            }
        }
    }

    // Check if the snake has eaten the food
    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;

        // Generate new food coordinates
        bool foodSpawned = false;
        while (!foodSpawned) {
            fruitCordX = rand() % width;
            fruitCordY = rand() % height;

            // Check if the new food position overlaps with the snake
            foodSpawned = true;
            for (int i = 0; i < snakeTailLen; i++) {
                if (snakeTailX[i] == fruitCordX && snakeTailY[i] == fruitCordY) {
                    foodSpawned = false; // Food overlaps with the snake, try again
                    break;
                }
            }

            // Also check if the food spawns on the head
            if (x == fruitCordX && y == fruitCordY) {
                foodSpawned = false; // Food overlaps with the head, try again
            }
        }

        // Add a new segment to the end of the tail
        snakeTailX[snakeTailLen] = prevX; // Position of the new segment at the previous head
        snakeTailY[snakeTailLen] = prevY + 1; // Keep the tail one line lower than the head
        snakeTailLen++; // Increase the tail length
    }
}


int SetDifficulty() {
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case '1':
        dfc = 50; // Easy
        break;
    case '2':
        dfc = 100; // Medium
        break;
    case '3':
        dfc = 150; // Hard
        break;
    default:
        dfc = 100; // Default to medium
    }
    return dfc;
}

void UserInput() {
    while (_kbhit()) {
        switch (_getch()) {
        case 72: // Up arrow key
            if (sDir != DOWN) sDir = UP; // Prevents reversing
            break;
        case 80: // Down arrow key
            if (sDir != UP) sDir = DOWN; // Prevents reversing
            break;
        case 75: // Left arrow key
            if (sDir != RIGHT) sDir = LEFT; // Prevents reversing
            break;
        case 77: // Right arrow key
            if (sDir != LEFT) sDir = RIGHT; // Prevents reversing
            break;
        case 'x':
            isGameOver = true; // End the game
            break;
        case 'p': // Toggle pause on 'p' key
            isPaused = !isPaused; // Toggle the pause state
            break;
        }
    }
}

int main() {
    srand(time(0)); // Initialize random seed
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, width + 1, height + 2 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    COORD bufferSize = { width + 2, height + 3 };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int dfc = SetDifficulty(); // Set difficulty
    system("pause");
    system("cls");

    GameInit(); // Initialize the game variables

    // Start the game loop
    while (!isGameOver) {
        UserInput(); // Check for user input first
        if (!isPaused) { // Only update and render if not paused
            UpdateGame();
            GameRender(playerName); // Render after updating
        } else {
            // Display a paused message
            COORD pauseCoord = { 0, (short)(height + 1) };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pauseCoord);
            cout << "Game Paused. Press 'p' to resume.      "; // Added spaces to clear any previous text
        }

        Sleep(dfc/2); // Control the game speed based on difficulty
    }

    cout << "\nGame Over! Your Score: " << playerScore << endl;
    system("pause"); // Waits for the user to press a key
    return 0;
}
