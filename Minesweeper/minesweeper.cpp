#include "minesweeper.h"
#include <QtGlobal>
#include <QDebug>

Minesweeper::Minesweeper()
{
    //Initialize board
    for(int i = 0; i < 10; i++)
    {
        for ( int j = 0; j < 10; j++)
        {
            mineBoard[i][j] = 0;
        }
    }

    generateBoard();
}

void Minesweeper::generateBoard()
{
    //Generate ten mines and create its adjacent number list
    for( int i = 0; i < 10; i++)
    {
        int row, column;

        //Prevent generating mine on another mine
            row = qrand() % 10;
            column = qrand() % 10;


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
        if ( (row-1) != -1 && (column + 1) != 10 && mineBoard[row-1][column+1] != MINE)
            mineBoard[row-1][column+1]++;
        //Left
        if ( (column -1) != -1 && mineBoard[row][column-1] != MINE)
            mineBoard[row][column-1]++;
        //Right
        if ( (column + 1) != 10 && mineBoard[row][column+1] != MINE)
            mineBoard[row][column+1]++;
        //Bottom left
        if ( (row+1) != 10 && (column -1) != -1 && mineBoard[row+1][column-1] != MINE)
            mineBoard[row+1][column-1]++;
        //Bottom center
        if ( (row+1) != 10 && mineBoard[row+1][column] != MINE)
            mineBoard[row+1][column]++;
        //Bottom right
        if ( (row+1) != 10 && (column+1) != 10 && mineBoard[row+1][column+1] != MINE)
            mineBoard[row+1][column+1]++;
    }
}

bool Minesweeper::isMine(int row, int column)
{
        //Ensure the input is sanitary
        if ( row < 0 || row > 9)
            exit(-1);
        if ( column < 0 || column > 9)
            exit(-1);

        return mineBoard[row][column] == MINE;
}

int Minesweeper::getValue(int row, int column)
{
    //Ensure the input is sanitary
    if ( row < 0 || row > 9)
        exit(-1);
    if ( column < 0 || column > 9)
        exit(-1);

    return mineBoard[row][column];
}

void Minesweeper::printBoard()
{
    QString str = "\n";
    for ( int i = 0; i < 10; i++)
    {
        for ( int j = 0; j < 10; j++)
        {
            if ( mineBoard[i][j] != 10)
            str += QString::number(mineBoard[i][j]) + "   ";
            else
                str += QString::number(mineBoard[i][j]) + " ";
        }
        str += "\n";
    }
    qDebug() << str;
}
