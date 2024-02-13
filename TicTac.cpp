// TicTac.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
using namespace std; 

void drawTicTacToeGrid() {
    std::cout << "   |   |   " << std::endl;
    std::cout << "---+---+---" << std::endl;
    std::cout << "   |   |   " << std::endl;
    std::cout << "---+---+---" << std::endl;
    std::cout << "   |   |   " << std::endl;
}

int** init_array(int dim) {

    int **ptr = new int*[dim];

    for (int i = 0; i < dim; i++) {
        ptr[i] = new int[dim] {};
    }
    return ptr; 
    
}

bool row_and_col_check(int** grid, int dim) {
    int row_sum = 0;
    int column_sum = 0;
    for (int i = 0; i < dim; i++)
    {
        row_sum = 0;
        column_sum = 0;
        for (int j = 0; j < dim; j++) {
            row_sum += grid[i][j];
            column_sum += grid[j][i];
            if (abs(row_sum) == dim || abs(column_sum) == dim) {
                return true;
            }
        }
    }
    return false;
}

bool diag_check(int** grid, int dim) {
    int diag0_sum = 0;
    int diag1_sum = 0;
    for (int i = 0; i < dim; i++)
    {
        diag0_sum += grid[i][i];
        diag1_sum += grid[i][dim - i - 1];
    }

    if (abs(diag0_sum) == dim || abs(diag1_sum) == dim) {
        return true;
    }
    else { return false; }
}

bool winCheck(int** grid, int dim) {

    bool win = ((diag_check(grid, dim) == true) || (row_and_col_check(grid,dim) == true));
    return win; 

}


int main() 
{
    int dim = 3; 
    int** grid = init_array(dim); 
    string player;
    int marker; 
    string move; 
    int coord1;
    int coord2;
    bool valid_move = false; 
    for (int turn = 0; turn < 9; turn++)
    {
        if (turn%2 == 0) {
            player = "Player 1";
            marker = 1; 
        }
        else {
            player = "Player 2";
            marker = -1;
        }

        while (valid_move == false) {
            cout << player << " Write  move";
            scanf_s("%d" "%d", &coord1, &coord2);
            if (grid[coord1][coord2] == 0) {
                grid[coord1][coord2] = marker; 
                valid_move = true; 
            }

        }
        valid_move = false; 
        bool win = winCheck(grid, dim); 
        if (win == true) {
            cout << player << " Has won!";
                break; 
        }
        if (turn == 8) {
            cout << "Draw!";
        }
    }
    //drawTicTacToeGrid();
    return 0;
}