#ifndef ADD_WINDOW_H
#define ADD_WINDOW_H

#include <QMainWindow>

namespace Ui {
class Add_window;
}

class Add_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Add_window(QWidget *parent = nullptr);
    ~Add_window();

private slots:
    void on_actionSearch_triggered();

    void on_actionQuiz_triggered();

    void on_editButton_clicked();

public slots:
    void open();

signals:
    void searchSignal();
    void quizSignal();

private:
    Ui::Add_window *ui;
};

#endif // ADD_WINDOW_H
