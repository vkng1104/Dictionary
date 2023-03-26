#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "data.h"
#include "function.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    searchWindow = new search_window(this);
    quizWindow = new quizwindow(this);
    addWindow = new Add_window(this);
    hisfav = new HisFav(this);

    hisfav->init();

    connect(searchWindow, &search_window::searchSignal, this, &MainWindow::last_search);
    connect(addWindow, &Add_window::searchSignal, searchWindow, &search_window::open);
    connect(searchWindow, &search_window::editSignal, addWindow, &Add_window::open);
    connect(addWindow, &Add_window::quizSignal, quizWindow, &quizwindow::open);
    connect(quizWindow, &quizwindow::fav_Signal, this, &MainWindow::addToFav);
    connect(searchWindow, &search_window::favSignal, this, &MainWindow::addToFav2);
    connect(this, &MainWindow::favSignal, hisfav, &HisFav::addToFav);
    connect(searchWindow, &search_window::searchSignal, this, &MainWindow::addToHis);
    connect(this, &MainWindow::hisSignal, hisfav, &HisFav::addToHis);

    std::pair<std::string, std::vector<std::string>> tmp = randomWord();
    ui->pushButton_6->setText(QString::fromStdString(tmp.first));
    qDebug() << QString::fromStdString(tmp.first) << "\n";

    tmp = randomWord();
    ui->pushButton_7->setText(QString::fromStdString(tmp.first));
    qDebug() << QString::fromStdString(tmp.first) << "\n";

    tmp = randomWord();
    ui->pushButton_8->setText(QString::fromStdString(tmp.first));
    qDebug() << QString::fromStdString(tmp.first) << "\n";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    searchWindow->show();
}

void MainWindow::on_pushButton_favList_clicked()
{
    hisfav->setTab(1);
    hisfav->show();
}

void MainWindow::on_actionFavorite_list_triggered()
{
    hisfav->setTab(1);
    hisfav->show();
}

void MainWindow::last_search()
{
    int r = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(r, 0, new QTableWidgetItem(searchWindow->lineEditText()));

    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss");
    ui->tableWidget->setItem(r, 1, new QTableWidgetItem(formattedTime));

    ui->tableWidget->adjustSize();
}


void MainWindow::on_pushButton_4_clicked() // View history
{
    hisfav->setTab(2);
    hisfav->show();
}

void MainWindow::on_actionHistory_triggered()
{
    hisfav->setTab(2);
    hisfav->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    quizWindow->show();
}

void MainWindow::on_actionQuiz_triggered()
{
    quizWindow->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    QApplication::quit();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->lineEdit->text().isEmpty()) return;
    searchWindow->quickSearch(ui->lineEdit->text());
    hisfav->cur = ui->lineEdit->text();
    emit hisSignal();

    // add to table widget
    int r = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(r, 0, new QTableWidgetItem(ui->lineEdit->text()));

    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss");
    ui->tableWidget->setItem(r, 1, new QTableWidgetItem(formattedTime));

    ui->tableWidget->adjustSize();

    searchWindow->show();
}


void MainWindow::on_pushButton_6_clicked()
{
    searchWindow->quickSearch(ui->pushButton_6->text());
    hisfav->cur = ui->pushButton_6->text();
    emit hisSignal();
    // add to table widget
    int r = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(r, 0, new QTableWidgetItem(ui->pushButton_6->text()));

    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss");
    ui->tableWidget->setItem(r, 1, new QTableWidgetItem(formattedTime));

    ui->tableWidget->adjustSize();

    // random a new word
    std::pair<std::string, std::vector<std::string>> tmp = randomWord();
    ui->pushButton_6->setText(QString::fromStdString(tmp.first));
    searchWindow->show();
}


void MainWindow::on_pushButton_7_clicked()
{
    searchWindow->quickSearch(ui->pushButton_7->text());
    hisfav->cur = ui->pushButton_7->text();
    emit hisSignal();
    // add to table widget
    int r = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(r, 0, new QTableWidgetItem(ui->pushButton_7->text()));

    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss");
    ui->tableWidget->setItem(r, 1, new QTableWidgetItem(formattedTime));

    ui->tableWidget->adjustSize();

    std::pair<std::string, std::vector<std::string>> tmp = randomWord();
    ui->pushButton_7->setText(QString::fromStdString(tmp.first));
    searchWindow->show();
}


void MainWindow::on_pushButton_8_clicked()
{
    searchWindow->quickSearch(ui->pushButton_8->text());
    hisfav->cur = ui->pushButton_8->text();
    emit hisSignal();
    // add to table widget
    int r = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(r, 0, new QTableWidgetItem(ui->pushButton_8->text()));

    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss");
    ui->tableWidget->setItem(r, 1, new QTableWidgetItem(formattedTime));

    ui->tableWidget->adjustSize();

    std::pair<std::string, std::vector<std::string>> tmp = randomWord();
    ui->pushButton_8->setText(QString::fromStdString(tmp.first));
    searchWindow->show();
}

void MainWindow::on_actionManage_triggered()
{
    addWindow->show();
}


void MainWindow::on_actionReset_triggered()
{
    resetData(); // data.cpp
    QMessageBox mb(this);
    QPixmap pm(":/img/img/yes.png");
    mb.setWindowIcon(QIcon(pm));
    mb.setWindowTitle("Reset the dictionary");
    mb.setText("Successfully reset! All of your changes to our dictionary were removed!");
    mb.adjustSize();
    mb.exec();
}

void MainWindow::addToFav()
{
    hisfav->cur = quizWindow->curAns;
    qDebug() << hisfav->cur << '\n';
    emit favSignal();
}

void MainWindow::addToFav2()
{
    hisfav->cur = searchWindow->lineEditText();
    qDebug() << hisfav->cur << '\n';
    emit favSignal();
}

void MainWindow::addToHis()
{
    hisfav->cur = searchWindow->lineEditText();
    qDebug() << hisfav->cur << '\n';
    emit hisSignal();
}
