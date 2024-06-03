#ifndef OFFICE_H
#define OFFICE_H

#include <QWidget>
#include<office_sa.h>

namespace Ui {
class office;
}

class office : public QWidget
{
    Q_OBJECT

public:
    explicit office(QWidget *parent = nullptr);
    ~office();
    void sqlconnect();
    void update1();

    office_sa *office_sa1=NULL;

signals:
    void back();

private slots:
    void on_modify_clicked();
    void comeBackTo();

    void on_search_clicked();

    void on_delete_2_clicked();

private:
    Ui::office *ui;
};

#endif // OFFICE_H
