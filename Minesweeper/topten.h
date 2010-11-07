#ifndef TOPTEN_H
#define TOPTEN_H

#include <QDialog>

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
};

#endif // TOPTEN_H
