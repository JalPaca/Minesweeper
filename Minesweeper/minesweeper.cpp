/**
 * MineSweeper
 * Handles the minesweeper game, contains the actual board used
 * @author Stephen Liang
 * @author Aisha Halim
 * Created for CS 340 Fall 2010 - Professor Troy
 */
#include "minesweeper.h"
#include <ctime>
#include <QtGlobal>

/**
  * Constructor
  * Initializes the board
  */
Minesweeper::Minesweeper(int gridSize, int numberOfMines)
{
    this->gridSize = gridSize;
    this->numberOfMines = numberOfMines;
    //Initialize board
    mineBoard.resize(gridSize);
    for (int i = 0; i < gridSize; ++i)
        mineBoard[i].resize(gridSize);
    //Generates the board with mines and populates the number of mines around it
    generateBoard();
}

/**
  * Destructor
  */
Minesweeper::~Minesweeper()
{
}

/**
  * generateBoard()
  * Generates the board with mines and populates the number of mines around it
  */
void Minesweeper::generateBoard()
{
    /* initialize random seed: */
    qsrand (time(NULL));
    //Generate ten mines and create its adjacent number list
    for( int i = 0; i < numberOfMines; i++)
    {
        int row, column;

        //Prevent generating mine on another mine
        do
        {
            row = qrand() % gridSize;
            column = qrand() % gridSize;
        }while (mineBoard[row][column] == MINE);

        mineBoard[row][column] = MINE; //Number 9 indiciates a mine

        //Now that we have a mine created, increment its surroundings
        //There are eight of them

        //Top left
        if ( (row-1) != -1 && (column -1) != -1 && mineBoard[row-1][column-1] != MINE)
            mineBoard[row-1][column-1]++;
        //Top center
        if ( (row-1) != -1 && mineBoard[row-1][column] != MINE)
            mineBoard[row-1][column]++;
        //Top right
        if ( (row-1) != -1 && (column + 1) != gridSize && mineBoard[row-1][column+1] != MINE)
            mineBoard[row-1][column+1]++;
        //Left
        if ( (column -1) != -1 && mineBoard[row][column-1] != MINE)
            mineBoard[row][column-1]++;
        //Right
        if ( (column + 1) != gridSize && mineBoard[row][column+1] != MINE)
            mineBoard[row][column+1]++;
        //Bottom left
        if ( (row+1) != gridSize && (column -1) != -1 && mineBoard[row+1][column-1] != MINE)
            mineBoard[row+1][column-1]++;
        //Bottom center
        if ( (row+1) != gridSize && mineBoard[row+1][column] != MINE)
            mineBoard[row+1][column]++;
        //Bottom right
        if ( (row+1) != gridSize && (column+1) != gridSize && mineBoard[row+1][column+1] != MINE)
            mineBoard[row+1][column+1]++;
    }
}

/**
  * isMine(int, int)
  * Determines if there is a mine
  * @param int - Row to inspect
  * @param int - Column to inspect
  * @return bool - Whether or not the location is a mine
  */
bool Minesweeper::isMine(int row, int column)
{
        //Ensure the input is sanitary
        if ( row < 0 || row > (gridSize - 1))
            qFatal("Error in input");
        if ( column < 0 || column > (gridSize - 1))
            qFatal("Error in input");

        return mineBoard[row][column] == MINE;
}

/**
  * getValue(int, int)
  * Returns the value of the given cell
  * @param int - Row to inspect
  * @param int - Column to inspect
  * @return int - The value at the row
  */
int Minesweeper::getValue(int row, int column)
{
    //Ensure the input is sanitary
    if ( row < 0 || row > (gridSize - 1))
        qFatal("Error in input");
    if ( column < 0 || column > (gridSize - 1))
        qFatal("Error in input");

    return mineBoard[row][column];
}
