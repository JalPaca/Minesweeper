#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QDebug>
#include <QtDebug>
#include "minesweeper.h"
#include "minesweeperbutton.h"
#include "savescore.h"
#include "topten.h"
#include "aboutwindow.h"
#include "helpwindow.h"
#include <QTimer>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    hasFinished = false;
    cellsRevealed = 0;
    flagsFlagged = 0;
    minesFlagged = 0;
    hasStarted = false;
    currentTime = 0;

    ui->setupUi(this);

    ui->mineContainer->setSpacing(0);
    timer = new QTimer();
    ui->lcdFlagCount->setDigitCount(2);

    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(handleHelpButton()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(handleAboutButton()));
    connect(ui->action_Reset, SIGNAL(triggered()), this, SLOT(reset()));
    connect(ui->smileyFace, SIGNAL(clicked()), this, SLOT(handleSmileyFace()));
    connect(ui->actionTop_Ten, SIGNAL(triggered()), this, SLOT(handleTopTen()));

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    game = new Minesweeper();

    //We will need to map the click to an object's coordinates
    signalMapper = new QSignalMapper(this);
    signalMapper2 = new QSignalMapper(this);
    //MineSweeperButton
    for( int i = 0; i < 10; i++)
    {
        for( int j = 0; j < 10; j++ )
        {
            MineSweeperButton* button = new MineSweeperButton("");
            button->setAttribute(Qt::WA_LayoutUsesWidgetRect);
            button->setMaximumHeight(30);
            button->setMaximumWidth(30);

            ui->mineContainer->addWidget(button, i, j);
            QString coordinates = QString::number(i)+","+QString::number(j); //Coordinate of the button
            button->setText(QString::number(game->getValue(i, j)));     // for debugging
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
    if (hasFinished) return;
        MineSweeperButton *buttonPushed = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));

        if ( !hasStarted ) timer->start(1000);
        hasStarted = true;

        if (! buttonPushed->isFlat() ) {
                buttonPushed->setFlat(false);
                if ( buttonPushed->text().isEmpty() || buttonPushed->text().compare("!") == 0){
                        flagsFlagged++;
                        buttonPushed->setText("M");
                        ui->lcdFlagCount->display(flagsFlagged);

                        // find if flagged a mine
                        QStringList results = coordinates.split(",");

                        int row = results.at(0).toInt();
                        int column = results.at(1).toInt();

                        if ( game->getValue(row, column) == 9 ) {
                            minesFlagged++;
                        }
                } else if ( buttonPushed->text().compare(QString("?")) == 0 ) {
                        buttonPushed->setText("");
                } else if ( buttonPushed->text().compare(QString("M")) == 0 ) {
                        flagsFlagged--;
                        ui->lcdFlagCount->display(flagsFlagged);
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
        ui->lcdTimer->display(currentTime);
      //  ui->timerLabel->setText(QString::number(currentTime));
}

void MainWindow::revealCell(QString coordinates)
{
    if (hasFinished) return;
    else cellsRevealed++;
    qDebug() << "Cells: " << cellsRevealed;
    if (cellsRevealed == 90) {
        won();
        return;
    }
    qDebug() << "Cells revealed: " << cellsRevealed;
    QStringList results = coordinates.split(",");
    MineSweeperButton *buttonPushed = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));
    if ( buttonPushed->text().compare(QString("M")) == 0 || buttonPushed->text().compare("?") == 0) {
            qDebug() << "flag clicked on...must return" << endl;
            cellsRevealed--;
            return;
    }
    if (buttonPushed->isFlat()) {
            qDebug() << "is flat; should be doing nothing!! " << endl;
            cellsRevealed--;
            return;
    }
    qDebug() << "mine number incremented." << endl;

    int row = results.at(0).toInt();
    int column = results.at(1).toInt();

    //!!!!ahh baddd recursive function call for clearing
    clear(row, column);
    buttonPushed->setFlat(true);    // if revealed, set button flat
    buttonPushed->setDisabled(true);    // according to Prof.'s specs

    if ( results.size() != 2) //Ensure that we receive two coordinatesrightClickedButton
        exit(-1);

    buttonPushed->setText(QString::number(game->getValue(row, column)));
    if ( game->isMine( row, column ) ) {
        lost();
        cellsRevealed--;
        return;
    }

    if ( !hasStarted ) timer->start(1000);
    hasStarted = true;
}

void MainWindow::clear(int row, int column)
{
    QString coordinates = QString::number(row) + "," + QString::number(column);
    qDebug() << "I am checking " + QString::number(row) + "col: " + QString::number(column);
    MineSweeperButton *buttonPushed = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));

        if ( game->getValue(row, column) == 0 && buttonPushed->isFlat () == false)
        {
            buttonPushed->setText ("0");
            buttonPushed->setFlat (true);
            buttonPushed->setDisabled (true);
            cellsRevealed++;

            //Top left
            if ( (row-1) != -1 && (column -1) != -1)
                clear(row-1, column-1);
            //Top center
            if ( (row-1) != -1)
                clear(row-1, column);
            //Top right
            if ( (row-1) != -1 && (column + 1) != 10)
                clear(row-1, column+1);
            //Left
            if ( (column -1) != -1)
                clear(row, column-1);
            //Right
            if ( (column + 1) != 10)
                clear(row, column+1);
            //Bottom left
            if ( (row+1) != 10 && (column -1) != -1)
                clear(row+1, column-1);
            //Bottom center
            if ( (row+1) != 10)
                clear(row+1, column);
            //Bottom right
            if ( (row+1) != 10 && (column+1) != 10)
            {
                clear(row+1, column+1);
            }
        }
        else
        {
            qDebug() << "Row: " << row << "col: " << column << " is not zero, rather it is: " << game->getValue (row, column);
            qDebug() << "Row: " << row << " col: " << column << " is " << buttonPushed->isFlat ();
        }
}

void MainWindow::lost() {
   // ui->timerLabel->setText("0");
    timer->stop();
    qDebug() << "num flags flagged: " << flagsFlagged << endl;
    qDebug() << "num cells revealed: " << cellsRevealed << endl;
    qDebug() << "num mines flagged: " << minesFlagged << endl;
    hasFinished = true;
}

void MainWindow::reset() {
    hasFinished = false;
    cellsRevealed = 0;
    flagsFlagged = 0;
    minesFlagged = 0;
    hasStarted = false;
    currentTime = 0;

    ui->lcdFlagCount->display(flagsFlagged);
    ui->lcdTimer->display(currentTime);

//    this->game;
    game = new Minesweeper();

    for( int i = 0; i < 10; i++)
    {
        for( int j = 0; j < 10; j++ )
        {
            QString coordinates = QString::number(i)+","+QString::number(j);
            MineSweeperButton *button = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));
            button->setText("");
            button->setFlat(false);
            button->setDisabled (false);
        }

    }
}

void MainWindow::won()
{
    //ui->timerLabel->setText("0");
    timer->stop();
    hasFinished = true;

    SaveScore* scoreScreen = new SaveScore(this->currentTime);

    scoreScreen->show();
}

void MainWindow::handleSmileyFace()
{
    won();
}

void MainWindow::handleTopTen()
{
    qDebug() << "Top ten";
    TopTen* scores = new TopTen();
    scores->show();
}

void MainWindow::handleHelpButton()
{
    HelpWindow* help = new HelpWindow();
    help->show();
}

void MainWindow::handleAboutButton()
{
    AboutWindow* aboutWindow = new AboutWindow();

    aboutWindow->show();
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
