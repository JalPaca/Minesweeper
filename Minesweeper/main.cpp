#include <QtGui/QApplication>
#include "mainwindow.h"
#include "minesweeper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("gtk");
    
    MainWindow w;
    w.show();

    Minesweeper board;
    return a.exec();
}
