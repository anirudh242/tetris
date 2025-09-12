#include <iostream>
#include <vector>

const int WIDTH = 11, HEIGHT = 21;
std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(WIDTH, 0));

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
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (board[i][j] == 9)
            {
                std::cout << " #"; 
            }
            else
            {
                std::cout << " ."; 
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    initBoard();
    drawBoard();

    return 0;
}
