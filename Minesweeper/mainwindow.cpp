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
    ui->lcdFlagCount->display (10-flagsFlagged);

    //Initialize statuses
    for ( int i = 0; i < 10; i++)
    {
        for ( int j = 0; j < 10; j++)
            mineStatus[i][j] = 0;
    }

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
            button->setIcon (QIcon(QString("not_flat_button.png")));
            button->icon ().setThemeName ("not_flat_button.png");
            button->setIconSize (QSize(30,30));

            ui->mineContainer->addWidget(button, i, j);
            QString coordinates = QString::number(i)+","+QString::number(j); //Coordinate of the button
            //button->setText(QString::number(game->getValue(i, j)));     // for debugging
            signalMapper->setMapping(button, coordinates);
            signalMapper2->setMapping(button, coordinates);

            QObject::connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
            connect(button, SIGNAL(rightButtonClicked()), signalMapper2, SLOT(map()));
            connect(button, SIGNAL(pressed()), this, SLOT(handleButtonPressed()));
            connect(button, SIGNAL(released()), this, SLOT(handleButtonReleased()));
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

        // find if flagged a mine
        QStringList results = coordinates.split(",");

        int row = results.at(0).toInt();
        int column = results.at(1).toInt();

        if ( !hasStarted ) timer->start(1000);
        hasStarted = true;
qDebug () << "right clicked!!!!";
        if (! buttonPushed->isFlat() ) {
                buttonPushed->setFlat(false);
qDebug () << "isn't flat when right clicked!"<< buttonPushed->icon ().themeName ();
                //0 = flat, 1 = flat with flag, 2 =
//it appears that question marks are cleared but flags are not
                if ( mineStatus[row][column] == 0){
                    qDebug() << "case1";
                        flagsFlagged++;
                        //buttonPushed->setText("M");
                        buttonPushed->setIcon (QIcon(QString("flag_no_flat_button.png")));
                        mineStatus[row][column] = 1;
                        buttonPushed->setIconSize (QSize(30,30));
                        ui->lcdFlagCount->display(10-flagsFlagged);

                        if ( game->getValue(row, column) == 9 ) {
                            minesFlagged++;
                        }
                } else if ( mineStatus[row][column] == 1 ) {
                    qDebug() << "case2";
                        flagsFlagged--;
                        ui->lcdFlagCount->display(10-flagsFlagged);
                        buttonPushed->setText("");
                        buttonPushed->setIcon (QIcon("unknown_no_flat_button.png"));
                        mineStatus[row][column] = 2;
                        buttonPushed->setIconSize (QSize(30,30));
                } else if ( mineStatus[row][column] == 2 ) {
                        ui->lcdFlagCount->display(10-flagsFlagged);
                        qDebug() << "case3";
                        buttonPushed->setIcon (QIcon(QString("not_flat_button.png")));
                       mineStatus[row][column] = 0;
                        // don't do anything!
                        qDebug() << "asdf";
                }else {
                    qDebug() << "case badddd" << endl;
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

    int row = results.at(0).toInt();
    int column = results.at(1).toInt();

    qDebug() << "This cell contains a " << game->getValue(row, column);

    if ( mineStatus[row][column] == 1 || mineStatus[row][column] == 2) {
            qDebug() << "flag clicked on...must return" << endl;
            cellsRevealed--;
            return;
        }else{
            qDebug() << "The status is: " << mineStatus[row][column];
        }
    if (buttonPushed->isFlat()) {
            qDebug() << "is flat; should be doing nothing!! " << endl;
            cellsRevealed--;
            return;
    }

    qDebug() << "mine number incremented." << endl;

    //!!!!ahh baddd recursive function call for clearing
    if ( game->getValue (row, column) == 0 ) {
        cellsRevealed--;
        clear(row, column, true);
    }

    buttonPushed->setFlat(true);    // if revealed, set button flat
  //  buttonPushed->setDisabled(true);    // according to Prof.'s specs

    if ( results.size() != 2) //Ensure that we receive two coordinatesrightClickedButton
        exit(-1);

    //buttonPushed->setText(QString::number(game->getValue(row, column)));
    if ( game->getValue (row, column) == 0) {
        buttonPushed->setIcon (QIcon(QString("flat_button.png")));
    } else if ( game->getValue (row,column) == 1) {
        buttonPushed->setIcon (QIcon(QString("one_flat_button.png")));
    } else if (game->getValue (row,column) == 2) {
        buttonPushed->setIcon (QIcon(QString("two_flat_button.png")));
    } else if (game->getValue (row,column) == 3){
        buttonPushed->setIcon (QIcon(QString("three_flat_button.png")));
    } else if (game->getValue (row,column) == 4){
        buttonPushed->setIcon (QIcon(QString("four_flat_button.png")));
    } else if (game->getValue (row,column) == 5){
        buttonPushed->setIcon (QIcon(QString("five_flat_button.png")));
    } else if (game->getValue (row,column) == 6){
        buttonPushed->setIcon (QIcon(QString("six_flat_button.png")));
    } else if (game->getValue (row,column) == 7){
        buttonPushed->setIcon (QIcon(QString("seven_flat_button.png")));
    } else if (game->getValue (row,column) == 8){
        buttonPushed->setIcon (QIcon(QString("eight_flat_button.png")));
    } else if (game->getValue(row, column) == 9) {
        buttonPushed->setIcon (QIcon(QString("mine_exploded_flat_button.png")));
    }else {
        qDebug() << "This should never happen";
    }

    if ( game->isMine( row, column ) ) {
        lost();
        cellsRevealed--;
        return;
    }else{
        ui->smileyFace->setIcon(QIcon("normal_face.png"));
    }

    if ( !hasStarted ) timer->start(1000);
    hasStarted = true;
}

void MainWindow::clear(int row, int column, bool allowedClear)
{
    QString coordinates = QString::number(row) + "," + QString::number(column);
    qDebug() << "I am checking " + QString::number(row) + "col: " + QString::number(column);
    MineSweeperButton *buttonPushed = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));

        if ( buttonPushed->isFlat () == false && game->getValue (row, column) != 9 && allowedClear == true && mineStatus[row][column] != 1)
        {
     //       buttonPushed->setText (QString::number (game->getValue (row, column)));

            buttonPushed->setFlat (true);
            if ( game->getValue (row, column) == 0) {
                buttonPushed->setIcon (QIcon(QString("flat_button.png")));
                buttonPushed->icon ().setThemeName ("flat_button.png");
            } else if ( game->getValue (row,column) == 1) {
                buttonPushed->setIcon (QIcon(QString("one_flat_button.png")));
                buttonPushed->icon ().setThemeName ("one_flat_button.png");
            } else if (game->getValue (row,column) == 2) {
                buttonPushed->setIcon (QIcon(QString("two_flat_button.png")));
                buttonPushed->icon ().setThemeName ("two_flat_button.png");
            } else {
                buttonPushed->setIcon (QIcon(QString("three_flat_button.png")));
                buttonPushed->icon ().setThemeName ("three_flat_button.png");
            }
            //           buttonPushed->setDisabled (true);
            cellsRevealed++;

            if ( game->getValue (row, column) == 0)
                allowedClear = true;
            else
                allowedClear = false;

            //Top left
            if ( (row-1) != -1 && (column -1) != -1)
                clear(row-1, column-1, allowedClear);
            //Top center
            if ( (row-1) != -1)
                clear(row-1, column, allowedClear);
            //Top right
            if ( (row-1) != -1 && (column + 1) != 10)
                clear(row-1, column+1, allowedClear);
            //Left
            if ( (column -1) != -1)
                clear(row, column-1, allowedClear);
            //Right
            if ( (column + 1) != 10)
                clear(row, column+1, allowedClear);
            //Bottom left
            if ( (row+1) != 10 && (column -1) != -1)
                clear(row+1, column-1, allowedClear);
            //Bottom center
            if ( (row+1) != 10)
                clear(row+1, column, allowedClear);
            //Bottom right
            if ( (row+1) != 10 && (column+1) != 10)
            {
                clear(row+1, column+1, allowedClear);
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
    ui->smileyFace->setIcon(QIcon("sad_face.png"));
    timer->stop();
    for ( int i = 0; i < 10; i++ ) {
        for ( int j = 0; j < 10; j++ ) {
            QString coordinates = QString::number(i)+","+QString::number(j);
            MineSweeperButton *button = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));
            if (! button->isFlat () && game->getValue (i,j) == 9 ) {
                button->setFlat (true);
   //             button->setDisabled (true);
                if ( mineStatus[i][j] == 1 ) {
                    button->setIcon (QIcon(QString("mine_disarmed_flat_button.png")));
                } else {
                    button->setIcon (QIcon(QString("mine_flat_button.png")));
                }
            }

        }
    }
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

    this->timer->stop();
    ui->lcdFlagCount->display(10-flagsFlagged);
    ui->lcdTimer->display(currentTime);
    ui->smileyFace->setIcon(QIcon("normal_face.png"));

