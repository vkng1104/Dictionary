#include "history_window.h"
#include "ui_history_window.h"

history_window::history_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::history_window)
{
    ui->setupUi(this);
}

history_window::~history_window()
{
    delete ui;
}
