#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("gtk");
    
    MainWindow w;
    w.show();
    return a.exec();
}
