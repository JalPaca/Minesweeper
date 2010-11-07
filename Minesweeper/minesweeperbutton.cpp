#include "minesweeperbutton.h"
#include <QMouseEvent>
#include <QDebug>

MineSweeperButton::MineSweeperButton(QWidget *parent) : QPushButton()
{
}

MineSweeperButton::MineSweeperButton(QString blah) : QPushButton()
{
    qDebug() << "blah";
}

void MineSweeperButton::mousePressEvent(QMouseEvent *qMEvent) {

    if ( qMEvent->button() == Qt::RightButton ){
        emit rightButtonClicked();
    }
    QPushButton::mousePressEvent(qMEvent);
}
