#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QSignalMapper>
#include "minesweeper.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    Minesweeper *game;
    QSignalMapper *signalMapper;
    QSignalMapper *signalMapper2;

    QTimer *timer;
    int currentTime;
    bool hasStarted;
    bool hasFinished;
    int cellsRevealed;
    int minesFlagged;
    int flagsFlagged;
    void lost();
    void won();
    void clear(int, int, bool);
    int mineStatus[10][10];

private slots:
    void updateTimer();
    void hasRightClicked(QString);
    void reset();
    void handleSmileyFace();
    void handleTopTen();
    void handleAboutButton();
    void handleHelpButton();
    void handleButtonPressed();
    void handleButtonReleased();
    //void revealAll(QString);

public slots:

    void revealCell(QString);

};

#endif // MAINWINDOW_H
