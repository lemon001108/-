#ifndef NURSE_SA_H
#define NURSE_SA_H

#include <QWidget>

namespace Ui {
class nurse_sa;
}

class nurse_sa : public QWidget
{
    Q_OBJECT

public:
    explicit nurse_sa(QWidget *parent = nullptr);
    ~nurse_sa();

    void sqlconnect();

private slots:

    void on_add_clicked();

    void on_modify_clicked();

    void on_b_clicked();

signals:
    void back();

private:
    Ui::nurse_sa *ui;
};

#endif // NURSE_SA_H
