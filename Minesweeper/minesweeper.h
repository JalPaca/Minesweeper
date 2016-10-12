/**
 * Minesweeper header files
 * @author Stephen Liang
 * @author Aisha Halim
 * Created for CS 340 Fall 2010 - Professor Troy
 */

#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#define MINE 9

class Minesweeper
{
public:
    Minesweeper(int gridSize, int mineNumber);
    ~Minesweeper();
    bool isMine(int, int);
    int getValue(int, int);
private:
    void generateBoard();
    std::vector<std::vector<int> > mineBoard;
};

#endif // MINESWEEPER_H
