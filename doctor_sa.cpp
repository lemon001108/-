#include "doctor_sa.h"
#include "ui_doctor_sa.h"
#include "ui_doct.h"
#include "doct.h"

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
#include <QSqlRecord>
#include<QSqlQueryModel>
#include<QTableWidget>
#include<QHeaderView>

doctor_sa::doctor_sa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctor_sa)
{
    ui->setupUi(this);
    sqlconnect();

    QPalette palette = this->palette();
    QPixmap background("D:/Qt/database system/hospital.jpg");
    palette.setBrush(QPalette::Window, background);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

doctor_sa::~doctor_sa()
{
    delete ui;
}

void doctor_sa::sqlconnect()
{
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QODBC");
    db1.setHostName("127.0.0.1");
    db1.setPort(3306);
    db1.setDatabaseName("user");
    db1.setUserName("root");
    db1.setPassword("0516");
    db1.open();
    bool ok=db1.open();
    if(ok)
    {
        qDebug()<<"数据库连接成功！";
    }
    else
    {
        QMessageBox::information(this,"信息", "连接失败");
        qDebug()<<"打开数据库错误："<<db1.lastError().text();
    }
}


void doctor_sa::on_add_clicked()
{
    QString number1=ui->number_2->text();
    int number11 = number1.toInt();
    QString age1 = ui->age_2->text();
    int age11 = age1.toInt();
    QString gender1=ui->gender_2->text();
    QString name1 = ui->name_2->text();
    QString office1=ui->office_2->text();
    int office11 = office1.toInt();
    QString phone1 = ui->phone_2->text();
    int phone11 = phone1.toInt();
    QString stage1=ui->stage_2->text();

    QSqlQuery query;
    query.prepare("SELECT `医生编号` FROM doctor WHERE `医生编号` = :number12");
    query.bindValue(":number12", number11);


    if (!query.exec()) {
        qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }
    if (query.next())
    {
        QString storednumber = query.value(0).toString();
        if (storednumber == number11) {
            qDebug() << "该编号已存在";
            QMessageBox::information(this,"提示","该编号已存在");
        }
        else {
        }
    }
    //不存在
    else
    {
        qDebug()<<"here1";
        if(!ui->number_2->text().isEmpty() && !ui->name_2->text().isEmpty() && !ui->gender_2->text().isEmpty() && !ui->age_2->text().isEmpty())
        {
            qDebug()<<"here2";
            QSqlQuery query1;
            query1.prepare("INSERT INTO doctor (`医生编号`, `科室号`, `姓名`, `性别`, `年龄`, `医生电话`, `职称`) VALUES (:number12, :office12,:name12,:gender12,:age12,:phone12,:satge12)");
            query1.bindValue(":number12", number11);
            query1.bindValue(":office12", office11);
            query1.bindValue(":name12", name1);
            query1.bindValue(":gender12", gender1);
            query1.bindValue(":age12", age11);
            query1.bindValue(":phone12", phone11);
            query1.bindValue(":satge12", stage1);
            if (query1.exec()) {
                qDebug() << "添加成功";
                QMessageBox::information(this, "提示", "添加成功");
                on_b_clicked();
            }
            else {
                qDebug() << "添加失败：" << query1.lastError().text();
                QMessageBox::information(this, "错误", "添加失败：" + query1.lastError().text());
            }

        }
        else
        {
            QMessageBox::information(this, "错误", "输入信息不合法");
        }
    }
}



void doctor_sa::on_modify_clicked()
{
    QString number1 = ui->number_2->text();
    int number11 = number1.toInt();
    QString age1 = ui->age_2->text();
    int age11 = age1.toInt();
    QString gender1 = ui->gender_2->text();
    QString name1 = ui->name_2->text();
    QString office1 = ui->office_2->text();
    int office11 = office1.toInt();
    QString phone1 = ui->phone_2->text();
    int phone11 = phone1.toInt();
    QString stage1 = ui->stage_2->text();

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    QSqlQuery query;
    query.prepare("UPDATE doctor SET `姓名` = COALESCE(:name, `姓名`), "
                  "`年龄` = COALESCE(:age, `年龄`), "
                  "`科室号` = COALESCE(:office, `科室号`), "
                  "`性别` = COALESCE(:gender, `性别`), "
                  "`医生电话` = COALESCE(:phone, `医生电话`), "
                  "`职称` = COALESCE(:stage, `职称`) "
                  "WHERE `医生编号` = :number");

    query.bindValue(":number", number11);
    query.bindValue(":name", name1.isEmpty() ? QVariant(QVariant::String) : name1);
    query.bindValue(":age", age1.isEmpty() ? QVariant(QVariant::Int) : age11);
    query.bindValue(":office", office1.isEmpty() ? QVariant(QVariant::Int) : office11);
    query.bindValue(":gender", gender1.isEmpty() ? QVariant(QVariant::String) : gender1);
    query.bindValue(":phone", phone1.isEmpty() ? QVariant(QVariant::Int) : phone11);
    query.bindValue(":stage", stage1.isEmpty() ? QVariant(QVariant::String) : stage1);

    if (query.exec()) {
        db.commit();
        qDebug() << "Update successful!";
        on_b_clicked();
    } else {
        db.rollback();
        qDebug() << "Update error: " << query.lastError();
    }
}

void doctor_sa::on_b_clicked()
{
    ui->name_2->clear();
    ui->age_2->clear();
    ui->number_2->clear();
    ui->office_2->clear();
    ui->gender_2->clear();
    ui->phone_2->clear();
    ui->stage_2->clear();
    emit this->back();
}
