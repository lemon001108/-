#ifndef PRIMARY_H
#define PRIMARY_H

#include <QWidget>
#include<QDebug>
#include<QPushButton>

#include "govern.h"
#include "doct.h"
#include "patience.h"
#include "nurse.h"
#include "office.h"
#include "medicine.h"

class doct;
class office;
class patience;
class nurse;
class medicine;

namespace Ui {
class primary;
}

class primary : public QWidget
{
    Q_OBJECT

public:
    explicit primary(QWidget *parent = nullptr);
    ~primary();
    doct *doctor1;
    office *office1;
    patience *patience1;
    nurse *nurse1;
    medicine *medicine1;
    void initPage();
    void dealMenu();


private slots:

    void on_back_clicked();

    /*void doctorcomeBackTo();
    void officecomeBackTo();
    void nursecomeBackTo();
    void patiencecomeBackTo();
    void medicinecomeBackTo();

    void on_office_clicked();

    void on_nurse_clicked();

    void on_patience_clicked();
    void on_medicine_clicked();*/
    //void switchPage();


    //void on_stackedWidget_currentChanged(int arg1);

    //void on_doctor_btn_clicked();

signals:
    void back();

private:
    Ui::primary *ui;

};

#endif // PRIMARY_H
