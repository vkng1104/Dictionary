#include "quizwindow.h"
#include "ui_quizwindow.h"
#include "function.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QPushButton>
#include "ui_hisfav.h"

quizwindow::quizwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::quizwindow)
{
    isCorrect = false;
    curAns = "";
    ui->setupUi(this);
    this->setFixedSize(1000,600);
}

quizwindow::~quizwindow()
{
    delete ui;
}

void quizwindow::open()
{
    this->show();
}

void quizwindow::on_pushButton_clicked()
{
    if(!ui->radioButtonDef->isChecked() and !ui->radioButtonWord->isChecked())
        QMessageBox::warning(this, "Something is missing", "Please choose a mode!");
    else if(!ui->radioButtonEng->isChecked() and !ui->radioButtonViet->isChecked())
        QMessageBox::warning(this, "Something is missing", "Please choose a language!");
    else
    {
        isCorrect = false;
        bool fl1 = false;
        if(ui->radioButtonDef->isChecked()) fl1 = true;

        bool fl2 = false;
        if(ui->radioButtonViet->isChecked()) fl2 = true;

        std::vector<std::pair<std::string, std::vector<std::string>>> words = create_quiz(fl1, fl2);
        std::ofstream fout("quizzes.txt");

        if(!fl1) // word
        {
            int x = rand();
            QString ques = QString::fromStdString(words[x % 4].first);
            ui->plainTextEdit->setPlainText(ques);

            if(!fl2) // eng
            {
                QString qs = "";
                qs = "A. " + QString::fromStdString(words[0].second[0]);
                ui->pteA->setPlainText(qs);
                // ui->buttonA->adjustSize();
                qs = "B. " + QString::fromStdString(words[1].second[0]);
                ui->pteB->setPlainText(qs);
                //ui->buttonB->adjustSize();
                qs = "C. " + QString::fromStdString(words[2].second[0]);
                ui->pteC->setPlainText(qs);
                //ui->buttonC->adjustSize();
                qs = "D. " + QString::fromStdString(words[3].second[0]);
                ui->pteD->setPlainText(qs);
                //ui->buttonD->adjustSize();
                fout << words[x % 4].second[0] << std::endl;
            }
            else // viet
            {
                QString qs = "";
                qs = "A. " + QString::fromStdString(words[0].second[1]);
                ui->pteA->setPlainText(qs);
                qs = "B. " + QString::fromStdString(words[1].second[1]);
                ui->pteB->setPlainText(qs);
                qs = "C. " + QString::fromStdString(words[2].second[1]);
                ui->pteC->setPlainText(qs);
                qs = "D. " + QString::fromStdString(words[3].second[1]);
                ui->pteD->setPlainText(qs);
                fout << words[x % 4].second[1] << std::endl;
            }
        }
        else // definition
        {
            int x = rand();
            if(!fl2) // eng
            {
                QString ques = QString::fromStdString(words[x % 4].second[0]);
                ui->plainTextEdit->setPlainText(ques);
            }
            else // viet
            {
                QString ques = QString::fromStdString(words[x % 4].second[1]);
                ui->plainTextEdit->setPlainText(ques);
            }

            fout << words[x % 4].first << std::endl; // save answer to file

            QString qs = "";
            qs = "A. " + QString::fromStdString(words[0].first);
            ui->pteA->setPlainText(qs);
            qs = "B. " + QString::fromStdString(words[1].first);
            ui->pteB->setPlainText(qs);
            qs = "C. " + QString::fromStdString(words[2].first);
            ui->pteC->setPlainText(qs);
            qs = "D. " + QString::fromStdString(words[3].first);
            ui->pteD->setPlainText(qs);
        }

        fout.close();
    }
}


