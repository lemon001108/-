#ifndef DOCT_H
#define DOCT_H

#include <QWidget>
#include <QProcess>
#include <QString>
#include<QSqlDatabase>


#include "doctor_sa.h"

namespace Ui {
class doct;
}

class doct : public QWidget
{
    Q_OBJECT

public:
    explicit doct(QWidget *parent = nullptr);
    ~doct();

    void sqlconnect();
    void update1();
    //void show_rec();
    doctor_sa *doctor_sa1=NULL;


signals:
    void back();

private slots:
    void on_modify_clicked();
    void comeBackTo();

    void on_search_clicked();

    void on_delete_2_clicked();

    void on_search_office_clicked();

private:
    Ui::doct *ui;
    int num;
};

#endif // DOCT_H
