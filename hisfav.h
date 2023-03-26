#ifndef HISFAV_H
#define HISFAV_H

#include <QDialog>

namespace Ui {
class HisFav;
}

class HisFav : public QDialog
{
    Q_OBJECT

public:
    explicit HisFav(QWidget *parent = nullptr);
    ~HisFav();
    void setTab(int);
    QString cur;
    void init();

public slots:
    void addToFav();
    void addToHis();

private:
    Ui::HisFav *ui;
};

#endif // HISFAV_H
