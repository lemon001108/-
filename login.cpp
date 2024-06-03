#include "login.h"
#include "ui_login.h"

#include <QFile>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QLineEdit>
#include <QSql>
#include<QSqlDatabase>

void Login::sqlconnect()
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

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("请输入账号名");
    ui->lineEdit_2->setPlaceholderText("请输入密码");
    ui->lineEdit_3->setPlaceholderText("请再次输入密码");
    sqlconnect();
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
    QString user_name=ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    QSqlQuery query;
    query.prepare("SELECT id FROM user WHERE id = :id");
    query.bindValue(":id", user_name);
    if (!query.exec()) {
        qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }

    if (query.next())
    {
        QString storedPassword = query.value(0).toString();
        if (storedPassword == user_name) {
            qDebug() << "该用户已存在";
            QMessageBox::information(this,"提示","该用户已存在");
        }
        else {
        }
    }
    //不存在
    else
    {
        if(!ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty())
        {
            if(ui->lineEdit_2->text()==ui->lineEdit_3->text())
            {
                QSqlQuery query1;
                query1.prepare("INSERT INTO user (id, password) VALUES (:id, :password)");
                query1.bindValue(":id", user_name);
                query1.bindValue(":password", password);
                if (query1.exec()) {
                    qDebug() << "用户注册成功";
                    QMessageBox::information(this, "提示", "注册成功");
                } else {
                    qDebug() << "用户注册失败：" << query1.lastError().text();
                    QMessageBox::information(this, "错误", "注册失败：" + query1.lastError().text());
                }

            }
            else
            {
                QMessageBox::information(this, "错误", "两次密码不一致注册失败");
            }
        }
        else
        {
           QMessageBox::information(this, "错误", "注册失败");
        }
    }


}

void Login::on_pushButton_2_clicked()
{
    //this->hide();
    //this->parentWidget()->show();
     emit this->back();

}

void Login::on_back_clicked()
{
    emit this->back();

}
