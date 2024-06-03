#include "patience_sa.h"
#include "ui_patience_sa.h"

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


patience_sa::patience_sa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patience_sa)
{
    ui->setupUi(this);
    sqlconnect();

    QPalette palette = this->palette();
    QPixmap background("D:/Qt/database system/hospital.jpg");
    palette.setBrush(QPalette::Window, background);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

patience_sa::~patience_sa()
{
    delete ui;
}

void patience_sa::sqlconnect()
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

void patience_sa::on_add_clicked()
{
    QString number1=ui->number_2->text();
    int number11 = number1.toInt();
    QString gender1=ui->gender_2->text();
    QString name1 = ui->name_2->text();
    QString docnumber1=ui->docnumber_2->text();
    int docnumber11 = docnumber1.toInt();
    QString phone1 = ui->phone_2->text();
    int phone11 = phone1.toInt();
    QString borntime1=ui->borntime_2->text();
    QString end1=ui->end_2->text();
    QString history1=ui->history_4->text();
    QString blood1=ui->blood_2->text();
    QString time1=ui->time_2->text();




    QSqlQuery query;
    query.prepare("SELECT `病历号` FROM patience WHERE `病历号` = :number12");
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
        if(!ui->number_2->text().isEmpty() && !ui->name_2->text().isEmpty() )
        {
            qDebug()<<"here2";
            QSqlQuery query1;
            query1.prepare("INSERT INTO patience (`病历号`, `医生编号`, `病人姓名`, `病人性别`, `血型`, `看诊时间`, `联系电话`, `既往病史`, `诊断结果`, `出生日期`) VALUES (:number12, :docnum12,:name12,:gender12,:blood12,:time12,:phone12,:history12,:end12,:borntime12)");
            query1.bindValue(":number12", number11);
            query1.bindValue(":docnum12", docnumber11);
            query1.bindValue(":name12", name1);
            query1.bindValue(":gender12", gender1);
            query1.bindValue(":borntime12", borntime1);
            query1.bindValue(":phone12", phone11);
            query1.bindValue(":blood12", blood1);
            query1.bindValue(":time12", time1);
            query1.bindValue(":history12", history1);
            query1.bindValue(":end12", end1);
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



void patience_sa::on_modify_clicked()
{
    QString number1=ui->number_2->text();
    int number11 = number1.toInt();
    QString gender1=ui->gender_2->text();
    QString name1 = ui->name_2->text();
    QString docnumber1=ui->docnumber_2->text();
    int docnumber11 = docnumber1.toInt();
    QString phone1 = ui->phone_2->text();
    int phone11 = phone1.toInt();
    QString borntime1=ui->borntime_2->text();
    QString end1=ui->end_2->text();
    QString history1=ui->history_4->text();
    QString blood1=ui->blood_2->text();
    QString time1=ui->time_2->text();

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    QSqlQuery query;
    query.prepare("UPDATE patience SET `病人姓名` = COALESCE(:name, `病人姓名`), "
                  "`医生编号` = COALESCE(:docnum, `医生编号`), "
                  "`病人性别` = COALESCE(:gender, `病人性别`), "
                  "`血型` = COALESCE(:blood, `血型`), "
                  "`看诊时间` = COALESCE(:time, `看诊时间`), "
                  "`联系电话` = COALESCE(:phone, `联系电话`), "
                  "`诊断结果` = COALESCE(:end, `诊断结果`), "
                  "`出生日期` = COALESCE(:borntime, `出生日期`), "
                  "`既往病史` = COALESCE(:history, `既往病史`) "
                  "WHERE `病历号` = :number");

    query.bindValue(":number", number11);
    query.bindValue(":name", name1.isEmpty() ? QVariant(QVariant::String) : name1);
    query.bindValue(":borntime", borntime1.isEmpty() ? QVariant(QVariant::String) : borntime1);
    query.bindValue(":docnum", docnumber1.isEmpty() ? QVariant(QVariant::Int) : docnumber11);
    query.bindValue(":gender", gender1.isEmpty() ? QVariant(QVariant::String) : gender1);
    query.bindValue(":blood", blood1.isEmpty() ? QVariant(QVariant::String) : blood1);
    query.bindValue(":time", time1.isEmpty() ? QVariant(QVariant::String) : time1);
    query.bindValue(":phone", phone1.isEmpty() ? QVariant(QVariant::Int) : phone11);
    query.bindValue(":history", history1.isEmpty() ? QVariant(QVariant::String) : history1);
    query.bindValue(":end", end1.isEmpty() ? QVariant(QVariant::String) : end1);


    if (query.exec()) {
        db.commit();
        qDebug() << "Update successful!";
        on_b_clicked();
    } else {
        db.rollback();
        qDebug() << "Update error: " << query.lastError();
    }
}

void patience_sa::on_b_clicked()
{
    ui->name_2->clear();
    ui->borntime_2->clear();
    ui->number_2->clear();
    ui->docnumber_2->clear();
    ui->gender_2->clear();
    ui->phone_2->clear();
    ui->end_2->clear();
    ui->history_4->clear();
    ui->blood_2->clear();
    ui->time_2->clear();

    emit this->back();
}

