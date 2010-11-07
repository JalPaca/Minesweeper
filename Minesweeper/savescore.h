#ifndef SAVESCORE_H
#define SAVESCORE_H

#include <QDialog>

namespace Ui {
    class SaveScore;
}

class SaveScore : public QDialog {
    Q_OBJECT
public:
    SaveScore(int, QWidget *parent = 0);
    ~SaveScore();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SaveScore *ui;
    int score;

private slots:
        void save();
};

#endif // SAVESCORE_H
