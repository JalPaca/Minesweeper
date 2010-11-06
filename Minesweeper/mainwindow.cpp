#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QDebug>
#include <QtDebug>
#include "minesweeper.h"
#include "minesweeperbutton.h"
#include <QTimer>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    hasLost = false;
    minesClicked = 0;
    flagsFlagged = 0;
    hasStarted = false;
    ui->setupUi(this);
    ui->mineContainer->setSpacing(0);

    currentTime = 0;
    timer = new QTimer();

    //Connect help button
    helpWindow = new HelpWindow();
    aboutWindow =  new AboutWindow();

    connect(ui->actionHelp, SIGNAL(triggered()), helpWindow, SLOT(show()));
    connect(ui->actionAbout, SIGNAL(triggered()), aboutWindow, SLOT(show()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    game = new Minesweeper();

    //We will need to map the click to an object's coordinates
    signalMapper = new QSignalMapper(this);
    signalMapper2 = new QSignalMapper(this);
    //MineSweeperButton
    for( int i = 0; i < 10; i++)
    {
        for( int j = 0; j < 10; j++)
        {
            MineSweeperButton* button = new MineSweeperButton("");
            button->setAttribute(Qt::WA_LayoutUsesWidgetRect);
            button->setMaximumHeight(30);
            button->setMaximumWidth(30);

            ui->mineContainer->addWidget(button, i, j);
            QString coordinates = QString::number(i)+","+QString::number(j); //Coordinate of the button
            signalMapper->setMapping(button, coordinates);
            signalMapper2->setMapping(button, coordinates);
            QObject::connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
            connect(button, SIGNAL(rightButtonClicked()), signalMapper2, SLOT(map()));
        }
    }

    //Connect the signal mapper to the Minesweeper class
    QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(revealCell(QString)));
    QObject::connect(signalMapper2, SIGNAL(mapped(QString)), this, SLOT(hasRightClicked(QString)));
}

void MainWindow::hasRightClicked(QString coordinates)
{
        MineSweeperButton *buttonPushed = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));
        if ( !hasStarted ) timer->start(1000);
        hasStarted = true;
        if (! buttonPushed->isFlat() ) {
                buttonPushed->setFlat(false);
                if ( buttonPushed->text().isEmpty() ){
                        flagsFlagged++;
                        buttonPushed->setText("M");
                } else if ( buttonPushed->text().compare(QString("?")) == 0 ) {
                        buttonPushed->setText("");
                } else if ( buttonPushed->text().compare(QString("M")) == 0 ) {
                        flagsFlagged--;
                        buttonPushed->setText("?");
                        // don't do anything!
                } else {
                }
        } else {
                buttonPushed->setFlat(true);
        }
}

void MainWindow::updateTimer() {
        currentTime++;
        ui->timerLabel->setText(QString::number(currentTime));
}

void MainWindow::revealCell(QString coordinates)
{
    if (hasLost) return;
    if (minesClicked == 90) {
        won();
        return;
    }

    QStringList results = coordinates.split(",");
    MineSweeperButton *buttonPushed = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));
    if ( buttonPushed->text().compare(QString("M")) == 0 || buttonPushed->text().compare("?") == 0) {
            qDebug() << "flag clicked on...must return" << endl;
            return;
            qDebug() << "shouldn't be here!!1" << endl;
     //   buttonPushed->setAttribute();
    }
    if (buttonPushed->isFlat()) {
            qDebug() << "is flat; should be doing nothing!! " << endl;
            return;
    }
    qDebug() << "mine number incremented." << endl;
    buttonPushed->setFlat(true);    // if revealed, set button flat
    if ( results.size() != 2) //Ensure that we receive two coordinatesrightClickedButton
        exit(-1);

    int row = results.at(0).toInt();
    int column = results.at(1).toInt();

    buttonPushed->setText(QString::number(game->getValue(row, column)));
    if ( game->isMine( row, column ) ) {
        lost();
        return;
    }
    minesClicked++;
    if ( !hasStarted ) timer->start(1000);
    hasStarted = true;


}

void MainWindow::lost() {
    ui->timerLabel->setText("0");
    timer->stop();
    qDebug() << "num flags clicked: " << flagsFlagged << endl;
    qDebug() << "num mines clicked: " << minesClicked << endl;

    hasLost = true;
}

void MainWindow::won()
{
    ui->timerLabel->setText("0");
    timer->stop();
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
