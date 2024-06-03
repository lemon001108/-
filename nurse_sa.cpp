#include "nurse_sa.h"
#include "ui_nurse_sa.h"

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

nurse_sa::nurse_sa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nurse_sa)
{
    ui->setupUi(this);
    sqlconnect();

    QPalette palette = this->palette();
    QPixmap background("D:/Qt/database system/hospital.jpg");
    palette.setBrush(QPalette::Window, background);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

nurse_sa::~nurse_sa()
{
    delete ui;
}

void nurse_sa::sqlconnect()
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

void nurse_sa::on_add_clicked()
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

    QSqlQuery query;
    query.prepare("SELECT `护士编号` FROM nurse WHERE `护士编号` = :number12");
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
            QSqlQuery query1;
            query1.prepare("INSERT INTO nurse (`护士编号`, `科室号`, `护士姓名`, `性别`, `年龄`, `联系电话`) VALUES (:number12, :office12,:name12,:gender12,:age12,:phone12)");
            query1.bindValue(":number12", number11);
            query1.bindValue(":office12", office11);
            query1.bindValue(":name12", name1);
            query1.bindValue(":gender12", gender1);
            query1.bindValue(":age12", age11);
            query1.bindValue(":phone12", phone11);

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
           QMessageBox::information(this, "错误", "添加失败");
        }
    }

}

void nurse_sa::on_modify_clicked()
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

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    QSqlQuery query;
    query.prepare("UPDATE nurse SET `护士姓名` = COALESCE(:name, `护士姓名`), "
                  "`年龄` = COALESCE(:age, `年龄`), "
                  "`科室号` = COALESCE(:office, `科室号`), "
                  "`性别` = COALESCE(:gender, `性别`), "
                  "`联系电话` = COALESCE(:phone, `联系电话`) "
                  "WHERE `护士编号` = :number");

    query.bindValue(":number", number11);
    query.bindValue(":name", name1.isEmpty() ? QVariant(QVariant::String) : name1);
    query.bindValue(":age", age1.isEmpty() ? QVariant(QVariant::Int) : age11);
    query.bindValue(":office", office1.isEmpty() ? QVariant(QVariant::Int) : office11);
    query.bindValue(":gender", gender1.isEmpty() ? QVariant(QVariant::String) : gender1);
    query.bindValue(":phone", phone1.isEmpty() ? QVariant(QVariant::Int) : phone11);

    if (query.exec()) {
        db.commit();
        qDebug() << "Update successful!";
        on_b_clicked();
    } else {
        db.rollback();
        qDebug() << "Update error: " << query.lastError();
    }
}

void nurse_sa::on_b_clicked()
{
    ui->name_2->clear();
    ui->age_2->clear();
    ui->number_2->clear();
    ui->office_2->clear();
    ui->gender_2->clear();
    ui->phone_2->clear();
    emit this->back();
}

