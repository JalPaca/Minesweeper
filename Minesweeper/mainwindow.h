#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QSignalMapper>
#include "minesweeper.h"
#include "aboutwindow.h"
#include "helpwindow.h"

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
    HelpWindow *helpWindow;
    AboutWindow *aboutWindow;
    QTimer *timer;
    int currentTime;
    bool hasStarted;
    bool hasLost;
    int cellsRevealed;
    int minesFlagged;
    int flagsFlagged;
    void lost();
    void won();


private slots:
    void updateTimer();
    void hasRightClicked(QString);
    void reset();
    //void revealAll(QString);

public slots:
    void revealCell(QString);
};

#endif // MAINWINDOW_H
