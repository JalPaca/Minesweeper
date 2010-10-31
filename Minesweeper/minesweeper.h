#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#define MINE 9

class Minesweeper
{
public:
    Minesweeper();
    bool isMine(int, int);
    int getValue(int, int);
private:
    void generateBoard();
    int mineBoard[10][10];
    void printBoard();
};

#endif // MINESWEEPER_H
