#include <iostream>
#include <unordered_set>

using namespace std;

enum direction_enum
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    NONE
};

struct State
{
    char puzzle[3][3];
    direction_enum previousMovement;
    int emptyRow;
    int emptyCol;
};

class StatesStack
{
public:
    StatesStack():mStates(new State[400000]), mSize(0) {}
    ~StatesStack() { delete[] mStates; }
    bool empty() { return mSize == 0;} 
    void push(State state)
    {
        mStates[mSize] = state;
        mSize++;
    }
    State pop()
    {
        mSize--;
        return mStates[mSize];
    }
private:
    State* mStates;
    int mSize;
};

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

void findEmptyPiece(State& state)
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (state.puzzle[row][col] == 0)
            {
                state.emptyRow = row;
                state.emptyCol = col;
                return;
            }
        }
    }
}

bool solved(char puzzle[3][3])
{
    return puzzle[0][0] == 1 && puzzle[0][1] == 2 && puzzle[0][2] == 3 && puzzle[1][0] == 4 && puzzle[1][1] == 5 && puzzle[1][2] == 6 && puzzle[2][0] == 7 && puzzle[2][1] == 8 && puzzle[2][2] == 0;
}

int getIdentifier(char puzzle[3][3])
{
    return (puzzle[0][0] * 100000000) + (puzzle[0][1] * 10000000) + (puzzle[0][2] * 1000000) + (puzzle[1][0] * 100000) + (puzzle[1][1] * 10000) + (puzzle[1][2] * 1000) + (puzzle[2][0] * 100) + (puzzle[2][1] * 10) + puzzle[2][2];
}

bool visited(unordered_set<int> &visitedSet, char puzzle[3][3])
{
    int puzzleIdentifier = getIdentifier(puzzle);
    return visitedSet.count(puzzleIdentifier) == 1;
}

void mark_visit(unordered_set<int> &visitedSet, char puzzle[3][3])
{
    int puzzleIdentifier = getIdentifier(puzzle);
    visitedSet.insert(puzzleIdentifier);
}

void makeMovement(State& state, direction_enum direction)
{
    switch (direction)
    {
    case LEFT:
        state.puzzle[state.emptyRow][state.emptyCol] = state.puzzle[state.emptyRow][state.emptyCol - 1];
        state.emptyCol--;
        state.previousMovement = LEFT;
        break;
    case UP:
        state.puzzle[state.emptyRow][state.emptyCol] = state.puzzle[state.emptyRow - 1][state.emptyCol];
        state.emptyRow--;
        state.previousMovement = UP;
        break;
    case RIGHT:
        state.puzzle[state.emptyRow][state.emptyCol] = state.puzzle[state.emptyRow][state.emptyCol + 1];
        state.emptyCol++;
        state.previousMovement = RIGHT;
        break;
    case DOWN:
        state.puzzle[state.emptyRow][state.emptyCol] = state.puzzle[state.emptyRow + 1][state.emptyCol];
        state.emptyRow++;
        state.previousMovement = DOWN;
        break;
    default:
        break;
    }
    state.puzzle[state.emptyRow][state.emptyCol] = 0;
}

void copyPuzzle(char toPuzzle[3][3], char puzzle[3][3])
{
    toPuzzle[0][0] = puzzle[0][0];
    toPuzzle[0][1] = puzzle[0][1];
    toPuzzle[0][2] = puzzle[0][2];
    toPuzzle[1][0] = puzzle[1][0];
    toPuzzle[1][1] = puzzle[1][1];
    toPuzzle[1][2] = puzzle[1][2];
    toPuzzle[2][0] = puzzle[2][0];
    toPuzzle[2][1] = puzzle[2][1];
    toPuzzle[2][2] = puzzle[2][2];
}

void solve(char puzzle[3][3])
{
    cout << "Solution starting." << endl;
    unordered_set<int> visitedSet;

    State newState;
    newState.previousMovement = NONE;
    copyPuzzle(newState.puzzle, puzzle);
    findEmptyPiece(newState);

    StatesStack statesStack;
    statesStack.push(newState);

    direction_enum previousMovement = NONE;
    bool solutionFound = false;
    int statesAnalyzed = 0;
    while(!solutionFound && !statesStack.empty())
    {
        statesAnalyzed++;
        State currentState = statesStack.pop();
        previousMovement = currentState.previousMovement;
        if (solved(currentState.puzzle))
        {
            solutionFound = true;
            copyPuzzle(puzzle, currentState.puzzle);
            continue;
        }
        
        //LEFT
        if (previousMovement != RIGHT && currentState.emptyCol > 0)
        {
            makeMovement(currentState, LEFT);
            if (!visited(visitedSet, currentState.puzzle))
            {
                statesStack.push(currentState);
                mark_visit(visitedSet, currentState.puzzle);
            }
            makeMovement(currentState, RIGHT);
        }
        //UP
        if (previousMovement != DOWN && currentState.emptyRow > 0)
        {
            makeMovement(currentState, UP);
            if (!visited(visitedSet, currentState.puzzle))
            {
                statesStack.push(currentState);
                mark_visit(visitedSet, currentState.puzzle);
            }
            makeMovement(currentState, DOWN);
        }
        //RIGHT
        if (previousMovement != LEFT && currentState.emptyCol < 2)
        {
            makeMovement(currentState, RIGHT);
            if (!visited(visitedSet, currentState.puzzle))
            {
                statesStack.push(currentState);
                mark_visit(visitedSet, currentState.puzzle);
            }
            makeMovement(currentState, LEFT);
        }
        //DOWN
        if (previousMovement != UP && currentState.emptyRow < 2)
        {
            makeMovement(currentState, DOWN);
            if (!visited(visitedSet, currentState.puzzle))
            {
                statesStack.push(currentState);
                mark_visit(visitedSet, currentState.puzzle);
            }
            makeMovement(currentState, UP);
        }
    }
    cout << "Solution found! " << statesAnalyzed << " states were analyzed." << endl << endl;
}