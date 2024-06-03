
#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "primary.h"
#include "ui_primary.h"
#include "login.h"
#include "ui_login.h"

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QLineEdit>
#include <QSql>
#include<QSqlDatabase>
#include<QPixmap>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{ 
    this->setWindowTitle("用户登录界面");
    ui->setupUi(this);
    ui->username->setPlaceholderText("请输入用户名");
    ui->password->setPlaceholderText("请输入密码");
    ui->password->setEchoMode(QLineEdit::Password);
    sqlconnect();
    QWidget *widget = new QWidget(this);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::blue);
    widget->setPalette(palette);

    this->login1=new Login;
    connect(this->login1,SIGNAL(back()),this,SLOT(logincomeBackTo()));

    this->primary1 = new primary();
    connect(this->primary1,SIGNAL(back()),this,SLOT(primarycomeBackTo()));

    ui->label_3->setStyleSheet("background:transparent");
    //ui->appear_password_2->setStyleSheet("background:transparent");




}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::sqlconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("user");
    db.setUserName("root");
    db.setPassword("0516");
    db.open();
    bool ok=db.open();
    if(ok)
    {
        qDebug()<<"数据库连接成功！";
    }
    else
    {
        QMessageBox::information(this,"信息", "连接失败");
        qDebug()<<"打开数据库错误："<<db.lastError().text();
    }
}


//登录
void MainWidget::on_login_clicked()
{
    QString user_name=ui->username->text();
    QString pass=ui->password->text();


    QSqlQuery query;
    query.prepare("SELECT password FROM user WHERE id = :id");
    query.bindValue(":id", user_name);
    if (!query.exec()) {
        qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }

    if (query.next())
    {
        QString storedPassword = query.value(0).toString();
        if (storedPassword == pass) {
            qDebug() << "登录成功";

            //this->primary1 = new primary();
            this->primary1->show();
            this->close();

            ui->username->setPlaceholderText("请输入手机号");
            ui->password->setPlaceholderText("请输入密码");
            ui->username->clear();
            ui->password->clear();
            QMessageBox::information(this,"提示","登录成功");
        }
        else {
            ui->password->clear();
            ui->password->setPlaceholderText("密码错误，请重新输入");
        }
    }
    //不存在
    else
    {
        ui->username->setPlaceholderText("该用户不存在");
        ui->username->clear();
    }
}

//注册
void MainWidget::on_regi_clicked()
{
    //this->login1=new Login();
    this->login1->show();
    this->close();
    ui->username->clear();
    ui->password->clear();
}

/*//是否显示密码
void MainWidget::on_appear_password_clicked(bool checked)
{
    if(checked)
    {
        ui->password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->password->setEchoMode(QLineEdit::Password);
    }
}*/

void MainWidget::logincomeBackTo()
{
    this->login1->hide();
    this->show();
}

void MainWidget::primarycomeBackTo()
{
    this->primary1->hide();
    this->show();
}


void MainWidget::on_appear_password_2_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        // 显示密码
        ui->password->setEchoMode(QLineEdit::Normal);
    } else
    {
        // 隐藏密码
        ui->password->setEchoMode(QLineEdit::Password);
    }
}
