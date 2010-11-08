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
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetScores()));

    //Database info
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE", "connection");

    db.setDatabaseName("scores.sqlite");

    if ( !db.open() )
    {
        qFatal("Failed to connect to database");
    }

    getTopTenScores();
}

void TopTen::resetScores()
{
    QSqlDatabase db = QSqlDatabase::database("connection");

    QSqlQuery sql(db);

    sql.prepare("DELETE FROM scores");

    if ( !sql.exec() )
    {
        qFatal("Unable to truncate table from database");
    }

    getTopTenScores(); //Refresh view
}

void TopTen::getTopTenScores()
{
    QString topScores = "<ol>";

    QSqlDatabase db = QSqlDatabase::database("connection");

    QSqlQuery sql(db);

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
    QSqlDatabase::database("connection").close();
    QSqlDatabase::removeDatabase("connection");
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
