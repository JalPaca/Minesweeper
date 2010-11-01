#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "minesweeper.h"
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
    HelpWindow *helpWindow;

public slots:
    void revealCell(QString);
};

#endif // MAINWINDOW_H
