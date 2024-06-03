#ifndef PATIENCE_H
#define PATIENCE_H

#include <QWidget>
#include<patience_sa.h>

namespace Ui {
class patience;
}

class patience : public QWidget
{
    Q_OBJECT

public:
    explicit patience(QWidget *parent = nullptr);
    ~patience();
    void sqlconnect();
    void update1();

    patience_sa *patience_sa1=NULL;

signals:
    void back();

private slots:
    void on_modify_clicked();
    void comeBackTo();

    void on_search_clicked();

    void on_delete_2_clicked();

private:
    Ui::patience *ui;
};

#endif // PATIENCE_H
