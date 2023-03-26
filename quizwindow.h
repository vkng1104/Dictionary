#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QMainWindow>

namespace Ui {
class quizwindow;
}

class quizwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit quizwindow(QWidget *parent = nullptr);
    ~quizwindow();
    QString curAns;

public slots:
    void open();

private slots:
    void on_pushButton_clicked();

    void on_submitButton_clicked();

    void on_pushButtonA_clicked();

    void on_pushButtonB_clicked();

    void on_pushButtonC_clicked();

    void on_pushButtonD_clicked();

signals:
    void fav_Signal();

private:
    Ui::quizwindow *ui;
    bool isCorrect;
};

#endif // QUIZWINDOW_H
