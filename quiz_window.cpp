#include "quiz_window.h"
#include "ui_quiz_window.h"
#include "function.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

quiz_window::quiz_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quiz_window)
{
    ui->setupUi(this);
}

quiz_window::~quiz_window()
{
    delete ui;
}

void quiz_window::on_pushButton_clicked()
{
    if(!ui->radioButtonDef->isChecked() and !ui->radioButtonWord->isChecked())
        QMessageBox::warning(this, "Something is missing", "Please choose a mode!");
    else if(!ui->radioButtonEng->isChecked() and !ui->radioButtonViet->isChecked())
        QMessageBox::warning(this, "Something is missing", "Please choose a language!");
    else
    {
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
                ui->buttonA->setText(qs);
                ui->buttonA->adjustSize();
                qs = "B. " + QString::fromStdString(words[1].second[0]);
                ui->buttonB->setText(qs);
                ui->buttonB->adjustSize();
                qs = "C. " + QString::fromStdString(words[2].second[0]);
                ui->buttonC->setText(qs);
                ui->buttonC->adjustSize();
                qs = "D. " + QString::fromStdString(words[3].second[0]);
                ui->buttonD->setText(qs);
                ui->buttonD->adjustSize();
                fout << words[x % 4].second[0] << std::endl;
            }
            else // viet
            {
                QString qs = "";
                qs = "A. " + QString::fromStdString(words[0].second[1]);
                ui->buttonA->setText(qs);
                qs = "B. " + QString::fromStdString(words[1].second[1]);
                ui->buttonB->setText(qs);
                qs = "C. " + QString::fromStdString(words[2].second[1]);
                ui->buttonC->setText(qs);
                qs = "D. " + QString::fromStdString(words[3].second[1]);
                ui->buttonD->setText(qs);
                fout << words[x % 4].second[1] << std::endl;
            }
        }
        else
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
            ui->buttonA->setText(qs);
            qs = "B. " + QString::fromStdString(words[1].first);
            ui->buttonB->setText(qs);
            qs = "C. " + QString::fromStdString(words[2].first);
            ui->buttonC->setText(qs);
            qs = "D. " + QString::fromStdString(words[3].first);
            ui->buttonD->setText(qs);
        }

        fout.close();
    }
}


void quiz_window::on_submitButton_clicked()
{
    if(!ui->buttonA->isChecked() and !ui->buttonB->isChecked() and
       !ui->buttonC->isChecked() and !ui->buttonD->isChecked())
        QMessageBox::warning(this, "Something is missing", "Please choose an answer!");
    else
    {
        QString users_answer = "";
        if(ui->buttonA->isChecked())
            users_answer = ui->buttonA->text();
        if(ui->buttonB->isChecked())
            users_answer = ui->buttonB->text();
        if(ui->buttonC->isChecked())
            users_answer = ui->buttonC->text();
        if(ui->buttonD->isChecked())
            users_answer = ui->buttonD->text();

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

