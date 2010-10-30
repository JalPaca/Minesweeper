#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mineContainer->setSpacing(0);

    
    for( int i = 0; i < 10; i++)
    {
        for( int j = 0; j < 10; j++)
        {
            QPushButton* button = new QPushButton("");
            button->setMaximumHeight(30);
            button->setMaximumWidth(30);
            ui->mineContainer->addWidget(button, i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
