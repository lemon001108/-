#ifndef PATIENCE_SA_H
#define PATIENCE_SA_H

#include <QWidget>

namespace Ui {
class patience_sa;
}

class patience_sa : public QWidget
{
    Q_OBJECT

public:
    explicit patience_sa(QWidget *parent = nullptr);
    ~patience_sa();
    void sqlconnect();

private slots:

    void on_add_clicked();

    void on_modify_clicked();

    void on_b_clicked();

signals:
    void back();

private:
    Ui::patience_sa *ui;
};

#endif // PATIENCE_SA_H
