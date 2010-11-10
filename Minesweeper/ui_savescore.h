/********************************************************************************
** Form generated from reading UI file 'savescore.ui'
**
** Created: Tue Nov 9 21:39:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVESCORE_H
#define UI_SAVESCORE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_SaveScore
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *name_label;
    QLineEdit *name;
    QLabel *congrats;

    void setupUi(QDialog *SaveScore)
    {
        if (SaveScore->objectName().isEmpty())
            SaveScore->setObjectName(QString::fromUtf8("SaveScore"));
        SaveScore->resize(400, 300);
        buttonBox = new QDialogButtonBox(SaveScore);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        name_label = new QLabel(SaveScore);
        name_label->setObjectName(QString::fromUtf8("name_label"));
        name_label->setGeometry(QRect(30, 140, 51, 21));
        name = new QLineEdit(SaveScore);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(110, 140, 241, 27));
        congrats = new QLabel(SaveScore);
        congrats->setObjectName(QString::fromUtf8("congrats"));
        congrats->setGeometry(QRect(40, 30, 301, 81));
        congrats->setWordWrap(true);

        retranslateUi(SaveScore);

        QMetaObject::connectSlotsByName(SaveScore);
    } // setupUi

    void retranslateUi(QDialog *SaveScore)
    {
        SaveScore->setWindowTitle(QApplication::translate("SaveScore", "Winner!!!!", 0, QApplication::UnicodeUTF8));
        name_label->setText(QApplication::translate("SaveScore", "Name", 0, QApplication::UnicodeUTF8));
        congrats->setText(QApplication::translate("SaveScore", "Congratulations! You have won Minesweeper, please enter your name!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SaveScore: public Ui_SaveScore {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVESCORE_H
