#include "topten.h"
#include <QFile>
#include <QDebug>
#include "ui_topten.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

TopTen::TopTen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopTen)
{
    ui->setupUi(this);

    getTopTenScores();
}

void TopTen::getTopTenScores()
{
    QString topScores = "<ol>";
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE");

    db.setDatabaseName("scores.sqlite");

    if ( !db.open() )
    {
        qFatal("Failed to connect to database");
    }

    QSqlQuery sql;
    sql.prepare("SELECT name, score FROM scores ORDER BY score ASC LIMIT 10");

    if ( !sql.exec() )
    {
        qFatal("Unable to select from database");
    }

    QSqlRecord record = sql.record();

    for( int r=0; sql.next(); r++ )
              topScores += "<li>" + sql.value(0).toString() + " - " + sql.value(1).toString() +"</li>";

    topScores += "</ol>";
    ui->topTenList->setText(topScores);
}


TopTen::~TopTen()
{
    delete ui;
}

void TopTen::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
