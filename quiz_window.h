#ifndef QUIZ_WINDOW_H
#define QUIZ_WINDOW_H

#include <QDialog>

namespace Ui {
class quiz_window;
}

class quiz_window : public QDialog
{
    Q_OBJECT

public:
    explicit quiz_window(QWidget *parent = nullptr);
    ~quiz_window();

private slots:
    void on_pushButton_clicked();

    void on_submitButton_clicked();

signals:
    void quiz_signal();
private:
    Ui::quiz_window *ui;
};

#endif // QUIZ_WINDOW_H
