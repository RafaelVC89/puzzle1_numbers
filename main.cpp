#include <iostream>
#include <chrono>
#include "solution.cpp"

using namespace std;
using namespace std::chrono;

extern void solve(char puzzle[3][3]);

char PUZZLE[3][3] = 
    {1, 2, 3,
     4, 5, 6,
     7, 8, 0};

void printPuzzle()
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            cout << PUZZLE[row][col] + 0 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void makeRandomMovement(int &row, int &column)
{
    int movement = rand() % 4;
    switch (movement)
    {
        case 0://Left
            if(column > 0)
            {
                PUZZLE[row][column] = PUZZLE[row][column - 1];
                column--;
            }
            break;
        case 1://Up
            if(row > 0)
            {
                PUZZLE[row][column] = PUZZLE[row - 1][column];
                row--;
            }
            break;
        case 2://Right
            if(column < 2)
            {
                PUZZLE[row][column] = PUZZLE[row][column + 1];
                column++;
            }
            break;
        case 3://Down
            if(row < 2)
            {
                PUZZLE[row][column] = PUZZLE[row + 1][column];
                row++;
            }
            break;
        default:
            cout << "Error, default should not be reached." << endl;
            break;
    }
    PUZZLE[row][column] = 0;
}

int main()
{
    //Initialize random seed with a static value to get the same random number each time
    srand(4);
    int row = 2;
    int column = 2;
    for (int i = 0; i < 1000; ++i)
    {
        makeRandomMovement(row, column);
    }
    cout << "Puzzle to solve: " << endl;
    printPuzzle();
    auto start = steady_clock::now();
    solve(PUZZLE);
    auto end = steady_clock::now();
    cout << "Puzzle after solution: " << endl;
    printPuzzle();
    cout << "Solution took " << duration_cast<milliseconds>(end - start).count() << " milliseconds." << endl;
    return 0;
}