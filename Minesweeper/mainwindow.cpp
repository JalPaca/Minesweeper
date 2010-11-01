#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QDebug>
#include "minesweeper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mineContainer->setSpacing(0);

    //Connect help button
    helpWindow = new HelpWindow();

    connect(ui->actionHelp, SIGNAL(triggered()), helpWindow, SLOT(show()));

    game = new Minesweeper();

    //We will need to map the click to an object's coordinates
    signalMapper = new QSignalMapper(this);
    
    for( int i = 0; i < 10; i++)
    {
        for( int j = 0; j < 10; j++)
        {
            QPushButton* button = new QPushButton("");
            button->setAttribute(Qt::WA_LayoutUsesWidgetRect);
            button->setMaximumHeight(30);
            button->setMaximumWidth(30);
            ui->mineContainer->addWidget(button, i, j);
            QString coordinates = QString::number(i)+","+QString::number(j); //Coordinate of the button
            signalMapper->setMapping(button, coordinates);
            QObject::connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        }
    }

    //Connect the signal mapper to the Minesweeper class
    QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(revealCell(QString)));
}

void MainWindow::revealCell(QString coordinates)
{
    QStringList results = coordinates.split(",");
    QPushButton *buttonPushed = qobject_cast<QPushButton *>(signalMapper->mapping(coordinates));

    if ( results.size() != 2) //Ensure that we receive two coordinates
        exit(-1);

    int row = results.at(0).toInt();
    int column = results.at(1).toInt();

    buttonPushed->setText(QString::number(game->getValue(row, column)));
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
