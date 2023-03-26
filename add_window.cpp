#include "add_window.h"
#include "ui_add_window.h"
#include <QMessageBox>
#include "config.h"
#include "function.h"
#include <iostream>

Add_window::Add_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Add_window)
{
    ui->setupUi(this);
}

Add_window::~Add_window()
{
    delete ui;
}

void Add_window::open(){ this->show(); }

void Add_window::on_actionSearch_triggered()
{
    emit searchSignal();
}


void Add_window::on_actionQuiz_triggered()
{
    emit quizSignal();
}


void Add_window::on_editButton_clicked()
{
    bool flag1[3];
    flag1[0] = ui->RB_Add->isChecked();
    flag1[1] = ui->RB_Edit->isChecked();
    flag1[2] = ui->RB_Remove->isChecked();

    bool checking = flag1[0] + flag1[1] + flag1[2];
    if(!checking)
    {
        QMessageBox::warning(this, "Something is missing", "Please choose a mode (Add/Edit/Remove)!");
        return;
    }

    bool flag2[2];
    flag2[0] = ui->radioButton_word->isChecked();
    flag2[1] = ui->radioButton_SlangEmo->isChecked();

    checking = flag2[0] + flag2[1];
    if(!checking)
    {
        QMessageBox::warning(this, "Something is missing", "Please choose a type of your word");
        return;
    }

    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Something is missing", "Please input the word you want to manage");
        return;
    }

    if(ui->plainTextEdit->toPlainText().isEmpty() and ui->plainTextEdit_2->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Something is missing", "Please input the definition");
        return;
    }

    QString qs[3];
    std::string utf8_text[3];
    qs[0] = ui->lineEdit->text();
    utf8_text[0] = qs[0].toUtf8().constData();

    qs[1] = ui->plainTextEdit->toPlainText();
    utf8_text[1] = qs[1].toUtf8().constData();

    qs[2] = ui->plainTextEdit_2->toPlainText();
    utf8_text[2] = qs[2].toUtf8().constData();

    std::string sub;
    sub.push_back(char(92));
    sub.push_back('n');

    std::cout << utf8_text[1] << " " << utf8_text[2] << '\n';

    if(flag2[0])
    {
        // check if input is a proper word
        if(!isWord(utf8_text[0]))
        {
            QMessageBox::warning(this, "Something is NOT correct", "Please rewrite your input correctly");
            return;
        }

        if(flag1[0]) // add a word
        {
            if (!ui->plainTextEdit->toPlainText().isEmpty() && !ui->plainTextEdit_2->toPlainText().isEmpty())
            {
                if (!config::tries.check_and_add(utf8_text[0], utf8_text[1] + sub, "", "English"))
                {
                    QMessageBox::warning(this, "Something is NOT correct", "We already have this word in our dictionary!\nChoose edit if you want to change the definition!");
                    return;
                }
                config::tries.edit(utf8_text[0], utf8_text[2] + sub, "", "Viet");
                QMessageBox mb(this);
                QPixmap pm(":/img/img/yes.png");
                mb.setWindowIcon(QIcon(pm));
                mb.setWindowTitle("Add a new word");
                mb.setText("Successfully add this word to our dictionary");
                mb.adjustSize();
                mb.exec();
            }
            else if (!ui->plainTextEdit_2->toPlainText().isEmpty())
            {
                if (!config::tries.check_and_add(utf8_text[0], utf8_text[2] + sub, "", "Viet"))
                {
                    QMessageBox::warning(this, "Something is NOT correct", "We already have this word in our dictionary!\nChoose edit if you want to change the definition!");
                    return;
                }
                QMessageBox mb(this);
                QPixmap pm(":/img/img/yes.png");
                mb.setWindowIcon(QIcon(pm));
                mb.setWindowTitle("Add a new word");
                mb.setText("Successfully add this word to our dictionary");
                mb.adjustSize();
                mb.exec();
            }
            else
            {
                if (!config::tries.check_and_add(utf8_text[0], utf8_text[1] + sub, "", "English"))
                {
                    QMessageBox::warning(this, "Something is NOT correct", "We already have this word in our dictionary!\nChoose edit if you want to change the definition!");
                    return;
                }
                QMessageBox mb(this);
                QPixmap pm(":/img/img/yes.png");
                mb.setWindowIcon(QIcon(pm));
                mb.setWindowTitle("Add a new word");
                mb.setText("Successfully add this word to our dictionary");
                mb.adjustSize();
                mb.exec();
            }
        }
        else if(flag1[1]) // edit a defintion
        {
            QString qs;
            if(!ui->plainTextEdit->toPlainText().isEmpty())
                qs = QString::fromStdString(config::tries.edit(utf8_text[0], utf8_text[1] + sub, "", "English"));
            if(!ui->plainTextEdit_2->toPlainText().isEmpty())
                qs = QString::fromStdString(config::tries.edit(utf8_text[0], utf8_text[2] + sub, "", "Viet"));
            if(qs != "Something is wrong, this word does NOT exist in our dictionary!")
            {
                QMessageBox mb(this);
                QPixmap pm(":/img/img/yes.png");
                mb.setWindowIcon(QIcon(pm));
                mb.setWindowTitle("Edit a word");
                mb.setText(qs);
                mb.adjustSize();
                mb.exec();
            }
            else QMessageBox::warning(this, "Something is NOT correct", qs);
        }
        else // remove a word
        {
            QString qs = QString::fromStdString(config::tries.remove(utf8_text[0]));
            if(qs == "Successfully remove the word")
            {
                QMessageBox mb(this);
                QPixmap pm(":/img/img/yes.png");
                mb.setWindowIcon(QIcon(pm));
                mb.setWindowTitle("Remove a word");
                mb.setText(qs);
                mb.adjustSize();
                mb.exec();
            }
            else QMessageBox::warning(this, "Something is NOT correct", qs);
        }
    }
    else // slang or emo
    {
        if(flag1[0]) // add a word
        {
            string def = "";
            if(!ui->plainTextEdit->toPlainText().isEmpty())
                def = utf8_text[1];
            if(!ui->plainTextEdit_2->toPlainText().isEmpty())
            {
                if(def != "")
                    def += '/' + utf8_text[2];
                else def = utf8_text[2];
            }

            add(config::active, config::root, utf8_text[0], def);
            QMessageBox mb(this);
            QPixmap pm(":/img/img/yes.png");
            mb.setWindowIcon(QIcon(pm));
            mb.setWindowTitle("Add a new word");
            mb.setText("Successfully add this word to our dictionary");
            mb.adjustSize();
            mb.exec();
        }
        else if(flag1[1]) // edit a defintion
        {
            string def = "";
            if(!ui->plainTextEdit->toPlainText().isEmpty())
                def = utf8_text[1];
            if(!ui->plainTextEdit_2->toPlainText().isEmpty())
            {
                if(def != "")
                    def += '/' + utf8_text[2];
                else def = utf8_text[2];
            }

            add(config::active, config::root, utf8_text[0], def);
            QMessageBox mb(this);
            QPixmap pm(":/img/img/yes.png");
            mb.setWindowIcon(QIcon(pm));
            mb.setWindowTitle("Edit a word");
            mb.setText("Successfully edit this word");
            mb.adjustSize();
            mb.exec();
        }
        else // remove a word
        {
            delWord(config::root, utf8_text[0], config::active);
            QMessageBox mb(this);
            QPixmap pm(":/img/img/yes.png");
            mb.setWindowIcon(QIcon(pm));
            mb.setWindowTitle("Remove a word");
            mb.setText("Successfully remove this word");
            mb.adjustSize();
            mb.exec();
        }
    }
}

