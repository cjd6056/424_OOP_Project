// OOP version of snake game.


#include <conio.h>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstring>
#include <limits>
#include <ctime>
using namespace std;

const int width = 60; 
const int height = 10;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Renderer {
public:
    Renderer() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width), static_cast<SHORT>(height) };
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
        COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
        SetConsoleScreenBufferSize(hConsole, bufferSize);

        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }

    void clearConsole() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    }

    void renderGame(const string& playerName, int score, int lives, int highScore, int x, int y, int fruitX, int fruitY, const int* tailX, const int* tailY, int tailLen) {
        clearConsole();

        for (int i = 0; i < height + 2; i++) {
            for (int j = 0; j <= width; j++) {
                if (i == 0 || i == height + 1) cout << "-";
                else if (j == 0 || j == width) cout << "|";
                else if (i == y + 1 && j == x) cout << "0";
                else if (i == fruitY + 1 && j == fruitX) cout << "#";
                else {
                    bool prTail = false;
                    for (int k = 0; k < tailLen; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
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

    void displayPause() {
        COORD pauseCoord = { 0, (short)(height + 1) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pauseCoord);
        cout << "Game Paused. Press 'p' to resume.      ";
    }
};

class Snake {
public:
    Snake() : x(width / 2), y(height / 2), score(0), tailLen(0), dir(RIGHT), funMode(false) {
        memset(tailX, 0, sizeof(tailX));
        memset(tailY, 0, sizeof(tailY));
    }

    void reset() {
        x = width / 2;
        y = height / 2;
        score = 0;
        tailLen = 0;
        dir = RIGHT;
        spawnFruit();
    }

    void move() {
        int prevX = x, prevY = y;

        switch (dir) {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
        }

        if (funMode) wrapAround();
        updateTail(prevX, prevY);
    }

    void wrapAround() {
        if (x >= width) x = 0;
        else if (x < 0) x = width - 1;
        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;
    }

    bool checkCollision() const {
        for (int i = 0; i < tailLen; i++) {
            if (tailX[i] == x && tailY[i] == y + 1) return true;
        }
        return false;
    }

    bool eatFruit() {
        if (x == fruitX && y == fruitY) {
            score += 10;
            tailLen++;
            spawnFruit();
            return true;
        }
        return false;
    }

    void setDirection(Direction newDir) {
        dir = newDir;
    }

    Direction getDirection() const {
        return dir;
    }

    void spawnFruit() {
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }
    int* getTailX() { return tailX; }
    int* getTailY() { return tailY; }
    int getTailLen() const { return tailLen; }

private:
    int x, y, score, tailLen, fruitX, fruitY;
    int tailX[100], tailY[100];
    Direction dir;
    bool funMode;

    void updateTail(int prevX, int prevY) {
        for (int i = tailLen - 1; i > 0; i--) {
            tailX[i] = tailX[i - 1];
            tailY[i] = tailY[i - 1];
        }
        if (tailLen > 0) {
            tailX[0] = prevX;
            tailY[0] = prevY + 1;
        }
    }
};

class Game {
public:
    Game() : lives(3), isGameOver(false), isPaused(false), speedDelay(50), highScore(0), renderer(), snake() {}

    void init() {
        cout << "Welcome to Snake. Good luck!\nEnter your name: ";
        cin >> playerName;
        srand(static_cast<unsigned int>(time(0)));
    }

    void start() {
        do {
            reset();
            setDifficulty();
            play();
        } while (playAgain());
    }

private:
    int lives, speedDelay, highScore;
    bool isGameOver, isPaused;
    string playerName;
    Renderer renderer;
    Snake snake;

    void reset() {
        lives = 3;
        snake.reset();
        isGameOver = false;
        isPaused = false;
    }

    void setDifficulty() {
        cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\n4: Fun Mode\nChoose difficulty level: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: speedDelay = 100; break;
            case 2: speedDelay = 50; break;
            case 3: speedDelay = 10; break;
            case 4: speedDelay = 50; snake.wrapAround(); break;
            default: speedDelay = 50; break;
        }
        cout << "Speed Delay: " << speedDelay << " ms" << endl;
    }

    void play() {
        while (!isGameOver) {
            handleInput();
            if (!isPaused) {
                update();
                renderer.renderGame(playerName, snake.getScore(), lives, highScore, snake.getX(), snake.getY(), snake.getTailX(), snake.getTailY(), snake.getTailLen());
                Sleep(speedDelay);
                if (snake.getScore() > highScore) highScore = snake.getScore();
            } else {
                renderer.displayPause();
            }
        }
        endGame();
    }

    void handleInput() {
        while (_kbhit()) {
            switch (_getch()) {
                case 72: if (snake.getDirection() != DOWN) snake.setDirection(UP); break;
                case 80: if (snake.getDirection() != UP) snake.setDirection(DOWN); break;
                case 75: if (snake.getDirection() != RIGHT) snake.setDirection(LEFT); break;
                case 77: if (snake.getDirection() != LEFT) snake.setDirection(RIGHT); break;
                case 'x': isGameOver = true; break;
                case 'p': isPaused = !isPaused; break;
            }
        }
    }

    void update() {
        snake.move();
        if (snake.checkCollision()) {
            lives--;
            if (lives <= 0) isGameOver = true;
            else snake.reset();
        } else if (snake.eatFruit()) {
            if (snake.getScore() > highScore) highScore = snake.getScore();
        }
    }

    void endGame() {
        cout << "\nGame Over! Your final score is: " << snake.getScore() << "\nHigh Score: " << highScore << endl;
    }

    bool playAgain() {
        char choice;
        cout << "\nPlay Again? (Y/N): ";
        cin >> choice;
        return choice == 'Y' || choice == 'y';
    }
};

int main() {
    Game game;
    game.init();
    game.start();
    return 0;
}
