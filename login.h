#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void sqlconnect();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_back_clicked();

signals:
    void back();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
