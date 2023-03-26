#include "hisfav.h"
#include "ui_hisfav.h"
#include <QTime>
#include <QDate>
#include <iostream>
#include <fstream>
#include "data.h"
#include "algorithm.h"
#include <QPushButton>

HisFav::HisFav(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HisFav)
{
    ui->setupUi(this);
    cur = "";
}

HisFav::~HisFav()
{
    delete ui;
}

void HisFav::setTab(int x)
{
    if(x == 1) // favorite list
        ui->tabWidget->setCurrentWidget(ui->tab_fav);
    else
        ui->tabWidget->setCurrentWidget(ui->tab_his);
}

void HisFav::addToFav()
{
    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss");

    QDate date = QDate::currentDate();
    QString formattedDate = date.toString("dd/MM/yyyy");

    QPushButton *btn1 = new QPushButton();
    btn1->setText("Remove");

    std::string file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/fav.txt";
    qDebug() << cur << "Hello\n";
    if(isEmpty_file(file))
    {
        qDebug() << "First\n";
        // add to table widget
        int r = ui->tableWidget_4->rowCount();
        ui->tableWidget_4->insertRow(ui->tableWidget_3->rowCount());
        ui->tableWidget_4->setItem(r, 0, new QTableWidgetItem(cur));
        ui->tableWidget_4->setItem(r, 1, new QTableWidgetItem(formattedTime));
        ui->tableWidget_4->setItem(r, 2, new QTableWidgetItem(formattedDate));
        ui->tableWidget_4->adjustSize();

        std::fstream fout1, fout2;
        fout1.open(file, std::ios::app);
        fout1 << cur.toUtf8().constData() << "#$#" << formattedTime.toUtf8().constData()
             << "#$#" << formattedDate.toUtf8().constData() << '\n';
        fout1.close();

        std::string file2 = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/favCheck.txt"; // used to check if a word occurs twice in fav list
        fout2.open(file2, std::ios::app);
        fout2 << cur.toUtf8().constData() << "#$#" << formattedTime.toUtf8().constData()
             << "#$#" << formattedDate.toUtf8().constData() << "#$#";
        fout2.close();
    }
    else
    {
        qDebug() << "Second\n";
        file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/favCheck.txt";
        std::string tmp = "";
        std::fstream fin;
        fin.open(file, std::ios::in);
        fin >> tmp;
        cout << tmp << '\n';
        fin.close();

        std::vector<int> idx = KMP_search(tmp, cur.toUtf8().constData(), kmp_preprocess(cur.toUtf8().constData()));
        if(!idx.empty()) return; // already have this word

        int r = ui->tableWidget_4->rowCount();
        ui->tableWidget_4->insertRow(ui->tableWidget_4->rowCount());
        ui->tableWidget_4->setItem(r, 0, new QTableWidgetItem(cur));
        ui->tableWidget_4->setItem(r, 1, new QTableWidgetItem(formattedTime));
        ui->tableWidget_4->setItem(r, 2, new QTableWidgetItem(formattedDate));
        ui->tableWidget_4->adjustSize();

        std::fstream fout1, fout2;
        fout1.open(file, std::ios::app);
        fout1 << cur.toUtf8().constData() << "#$#" << formattedTime.toUtf8().constData()
             << "#$#" << formattedDate.toUtf8().constData() << "#$#";
        fout1.close();

        std::string file2 = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/fav.txt";
        fout2.open(file2, std::ios::app);
        fout2 << cur.toUtf8().constData() << "#$#" << formattedTime.toUtf8().constData()
             << "#$#" << formattedDate.toUtf8().constData() << '\n';
        fout2.close();
    }

}

void HisFav::addToHis()
{
    qDebug() << cur << '\n';
    // add to table widget
    int r = ui->tableWidget_3->rowCount();
    ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
    ui->tableWidget_3->setItem(r, 0, new QTableWidgetItem(cur));

    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss");
    ui->tableWidget_3->setItem(r, 1, new QTableWidgetItem(formattedTime));

    QDate date = QDate::currentDate();
    QString formattedDate = date.toString("dd/MM/yyyy");
    ui->tableWidget_3->setItem(r, 2, new QTableWidgetItem(formattedDate));

    ui->tableWidget_3->adjustSize();

    std::string file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/his.txt";
    std::fstream fout;
    fout.open(file, std::ios::app);
    fout << cur.toUtf8().constData() << "#$#" << formattedTime.toUtf8().constData()
         << "#$#" << formattedDate.toUtf8().constData() << '\n';
    fout.close();
}

void HisFav::init()
{
    std::string file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/fav.txt";
    if(!isEmpty_file(file))
    {
        std::ifstream fin(file);
        std::string s = "";
        while(fin >> s)
        {
            QPushButton *btn1 = new QPushButton();
            btn1->setText("Remove");

            std::vector<int> index = KMP_search(s, "#$#", kmp_preprocess("#$#"));
            string tmp[3];
            tmp[0] = string(s.begin(), s.begin() + index[0]);
            cout << tmp[0] << '\n';
            tmp[1] = string(s.begin() + index[0] + 3, s.begin() + index[1]);
            tmp[2] = string(s.begin() + index[1] + 3, s.end());

            int r = ui->tableWidget_4->rowCount();
            ui->tableWidget_4->insertRow(ui->tableWidget_4->rowCount());
            ui->tableWidget_4->setItem(r, 0, new QTableWidgetItem(QString::fromStdString(tmp[0])));
            ui->tableWidget_4->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(tmp[1])));
            ui->tableWidget_4->setItem(r, 2, new QTableWidgetItem(QString::fromStdString(tmp[2])));
            ui->tableWidget_4->adjustSize();
        }
    }

    file = "C:/Users/ASUS/OneDrive - xhbnm/Documents/CS163/his.txt";
    if(!isEmpty_file(file))
    {
        std::ifstream fin(file);
        std::string s = "";
        while(getline(fin,s))
        {
            std::vector<int> index = KMP_search(s, "#$#", kmp_preprocess("#$#"));
            string tmp[3];
            tmp[0] = string(s.begin(), s.begin() + index[0]);
            tmp[1] = string(s.begin() + index[0] + 3, s.begin() + index[1]);
            tmp[2] = string(s.begin() + index[1] + 3, s.end());
            cout << tmp[0] << '\n';

            int r = ui->tableWidget_3->rowCount();
            ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
            ui->tableWidget_3->setItem(r, 0, new QTableWidgetItem(QString::fromStdString(tmp[0])));
            ui->tableWidget_3->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(tmp[1])));
            ui->tableWidget_3->setItem(r, 2, new QTableWidgetItem(QString::fromStdString(tmp[2])));
            ui->tableWidget_3->adjustSize();
        }
    }
}
