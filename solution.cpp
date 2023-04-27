#include <iostream>

using namespace std;

enum direction_enum
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    NONE
};

int States_visited;
int EMPTY_ROW;
int EMPTY_COL;
bool SOLVED;
bool VISITED[9][9][9][9][9][9][9][9][9] = {};

void printCurrentPuzzle(char puzzle[3][3])
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            cout << puzzle[row][col] + 0 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void findEmptyPiece(char puzzle[3][3])
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (puzzle[row][col] == 0)
            {
                EMPTY_ROW = row;
                EMPTY_COL = col;
                return;
            }
        }
    }
}

bool solved(char puzzle[3][3])
{
    return puzzle[0][0] == 1 && puzzle[0][1] == 2 && puzzle[0][2] == 3 && puzzle[1][0] == 4 && puzzle[1][1] == 5 && puzzle[1][2] == 6 && puzzle[2][0] == 7 && puzzle[2][1] == 8 && puzzle[2][2] == 0;
}

void clearVisited()
{
    for(int i1 = 0; i1 < 9; ++i1)
    {
        for(int i2 = 0; i2 < 9; ++i2)
        {
            for(int i3 = 0; i3 < 9; ++i3)
            {
                for(int i4 = 0; i4 < 9; ++i4)
                {
                    for(int i5 = 0; i5 < 9; ++i5)
                    {
                        for(int i6 = 0; i6 < 9; ++i6)
                        {
                            for(int i7 = 0; i7 < 9; ++i7)
                            {
                                for(int i8 = 0; i8 < 9; ++i8)
                                {
                                    for(int i9 = 0; i9 < 9; ++i9)
                                    {
                                        VISITED[i1][i2][i3][i4][i5][i6][i7][i8][i9] = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool visited(char puzzle[3][3])
{
    return VISITED[puzzle[0][0]][puzzle[0][1]][puzzle[0][2]][puzzle[1][0]][puzzle[1][1]][puzzle[1][2]][puzzle[2][0]][puzzle[2][1]][puzzle[2][2]];
}

void mark_visit(char puzzle[3][3])
{
    States_visited++;
    VISITED[puzzle[0][0]][puzzle[0][1]][puzzle[0][2]][puzzle[1][0]][puzzle[1][1]][puzzle[1][2]][puzzle[2][0]][puzzle[2][1]][puzzle[2][2]] = true;
}

void makeMovement(char puzzle[3][3], direction_enum direction)
{
    switch (direction)
    {
    case LEFT:
        puzzle[EMPTY_ROW][EMPTY_COL] = puzzle[EMPTY_ROW][EMPTY_COL - 1];
        EMPTY_COL--;
        break;
    case UP:
        puzzle[EMPTY_ROW][EMPTY_COL] = puzzle[EMPTY_ROW - 1][EMPTY_COL];
        EMPTY_ROW--;
        break;
    case RIGHT:
        puzzle[EMPTY_ROW][EMPTY_COL] = puzzle[EMPTY_ROW][EMPTY_COL + 1];
        EMPTY_COL++;
        break;
    case DOWN:
        puzzle[EMPTY_ROW][EMPTY_COL] = puzzle[EMPTY_ROW + 1][EMPTY_COL];
        EMPTY_ROW++;
        break;
    default:
        break;
    }
    puzzle[EMPTY_ROW][EMPTY_COL] = 0;
}


void depthFirst(char puzzle[3][3], direction_enum previousMovement)
{
    if (solved(puzzle))
    {
        SOLVED = true;
        return;
    }
    if (visited(puzzle))
    {
        return;
    }
    mark_visit(puzzle);
    //LEFT
    if (previousMovement != RIGHT && EMPTY_COL > 0)
    {
        makeMovement(puzzle, LEFT);
        depthFirst(puzzle, LEFT);
        if (SOLVED)
        {
            return;
        }
        makeMovement(puzzle, RIGHT);
    }
    //UP
    if (previousMovement != DOWN && EMPTY_ROW > 0)
    {
        makeMovement(puzzle, UP);
        depthFirst(puzzle, UP);
        if (SOLVED)
        {
            return;
        }
        makeMovement(puzzle, DOWN);
    }
    //RIGHT
    if (previousMovement != LEFT && EMPTY_COL < 2)
    {
        makeMovement(puzzle, RIGHT);
        depthFirst(puzzle, RIGHT);
        if (SOLVED)
        {
            return;
        }
        makeMovement(puzzle, LEFT);
    }
    //DOWN
    if (previousMovement != UP && EMPTY_ROW < 2)
    {
        makeMovement(puzzle, DOWN);
        depthFirst(puzzle, DOWN);
        if (SOLVED)
        {
            return;
        }
        makeMovement(puzzle, UP);
    }
}

void initializeGlobalVariables()
{
    EMPTY_ROW = 0;
    EMPTY_COL = 0;
    SOLVED = false;
    States_visited = 0;
}

void solve(char puzzle[3][3])
{
    cout << "Solution starting." << endl;
    initializeGlobalVariables();
    clearVisited();
    findEmptyPiece(puzzle);
    depthFirst(puzzle, NONE);
    cout << "Solution found!" << endl;
}