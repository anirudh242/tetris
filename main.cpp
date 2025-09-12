#include <iostream>
#include <vector>
#include <windows.h> 
#include <random>
#include <conio.h>   
#include <cstdlib>



const int WIDTH = 12, HEIGHT = 21;
std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(WIDTH, 0));

std::vector<std::vector<std::vector<int>>> pieces = {
    // I piece
    {
        {0,0,0,0}, 
        {1,1,1,1}, 
        {0,0,0,0}, 
        {0,0,0,0}
    },
    // O piece
    {
        {0,0,0,0}, 
        {0,1,1,0}, 
        {0,1,1,0}, 
        {0,0,0,0}
    },
    // T piece
    {
        {0,0,0,0},
        {0,1,0,0},
        {1,1,1,0}, 
        {0,0,0,0}
    },
    // L piece
    {
        {0,0,0,0}, 
        {0,0,1,0}, 
        {1,1,1,0}, 
        {0,0,0,0}
    },
    // J piece
    {
        {0,0,0,0}, 
        {1,0,0,0}, 
        {1,1,1,0}, 
        {0,0,0,0}
    },
    // Z piece
    {
        {0,0,0,0}, 
        {1,1,0,0}, 
        {0,1,1,0}, 
        {0,0,0,0}
    },
    // S piece
    {
        {0,0,0,0},
        {0,1,1,0}, 
        {1,1,0,0}, 
        {0,0,0,0}
    }
};

int currentPiece = 0;
int currentRotation = 0;
int currentX = (WIDTH / 2) - 1; // center
int currentY = 0;

int getRotatedBlock(int piece, int rotation, int row, int col) {
    int r = row;
    int c = col;

    for (int i = 0; i < rotation % 4; ++i) {
        // transpose + reverse to rotate
        int temp = r;
        r = c;
        c = 3 - temp;
    }

    return pieces[piece][r][c];
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
                displayBoard[currentY + i][currentX + j] = 1; 
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
}

bool doesPieceFit(int  piece, int rot, int xPos, int yPos)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (getRotatedBlock(piece, rot, i, j)  == 1) {
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
    int tickCounter = 10;
    int gameSpeed = 20;

    while (!isGameOver) 
    {
        Sleep(100);
        tickCounter++;

        char input = 0;
        if (_kbhit()) {
            input = _getch();
        }

        if (input == 'a' || input == 'A') { // Left
            if (doesPieceFit(currentPiece, currentRotation, currentX - 1, currentY)) 
            {
                currentX--;
            }
        }
        if (input == 'd' || input == 'D') { // Right
            if (doesPieceFit(currentPiece, currentRotation, currentX + 1, currentY))
             {
                currentX++;
            }
        }
        if (input == 's' || input == 'S') 
        { // Down (Soft Drop)
            if (doesPieceFit(currentPiece, currentRotation, currentX, currentY + 1)) 
            {
                currentY++;
            }
        }
        if (input == 'w' || input == 'W') 
        { // Rotate
            int nextRotation = (currentRotation + 1) % 4;
            if (doesPieceFit(currentPiece, nextRotation, currentX, currentY)) 
            {
                currentRotation = nextRotation;
            }
        }

        if (tickCounter >= gameSpeed)
        {
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
                            board[currentY + i][currentX + j] = 1;
                        }
                    }
                }

                currentRotation = 0;\
                currentX = (WIDTH / 2) - 2;
                currentY = 0;
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
    return 0;
}
