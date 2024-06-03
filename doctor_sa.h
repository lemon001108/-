#ifndef DOCTOR_SA_H
#define DOCTOR_SA_H

#include <QWidget>
#include "ui_doct.h"

struct doctor
{
    QString id;
    QString office_id;
    QString name;
    QString gender;
    QString age;
    QString phone;
    QString stage;
};

namespace Ui {
class doctor_sa;
}

class doctor_sa : public QWidget
{
    Q_OBJECT

public:
    explicit doctor_sa(QWidget *parent = nullptr);
    ~doctor_sa();
    void sqlconnect();


private slots:

    void on_add_clicked();

    void on_modify_clicked();

    void on_b_clicked();

signals:
    void back();

private:
    Ui::doctor_sa *ui;
};

#endif // DOCTOR_SA_H