//    this->game;
    game = new Minesweeper();

    for( int i = 0; i < 10; i++)
    {
        for( int j = 0; j < 10; j++ )
        {
            QString coordinates = QString::number(i)+","+QString::number(j);
            MineSweeperButton *button = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));
            button->setText("");
            button->setIcon (QIcon("not_flat_button.png"));
            button->icon ().setThemeName ("elementary");
            button->setIconSize (QSize(30,30));
            button->setFlat(false);
            button->setDisabled (false);
        }

    }
}

void MainWindow::won()
{
    //ui->timerLabel->setText("0");
    ui->smileyFace->setIcon(QIcon("happy_face.png"));
    timer->stop();
    hasFinished = true;

    for ( int i = 0; i < 10; i++ ) {
        for ( int j = 0; j < 10; j++ ) {
            QString coordinates = QString::number(i)+","+QString::number(j);
            MineSweeperButton *button = qobject_cast<MineSweeperButton *>(signalMapper->mapping(coordinates));
            if (! button->isFlat () ) {
                button->setFlat (true);
                button->setIcon (QIcon(QString("mine_flat_button.png")));
                button->icon ().setThemeName ("mine_flat_button.png");
                button->setDisabled (true);
            }
        }
    }

    SaveScore* scoreScreen = new SaveScore(this->currentTime);

    scoreScreen->show();
}

void MainWindow::handleSmileyFace()
{
    this->reset();
}

void MainWindow::handleButtonPressed()
{
    ui->smileyFace->setIcon(QIcon("scared_face.png"));
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

void MainWindow::handleButtonReleased()
{
    ui->smileyFace->setIcon(QIcon("normal_face.png"));
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
