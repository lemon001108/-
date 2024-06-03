#ifndef NURSE_H
#define NURSE_H

#include <QWidget>
#include<nurse_sa.h>

namespace Ui {
class nurse;
}

class nurse : public QWidget
{
    Q_OBJECT

public:
    explicit nurse(QWidget *parent = nullptr);
    ~nurse();
    void sqlconnect();
    void update1();

    nurse_sa *nurse_sa1=NULL;


private slots:
    void on_modify_clicked();
    void comeBackTo();

    void on_search_clicked();

    void on_delete_2_clicked();

    void on_search_office_clicked();

signals:
    void back();

private:
    Ui::nurse *ui;
};

#endif // NURSE_H
