#include "savescore.h"
#include "ui_savescore.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

SaveScore::SaveScore(int score, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveScore)
{
    ui->setupUi(this);
    this->score = score;
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

SaveScore::~SaveScore()
{
    delete ui;
}

void SaveScore::changeEvent(QEvent *e)
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

void SaveScore::save()
{
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE");

    db.setDatabaseName("scores.sqlite");

    if ( !db.open() )
    {
        qFatal("Failed to connect to database");
    }

    QSqlQuery sql;
    sql.prepare("INSERT INTO scores (name, score) VALUES (:name, :score)");
    sql.bindValue(":name", ui->name->text());
    sql.bindValue(":score", this->score);

    if ( !sql.exec( ) )
    {
        qFatal("Unable to select from database");
    }
    db.close();
    this->close();
}
