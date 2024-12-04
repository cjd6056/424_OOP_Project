#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

Game::Game(int* gamesPlayed) : highScore(0), lives(3), isGameOver(false), isPaused(false), funMode(false), speedDelay(50), gamesPlayed(gamesPlayed) 
{
    // Initialize gamesPlayed to 0 if not already
    if (*gamesPlayed == 0) 
    {
        *gamesPlayed = 0;
    }
}

void Game::init() 
{
    isGameOver = false;
    isPaused = false;
    snake.reset();
    Fuel.spawn();
    score = 0;
}

void Game::render() 
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    for (int i = 0; i < height + 2; i++) 
    {
        for (int j = 0; j <= width; j++) 
        {
            if (i == 0 || i == height + 1) cout << "-";
            else if (j == 0 || j == width) cout << "|";
            else if (i == snake.y + 1 && j == snake.x) cout << "0";
            else if (i == Fuel.y + 1 && j == Fuel.x) cout << "#";
            else 
            {
                bool prTail = false;
                for (int k = 0; k < snake.tailLen; k++) 
                {
                    if (snake.tailX[k] == j && snake.tailY[k] == i) 
                    {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail) cout << " ";
            }
        }
        cout << endl;
    }
    cout << playerName << "'s Score: " << score << " | Lives: " << lives << " | High Score: " << highScore << " | Games Played: " << *gamesPlayed << "    ";
    cout << "\nPress 'X' to exit or press 'P' to pause";

}

void Game::setDifficulty() 
{
    int choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\n4: Fun Mode\nChoose difficulty level: ";
    cin >> choice;

    if (cin.fail()) 
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = 0;
    }

    switch (choice) 
    {
        case 1: speedDelay = 100; break;
        case 2: speedDelay = 50; break;
        case 3: speedDelay = 10; break;
        case 4: funMode = true; speedDelay = 50; break;
        default: speedDelay = 50; break;
    }
    cout << "Speed Delay: " << speedDelay << " ms" << endl;
}

void Game::handleInput() 
{
    while (_kbhit()) 
    {
        switch (_getch()) 
        {
            case 72: if (snake.direction != DOWN) snake.direction = UP; break;
            case 80: if (snake.direction != UP) snake.direction = DOWN; break;
            case 75: if (snake.direction != RIGHT) snake.direction = LEFT; break;
            case 77: if (snake.direction != LEFT) snake.direction = RIGHT; break;
            case 'x': isGameOver = true; break;
            case 'p': isPaused = !isPaused; break;
        }
    }
}

void Game::update() 
{
    snake.updatePosition();

    if (funMode) 
    {
        if (snake.x >= width) snake.x = 0;
        else if (snake.x < 0) snake.x = width - 1;
        if (snake.y >= height) snake.y = 0;
        else if (snake.y < 0) snake.y = height - 1;
        lives = 1;
    } 
    else if (snake.x >= width || snake.x < 0 || snake.y >= height || snake.y < 0) 
    {
        lives--;
        if (lives <= 0) isGameOver = true;
        else init();
        return;
    }

    if (snake.checkCollision()) 
    {
        lives--;
        if (lives <= 0) isGameOver = true;
        else init();
        return;
    }

    if (snake.x == Fuel.x && snake.y == Fuel.y) 
    {
        score += 10;
        snake.grow();
        Fuel.spawn();
    }
}

void Game::play() 
{
    cout << "Welcome to Snake. Good luck!\nEnter your name: ";
    cin >> playerName;

    do 
    {
        lives = 3;
        init();
        setDifficulty();
        system("pause");
        system("cls");

        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

        while (!isGameOver) 
        {
            handleInput();
            if (!isPaused) 
            {
                update();
                render();
                Sleep(speedDelay);
                if (score > highScore) 
                {
                    highScore = score;
                    saveHighScore(); // Save immediately when a new high score is achieved
                }
            } 
            else 
            {
                COORD pauseCoord = { 0, (short)(height + 1) };
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pauseCoord);
                cout << "Game Paused. Press 'p' to resume.      ";
            }
        }

        if (lives <= 0) 
        {
            cout << "\n\nGoodbye Cruel World! Press any key to continue...\n";
            _getch();
            if (score > highScore) 
            {
                highScore = score; 
                saveHighScore(); // Update high score before resetting score
            }
            cout << "\nGame Over! Your last score was: " << score;
            score = 0;
            funMode = false;
            lives = 3;
        }

        cout << "\nHigh Score: " << highScore << endl;

        // Increment games played after each game finishes
        (*gamesPlayed)++;

    } 
    while (playAgain());
}


void Game::saveHighScore() 
{
    // Check if a high score file already exists and read the previous high score
    int previousHighScore = 0;
    std::ifstream inFile("High_Score_Legends.txt", std::ios::in);
    if (inFile) 
    {
        std::string line;
        while (std::getline(inFile, line)) 
        {
            if (line.find("High Score:") != std::string::npos) 
            {
                // Extract the high score from the line
                previousHighScore = std::stoi(line.substr(line.find(":") + 1));
                break;
            }
        }
        inFile.close();
    }

    // Compare the current high score with the previous high score
    if (highScore > previousHighScore) 
    {
        std::ofstream outFile("High_Score_Legends.txt", std::ios::out);
        if (outFile) 
        {
            outFile << "🏆 Only Legends Are Listed Here 🏆\n";
            outFile << "High Score: " << highScore <<  "\tUser: " << playerName << "\n";
            outFile.close();
        }
    }
}



bool Game::playAgain() 
{
    char choice;
    cout << "\nPlay Again? (Y/N): ";
    cin >> choice;
    return choice == 'Y' || choice == 'y';
}
