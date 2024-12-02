#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <limits>
#include <cstdlib>
#include <ctime>

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
    fruit.spawn();
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
            else if (i == fruit.y + 1 && j == fruit.x) cout << "#";
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

    if (snake.x == fruit.x && snake.y == fruit.y) 
    {
        score += 10;
        snake.grow();
        fruit.spawn();
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
                if (score > highScore) highScore = score;
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
            score = 0;
            funMode = false;
            lives = 3;
        }

        cout << "\nGame Over! Your final score is: " << score;
        cout << "\nHigh Score: " << highScore << endl;

        // Increment games played after each game finishes
        (*gamesPlayed)++;

    } 
    while (playAgain());
}

bool Game::playAgain() 
{
    char choice;
    cout << "\nPlay Again? (Y/N): ";
    cin >> choice;
    return choice == 'Y' || choice == 'y';
}
