#ifndef TOPTEN_H
#define TOPTEN_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
    class TopTen;
}

class TopTen : public QDialog {
    Q_OBJECT
public:
    TopTen(QWidget *parent = 0);
    ~TopTen();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TopTen *ui;
    void getTopTenScores();

private slots:
    void resetScores();

};

#endif // TOPTEN_H
