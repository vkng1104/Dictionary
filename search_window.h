#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include <QMainWindow>

namespace Ui {
class search_window;
}

class search_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit search_window(QWidget *parent = nullptr);
    QString lineEditText();
    void quickSearch(QString qs);
    ~search_window();

public slots:
    void open();

private slots:
    void on_pushButton_clicked();
    void on_actionReset_triggered();

    void on_actionAdd_triggered();

    void on_actionEdit_triggered();

signals:
    void searchSignal();
    void editSignal();
    void favSignal();

private:
    Ui::search_window *ui;
};

#endif // SEARCH_WINDOW_H
