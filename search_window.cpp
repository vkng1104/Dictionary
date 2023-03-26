#include "search_window.h"
#include "ui_search_window.h"
#include "function.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

search_window::search_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::search_window)
{
    ui->setupUi(this);
}

search_window::~search_window()
{
    delete ui;
}

void search_window::on_pushButton_clicked()
{
    ui->listWidget->clear();
    QString qs = ui->lineSearch->text();
    std::string utf8_text = qs.toUtf8().constData();
    if(ui->radioButton_word->isChecked())
    {
        bool fl2 = ui->checkBox_Eng->isChecked();
        bool fl1 = ui->checkBox_Viet->isChecked();

        if(!isWord(utf8_text))
        {
            QMessageBox::warning(this, "Something is NOT correct", "Please rewrite your input correctly");
            return;
        }

        if(fl1 or fl2)
        {
            std::vector<std::string> ans = search(1, utf8_text, fl1, fl2);
            for(int i = 0; i < ans.size(); i++) ui->listWidget->addItem(QString::fromStdString(ans[i]));
            if(!ui->lineSearch->text().isEmpty()) emit searchSignal();
        }
        else
            ui->listWidget->addItem("Please choose a language!");
    }
    else if(ui->radioButton_def->isChecked())
    {
        // search(2, ui, utf8_text, true, true);
        std::vector<std::string> ans = search(2, utf8_text, true, true);
        for(int i = 0; i < ans.size(); i++) ui->listWidget->addItem(QString::fromStdString(ans[i]));
        if(!ui->lineSearch->text().isEmpty()) emit searchSignal();
    }
    else if(ui->radioButton_SlangEmo->isChecked())
    {
        std::vector<std::string> ans = search(3, utf8_text, true, true);
        for(int i = 0; i < ans.size(); i++) ui->listWidget->addItem(QString::fromStdString(ans[i]));
        if(!ui->lineSearch->text().isEmpty()) emit searchSignal();
    }
    else
        ui->listWidget->addItem("Please choose a word or a definition!");
}

QString search_window::lineEditText()
{
    return ui->lineSearch->text();
}

void search_window::quickSearch(QString qs)
{
    ui->listWidget->clear();
    ui->lineSearch->setText(qs);
    ui->checkBox_Eng->setChecked(true);
    ui->checkBox_Viet->setChecked(true);
    ui->radioButton_word->setChecked(true);
    std::string utf8_text = qs.toUtf8().constData();
    // search(1, ui, utf8_text, true, true);
    std::vector<std::string> ans = search(1, utf8_text, true, true);
    for(int i = 0; i < ans.size(); i++) ui->listWidget->addItem(QString::fromStdString(ans[i]));
}

void search_window::on_actionReset_triggered()
{
    ui->listWidget->clear();
    ui->lineSearch->clear();
    ui->checkBox_Eng->setChecked(false);
    ui->checkBox_Viet->setChecked(false);
    ui->radioButton_word->setChecked(false);
    ui->radioButton_def->setChecked(false);
}

void search_window::on_actionAdd_triggered()
{
    // ADD TO FAV LIST
    if(!ui->lineSearch->text().isEmpty() && ui->radioButton_word->isChecked())
    {
        QString qs = ui->lineSearch->text();
        std::string utf8_text = qs.toUtf8().constData();
        if(!isWord(utf8_text))
        {
            QMessageBox::warning(this, "Something is NOT correct", "Please rewrite your input correctly");
            return;
        }

        QMessageBox mb(this);
        QPixmap pm(":/img/img/yes.png");
        // mb.setIconPixmap(pm);
        mb.setWindowIcon(QIcon(pm));
        mb.setWindowTitle("Add to your favorite list");
        mb.setText("That was a good way to review it later my friend!");
        mb.adjustSize();
        mb.exec();
        emit favSignal();
    }
    else
        QMessageBox::warning(this, "Something is NOT correct", "Please input your word or choose the WORD mode");
}

void search_window::open()
{
    this->show();
}


void search_window::on_actionEdit_triggered()
{
    emit editSignal();
}