void quizwindow::on_submitButton_clicked()
{
    if(!ui->buttonA->isChecked() and !ui->buttonB->isChecked() and
       !ui->buttonC->isChecked() and !ui->buttonD->isChecked())
        QMessageBox::warning(this, "Something is missing", "Please choose an answer!");
    else
    {
        QString users_answer = "";
        if(ui->buttonA->isChecked())
            users_answer = ui->pteA->toPlainText();
        if(ui->buttonB->isChecked())
            users_answer = ui->pteB->toPlainText();
        if(ui->buttonC->isChecked())
            users_answer = ui->pteC->toPlainText();
        if(ui->buttonD->isChecked())
            users_answer = ui->pteD->toPlainText();

        std::string utf8_text = users_answer.toUtf8().constData();
        utf8_text = std::string(utf8_text.begin() + 3, utf8_text.end());
        users_answer = QString::fromStdString(utf8_text);

        QFile file("quizzes.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, "Can't find the answer", "Answer is missing!");
            return;
        }
        QTextStream in(&file);
        QString answer = in.readLine();
        qDebug() << answer << " " << users_answer << "\n";

        if(answer == users_answer)
        {
            isCorrect = true;
            QMessageBox mb(this);
            QPixmap pm(":/img/img/yes.png");
            // mb.setIconPixmap(pm);
            mb.setWindowIcon(QIcon(pm));
            mb.setWindowTitle("Congratulations!!!!!!!!");
            mb.setText("That was a CORRECT answer. Good job my friend!");
            mb.adjustSize();
            mb.exec();
            // QMessageBox::critical(this, "Congratulations!!!!!!!!", "That was a CORRECT answer. Good job my friend!");
        }
        else
        {
            isCorrect = false;
            QMessageBox mb(this);
            QPixmap pm(":/img/img/no.png");
            // mb.setIconPixmap(pm);
            mb.setWindowIcon(QIcon(pm));
            mb.setWindowTitle("Noooooooooooooo!!!!!!!!");
            mb.setText("That was a WRONG answer. Poor my friend!");
            mb.adjustSize();
            mb.exec();
            // QMessageBox::critical(this, "Congratulations!!!!!!!!", "That was a correct answer. Good job my friend!");
        }
    }
}

void quizwindow::on_pushButtonA_clicked()
{
    if(!ui->radioButtonDef->isChecked())
        QMessageBox::critical(this, "Something is wrong!!!!!!!!", "That was NOT a word to be added");
    else
    {
        curAns = ui->pteA->toPlainText();
        std::string utf8_text = curAns.toUtf8().constData();
        utf8_text = std::string(utf8_text.begin() + 3, utf8_text.end());
        curAns = QString::fromStdString(utf8_text);
        emit fav_Signal();
        qDebug() << curAns << '\n';
    }
}

void quizwindow::on_pushButtonB_clicked()
{
    if(!ui->radioButtonDef->isChecked())
        QMessageBox::critical(this, "Something is wrong!!!!!!!!", "That was NOT a word to be added");
    else
    {
        curAns = ui->pteB->toPlainText();
        std::string utf8_text = curAns.toUtf8().constData();
        utf8_text = std::string(utf8_text.begin() + 3, utf8_text.end());
        curAns = QString::fromStdString(utf8_text);
        emit fav_Signal();
        qDebug() << curAns << '\n';
    }
}

void quizwindow::on_pushButtonC_clicked()
{
    if(!ui->radioButtonDef->isChecked())
        QMessageBox::critical(this, "Something is wrong!!!!!!!!", "That was NOT a word to be added");
    else
    {
        curAns = ui->pteC->toPlainText();
        std::string utf8_text = curAns.toUtf8().constData();
        utf8_text = std::string(utf8_text.begin() + 3, utf8_text.end());
        curAns = QString::fromStdString(utf8_text);
        emit fav_Signal();
        qDebug() << curAns << '\n';
    }
}


void quizwindow::on_pushButtonD_clicked()
{
    if(!ui->radioButtonDef->isChecked())
        QMessageBox::critical(this, "Something is wrong!!!!!!!!", "That was NOT a word to be added");
    else
    {
        curAns = ui->pteD->toPlainText();
        std::string utf8_text = curAns.toUtf8().constData();
        utf8_text = std::string(utf8_text.begin() + 3, utf8_text.end());
        curAns = QString::fromStdString(utf8_text);
        emit fav_Signal();
        qDebug() << curAns << '\n';
    }
}

