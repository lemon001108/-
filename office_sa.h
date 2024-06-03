#ifndef OFFICE_SA_H
#define OFFICE_SA_H

#include <QWidget>

namespace Ui {
class office_sa;
}

class office_sa : public QWidget
{
    Q_OBJECT

public:
    explicit office_sa(QWidget *parent = nullptr);
    ~office_sa();

    void sqlconnect();

private slots:

    void on_add_clicked();

    void on_modify_clicked();

    void on_b_clicked();

signals:
    void back();

private:
    Ui::office_sa *ui;
};

#endif // OFFICE_SA_H
