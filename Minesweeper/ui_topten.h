/********************************************************************************
** Form generated from reading UI file 'topten.ui'
**
** Created: Mon Nov 8 19:10:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPTEN_H
#define UI_TOPTEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TopTen
{
public:
    QLabel *label;
    QLabel *topTenList;
    QPushButton *resetButton;
    QPushButton *close;

    void setupUi(QDialog *TopTen)
    {
        if (TopTen->objectName().isEmpty())
            TopTen->setObjectName(QString::fromUtf8("TopTen"));
        TopTen->resize(273, 364);
        label = new QLabel(TopTen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 181, 41));
        topTenList = new QLabel(TopTen);
        topTenList->setObjectName(QString::fromUtf8("topTenList"));
        topTenList->setGeometry(QRect(20, 70, 231, 221));
        topTenList->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        resetButton = new QPushButton(TopTen);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(20, 320, 93, 27));
        close = new QPushButton(TopTen);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(140, 320, 93, 27));

        retranslateUi(TopTen);
        QObject::connect(close, SIGNAL(clicked()), TopTen, SLOT(close()));

        QMetaObject::connectSlotsByName(TopTen);
    } // setupUi

    void retranslateUi(QDialog *TopTen)
    {
        TopTen->setWindowTitle(QApplication::translate("TopTen", "Top Ten Scores", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TopTen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt;\">Top Ten</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        topTenList->setText(QString());
        resetButton->setText(QApplication::translate("TopTen", "Reset Scores", 0, QApplication::UnicodeUTF8));
        close->setText(QApplication::translate("TopTen", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TopTen: public Ui_TopTen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPTEN_H
