#include <iostream>
#include <vector>
#include <random>
#include <windows.h> 
#include <conio.h>   
#include <cstdlib>   

const int WIDTH = 12;
const int HEIGHT = 21;
std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(WIDTH, 0));

std::vector<std::vector<std::vector<int>>> pieces = {
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // I
    {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // O
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // T
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // L
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // J
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}, // Z
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}  // S
};

int currentPiece = 0;
int currentRotation = 0;
int currentX = (WIDTH / 2) - 1; // center
int currentY = 1;
int score = 0;

int getRotatedBlock(int piece, int rotation, int row, int col) {
    switch (rotation % 4) {
        case 0: return pieces[piece][row][col];           // 0 degrees
        case 1: return pieces[piece][3 - col][row];       // 90 degrees (inverse)
        case 2: return pieces[piece][3 - row][3 - col];   // 180 degrees (inverse)
        case 3: return pieces[piece][col][3 - row];       // 270 degrees (inverse)
    }
    return 0;
}

void clearScreen()
{
    system("clear");
}

void initBoard()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
            {
                board[i][j] = 9; 
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

void drawBoard()
{
    std::vector<std::vector<int>> displayBoard = board; // temporary to display before locking

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (getRotatedBlock(currentPiece, currentRotation, i, j) == 1) {
                int boardY = currentY + i;
                int boardX = currentX + j;
                if (boardY >= 0 && boardY < HEIGHT && boardX >= 0 && boardX < WIDTH) {
                    displayBoard[boardY][boardX] = 1; 
                }
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            switch (displayBoard[i][j]) {
                case 0:
                    std::cout << " .";
                    break;
                case 9:
                    std::cout << " #";
                    break;
                default:
                    std::cout << "[]";
                    break;
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Score: " << score << std::endl;
}

bool doesPieceFit(int piece, int rot, int xPos, int yPos)
{ 
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (getRotatedBlock(piece, rot, i, j) == 1) {
                if (yPos + i >= HEIGHT || xPos + j >= WIDTH || xPos + j < 0 || yPos + i < 0) {
                    return false; 
                }
                if (board[yPos + i][xPos + j] != 0) {
                    return false; 
                }
            }
        } 
    }
    return true;
}

int main(int argc, char const *argv[])
{
    // random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 6);
    currentPiece = distrib(gen);

    initBoard();
    
    bool isGameOver = false;
    int tickCounter = 0;
    int gameSpeed = 5;

    while (!isGameOver) 
    {
        Sleep(5);
        tickCounter++;

        char input = 0;
        if (_kbhit()) {
            input = _getch();
        }

        if (input == 'a' || input == 'A') { 
            if (doesPieceFit(currentPiece, currentRotation, currentX - 1, currentY)) 
            {
                currentX--;
            }
        }
        if (input == 'd' || input == 'D') { 
            if (doesPieceFit(currentPiece, currentRotation, currentX + 1, currentY))
             {
                currentX++;
            }
        }
        if (input == 's' || input == 'S') 
        { 
            if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + 1)) 
            {
                currentY++;
            }
        }
        if (input == 'w' || input == 'W') 
        { 
            int nextRotation = (currentRotation + 1) % 4;
            if (doesPieceFit(currentPiece, nextRotation, currentX, currentY)) 
            {
                currentRotation = nextRotation;
            }
        }

        if (tickCounter >= gameSpeed)
        {
            tickCounter = 0;
            if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + 1))
            {
                currentY++;
            } 
            else
            {
                // lock
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        if (getRotatedBlock(currentPiece, currentRotation, i, j) == 1) {
                             if (currentY + i >= 0 && currentY + i < HEIGHT && currentX + j >= 0 && currentX + j < WIDTH) {
                                board[currentY + i][currentX + j] = 1;
                            }
                        }
                    }
                }

                int linesCleared = 0;
                for (int i = HEIGHT - 2; i >= 1; --i)
                {
                    bool isLineFull = true;
                    for (int j = 1; j < WIDTH - 1; j++)
                    {
                        if (board[i][j] == 0)
                        {
                            isLineFull = false;
                            break;
                        }
                    }

                    if (isLineFull)
                    {
                        linesCleared++;
                        for (int j = i; j > 1; --j) // to move all lines down by one
                        {
                            for (int k = 1; k < WIDTH - 1; ++k)
                            {
                                board[j][k] = board[j - 1][k];
                            }
                        }
                        for (int k = 1; k < WIDTH - 1; ++k)
                        {
                            board[1][k] = 0;
                        }
                        i++;
                    }
                }
                
                if (linesCleared > 0)
                    score += linesCleared * 10 * linesCleared;

                currentRotation = 0;
                currentX = (WIDTH / 2) - 1;
                currentY = 1;
                currentPiece = distrib(gen);

                if (!doesPieceFit(currentPiece, currentRotation, currentX, currentY)) {
                    isGameOver = true;
                }
            }
        }
        clearScreen();
        drawBoard();
    }

    std::cout << "Game over!" << std::endl;
    std::cout << "Your score was: " << score << std::endl;
    return 0;
}

