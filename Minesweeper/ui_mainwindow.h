/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Nov 9 17:55:49 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Game;
    QAction *action_Exit;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *action_Reset;
    QAction *actionTop_Ten;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *mineContainer;
    QLCDNumber *lcdTimer;
    QLCDNumber *lcdFlagCount;
    QPushButton *smileyFace;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(329, 376);
        QPalette palette;
        QBrush brush(QColor(184, 196, 214, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(194, 214, 214, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        QBrush brush2(QColor(214, 214, 214, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        MainWindow->setPalette(palette);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        action_Game = new QAction(MainWindow);
        action_Game->setObjectName(QString::fromUtf8("action_Game"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionHelp->setShortcutContext(Qt::ApplicationShortcut);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        action_Reset = new QAction(MainWindow);
        action_Reset->setObjectName(QString::fromUtf8("action_Reset"));
        action_Reset->setIconVisibleInMenu(false);
        actionTop_Ten = new QAction(MainWindow);
        actionTop_Ten->setObjectName(QString::fromUtf8("actionTop_Ten"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border:  1px, hidden;\n"
"}"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 40, 310, 272));
        mineContainer = new QGridLayout(gridLayoutWidget);
        mineContainer->setSpacing(0);
        mineContainer->setContentsMargins(11, 11, 11, 11);
        mineContainer->setObjectName(QString::fromUtf8("mineContainer"));
        mineContainer->setContentsMargins(0, 0, 0, 0);
        lcdTimer = new QLCDNumber(centralWidget);
        lcdTimer->setObjectName(QString::fromUtf8("lcdTimer"));
        lcdTimer->setGeometry(QRect(240, 10, 64, 23));
        lcdTimer->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"	background-color: black;\n"
"	color: red;\n"
"	foreground-color: red;\n"
"}"));
        lcdTimer->setFrameShadow(QFrame::Raised);
        lcdTimer->setSegmentStyle(QLCDNumber::Outline);
        lcdFlagCount = new QLCDNumber(centralWidget);
        lcdFlagCount->setObjectName(QString::fromUtf8("lcdFlagCount"));
        lcdFlagCount->setEnabled(true);
        lcdFlagCount->setGeometry(QRect(30, 10, 64, 23));
        lcdFlagCount->setAutoFillBackground(false);
        lcdFlagCount->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"	background-color: black;\n"
"	border: 1px;\n"
"	color: red;\n"
"}"));
        lcdFlagCount->setSmallDecimalPoint(true);
        lcdFlagCount->setNumDigits(4);
        lcdFlagCount->setSegmentStyle(QLCDNumber::Filled);
        smileyFace = new QPushButton(centralWidget);
        smileyFace->setObjectName(QString::fromUtf8("smileyFace"));
        smileyFace->setGeometry(QRect(150, 10, 31, 27));
        QIcon icon;
        icon.addFile(QString::fromUtf8("normal_face.png"), QSize(), QIcon::Normal, QIcon::On);
        smileyFace->setIcon(icon);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 329, 23));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Reset);
        menu_File->addSeparator();
        menu_File->addAction(actionTop_Ten);
        menu_File->addAction(action_Exit);
        menu_Help->addAction(actionHelp);
        menu_Help->addAction(actionAbout);

        retranslateUi(MainWindow);
        QObject::connect(action_Exit, SIGNAL(activated()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MineSweeper", 0, QApplication::UnicodeUTF8));
        action_Game->setText(QApplication::translate("MainWindow", "&Game", 0, QApplication::UnicodeUTF8));
        action_Game->setShortcut(QApplication::translate("MainWindow", "Shift+G", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        action_Exit->setShortcut(QApplication::translate("MainWindow", "Shift+X", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        actionHelp->setShortcut(QApplication::translate("MainWindow", "Shift+L", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Shift+A", 0, QApplication::UnicodeUTF8));
        action_Reset->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        action_Reset->setShortcut(QApplication::translate("MainWindow", "Shift+R", 0, QApplication::UnicodeUTF8));
        actionTop_Ten->setText(QApplication::translate("MainWindow", "Top Ten", 0, QApplication::UnicodeUTF8));
        actionTop_Ten->setShortcut(QApplication::translate("MainWindow", "Shift+T", 0, QApplication::UnicodeUTF8));
        smileyFace->setText(QString());
        menu_File->setTitle(QApplication::translate("MainWindow", "&Game", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
