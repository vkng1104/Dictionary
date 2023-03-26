#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "search_window.h"
#include "quizwindow.h"
#include "add_window.h"
#include "hisfav.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void last_search();
    void addToFav();
    void addToFav2();
    void addToHis();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_favList_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_actionExit_triggered();

    void on_actionQuiz_triggered();

    void on_actionManage_triggered();

    void on_actionReset_triggered();

    void on_actionFavorite_list_triggered();

    void on_actionHistory_triggered();

signals:
    void favSignal();
    void hisSignal();

private:
    Ui::MainWindow *ui;
    search_window *searchWindow;
    quizwindow *quizWindow;
    Add_window *addWindow;
    HisFav *hisfav;
};
#endif // MAINWINDOW_H
