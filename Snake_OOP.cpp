
/*
AERSP 424 Final Project
Authors: Conor Dowdell, Gabrielle Dowdell, Shanon Hyde
Sources: https://www.geeksforgeeks.org/snake-code-cpp/
Video: https://www.youtube.com/watch?v=E_-lMZDi7Uw

OOP style: 3 main classes
{ 
1. Snake
2. Fruit
3. Game
}
*/ 

#include <conio.h>
#include <iostream>
#define NOMINMAX // to help with min and max errors via windows.h
#include <windows.h> //Windows API
#include <algorithm>
#include <cstring>
#include <limits>
#include <string>
using namespace std;

const int width = 60;
const int height = 10;

enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Snake 
{
public:
    int x, y;
    int tailX[100], tailY[100];
    int tailLen;
    snakesDirection direction;

    Snake() 
    {
        reset();
    }

    void reset() 
    {
        x = width / 2;
        y = height / 2;
        tailLen = 0;
        direction = RIGHT;
        memset(tailX, 0, sizeof(tailX));
        memset(tailY, 0, sizeof(tailY));
    }

    void updatePosition() 
    {
        for (int i = tailLen - 1; i > 0; i--) 
        {
            tailX[i] = tailX[i - 1];
            tailY[i] = tailY[i - 1];
        }
        if (tailLen > 0) 
        {
            tailX[0] = x;
            tailY[0] = y+1; // Adjust for visual effect
        }
        switch (direction) 
        {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
        }
    }

    bool checkCollision() const 
    {
        for (int i = 0; i < tailLen; i++) 
        {
            if (tailX[i] == x && tailY[i] == y+1) // Adjust for visual effect
            {
                return true;
            }
        }
        return false;
    }

    void grow() 
    {
        tailLen++;
    }
};

class Fruit 
{
public:
    int x, y;

    Fruit() 
    {
        spawn();
    }

    void spawn() 
    {
        x = rand() % (width - 2) + 1;
        y = rand() % (height - 2) + 1;
    }
};

class Game 
{
private:
    Snake snake;
    Fruit fruit;
    int score, highScore, lives;
    bool isGameOver, isPaused, funMode;
    int speedDelay;
    string playerName;

public:
    Game() : highScore(0), lives(3), isGameOver(false), isPaused(false), funMode(false), speedDelay(50) {}

    void init() 
    {
        isGameOver = false;
        isPaused = false;
        snake.reset();
        fruit.spawn();
        score = 0;
    }

    void render() 
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
        cout << playerName << "'s Score: " << score << " | Lives: " << lives << " | High Score: " << highScore << "    ";
    }

    void setDifficulty() 
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

    void handleInput() 
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

    void update() 
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

    void play() 
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
                cout << "\nGoodbye Cruel World! Press any key to continue...";
                _getch();
                score = 0;
                funMode = false;
                lives = 3;
            }

            cout << "\nGame Over! Your final score is: " << score;
            cout << "\nHigh Score: " << highScore << endl;
        } 
        while (playAgain());
    }

    bool playAgain() 
    {
        char choice;
        cout << "\nPlay Again? (Y/N): ";
        cin >> choice;
        return choice == 'Y' || choice == 'y';
    }
};

int main() 
{
    srand(static_cast<unsigned int>(time(0)));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    Game game;
    game.play();
    return 0;
}
