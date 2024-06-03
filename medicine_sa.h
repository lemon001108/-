#ifndef MEDICINE_SA_H
#define MEDICINE_SA_H

#include <QWidget>

namespace Ui {
class medicine_sa;
}

class medicine_sa : public QWidget
{
    Q_OBJECT

public:
    explicit medicine_sa(QWidget *parent = nullptr);
    ~medicine_sa();

    void sqlconnect();

signals:
    void back();

private slots:
    void on_b_clicked();

    void on_modify_clicked();

    void on_add_clicked();

private:
    Ui::medicine_sa *ui;
};

#endif // MEDICINE_SA_H
