#include <iostream>
#include <vector>
#include <windows.h> 

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
     for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (pieces[currentPiece][i][j] == 1) {
                board[currentY + i][currentX + j] = 1; 
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            switch (board[i][j]) {
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

int main(int argc, char const *argv[])
{
    initBoard();
    
    bool isGameOver = false;
    while (!isGameOver) {
        Sleep(50);
        clearScreen();
        drawBoard();
    }

    std::cout << "Game over!" << std::endl;
    return 0;
}
