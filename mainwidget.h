#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QProcess>
#include <QString>
#include<QSqlDatabase>

#include "primary.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void sqlconnect();
    Login * login1 = NULL;
    primary *primary1 = NULL;



private slots:

    //void on_appear_password_clicked(bool checked);
    void on_login_clicked();
    void on_regi_clicked();
    void logincomeBackTo();
    void primarycomeBackTo();


    void on_appear_password_2_stateChanged(int arg1);

private:
    Ui::MainWidget *ui;
};
#endif // MAINWIDGET_H

