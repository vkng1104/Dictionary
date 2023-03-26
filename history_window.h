#ifndef HISTORY_WINDOW_H
#define HISTORY_WINDOW_H

#include <QMainWindow>

namespace Ui {
class history_window;
}

class history_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit history_window(QWidget *parent = nullptr);
    ~history_window();

private:
    Ui::history_window *ui;
};

#endif // HISTORY_WINDOW_H
