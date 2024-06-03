#ifndef MEDICINE_H
#define MEDICINE_H

#include <QWidget>

#include<medicine_sa.h>

namespace Ui {
class medicine;
}

class medicine : public QWidget
{
    Q_OBJECT

public:
    explicit medicine(QWidget *parent = nullptr);
    ~medicine();
    void sqlconnect();
    void update1();

    medicine_sa *medicine_sa1=NULL;

signals:
    void back();

private slots:
    void on_search_clicked();

    void on_delete_2_clicked();

    void on_modify_clicked();

    void comeBackTo();

private:
    Ui::medicine *ui;
};

#endif // MEDICINE_H
