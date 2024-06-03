#include "office_sa.h"
#include "ui_office_sa.h"

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

office_sa::office_sa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::office_sa)
{
    ui->setupUi(this);
    sqlconnect();

    QPalette palette = this->palette();
    QPixmap background("D:/Qt/database system/hospital.jpg");
    palette.setBrush(QPalette::Window, background);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

office_sa::~office_sa()
{
    delete ui;
}

void office_sa::sqlconnect()
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

void office_sa::on_add_clicked()
{
    QString number1=ui->number_2->text();
    int number11 = number1.toInt();
    QString address1 = ui->address_2->text();
    QString name1 = ui->name_2->text();
    QString phone1 = ui->phone_2->text();
    int phone11 = phone1.toInt();
    QString leader1=ui->leader_2->text();

    QSqlQuery query;
    query.prepare("SELECT `科室号` FROM office WHERE `科室号` = :number12");
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
        if(!ui->number_2->text().isEmpty() && !ui->name_2->text().isEmpty())
        {

                QSqlQuery query1;
                query1.prepare("INSERT INTO office (`科室号`, `科室名称`, `科室电话`, `科室地址`, `科室主任`) VALUES (:number12, :name12,:phone12,:address12,:leader12)");
                query1.bindValue(":number12", number11);
                query1.bindValue(":name12", name1);
                query1.bindValue(":address12", address1);
                query1.bindValue(":phone12", phone11);
                query1.bindValue(":leader12", leader1);
                if (query1.exec()) {
                    qDebug() << "添加成功";
                    QMessageBox::information(this, "提示", "添加成功");
                    ui->name_2->clear();
                    ui->address_2->clear();
                    ui->number_2->clear();
                    ui->phone_2->clear();
                    ui->leader_2->clear();
                    on_b_clicked();
                }
        }
        else
        {
           QMessageBox::information(this, "错误", "添加失败");
        }
    }

}

void office_sa::on_modify_clicked()
{
    QString number1 = ui->number_2->text();
    int number11 = number1.toInt();
    QString address1 = ui->address_2->text();
    QString name1 = ui->name_2->text();
    QString phone1 = ui->phone_2->text();
    int phone11 = phone1.toInt();
    QString leader1 = ui->leader_2->text();

    QSqlQuery query;
    query.prepare("SELECT `科室号` FROM office WHERE `科室号` = :number12");
    query.bindValue(":number12", number1);

    if (!query.exec()) {
        qDebug() << "查询执行失败: " << query.lastError();
        return;
    }

    if (!query.next()) {
        qDebug() << "修改科室号";
        if (!ui->name_2->text().isEmpty()) {
            QSqlQuery query1;
            query1.prepare("SELECT `科室号` FROM office WHERE `科室名称` = :name12");
            query1.bindValue(":name12", name1);

            if (!query1.exec()) {
                qDebug() << "查询执行失败: " << query1.lastError();
                return;
            }

            if (!query1.next()) {
                QMessageBox::information(this, "错误", "输入不合法");
                return;
            }

            QString oldnumber = query1.value(0).toString();

            QSqlDatabase db = QSqlDatabase::database();
            db.transaction();

            // 调用存储过程更新office表的信息
            QSqlQuery queryUpdateOffice;
            queryUpdateOffice.prepare("CALL UpdateOfficeInfo2(:number, :name, :phone, :address, :leader)");
            queryUpdateOffice.bindValue(":number", number11);
            queryUpdateOffice.bindValue(":name", name1);
            queryUpdateOffice.bindValue(":leader", leader1.isEmpty() ? QVariant(QVariant::String) : leader1);
            queryUpdateOffice.bindValue(":address", address1.isEmpty() ? QVariant(QVariant::String) : address1);
            queryUpdateOffice.bindValue(":phone", phone1.isEmpty() ? QVariant(QVariant::String) : phone11);
            if (!queryUpdateOffice.exec()) {
                QMessageBox::information(this, "错误", "更新科室信息失败: " + queryUpdateOffice.lastError().text());
                db.rollback();
                return;
            }

            // 调用存储过程更新doctor表的科室号
            QSqlQuery queryUpdateDoctor;
            queryUpdateDoctor.prepare("CALL UpdateDoctorOfficeNumber(:newnumber, :oldnumber)");
            queryUpdateDoctor.bindValue(":newnumber", number11);
            queryUpdateDoctor.bindValue(":oldnumber", oldnumber.toInt());
            if (!queryUpdateDoctor.exec()) {
                QMessageBox::information(this, "错误", "更新医生科室号失败: " + queryUpdateDoctor.lastError().text());
                db.rollback();
                return;
            }

            // 调用存储过程更新nurse表的科室号
            QSqlQuery queryUpdateNurse;
            queryUpdateNurse.prepare("CALL UpdateNurseOfficeNumber(:newnumber, :oldnumber)");
            queryUpdateNurse.bindValue(":newnumber", number11);
            queryUpdateNurse.bindValue(":oldnumber", oldnumber.toInt());
            if (!queryUpdateNurse.exec()) {
                QMessageBox::information(this, "错误", "更新护士科室号失败: " + queryUpdateNurse.lastError().text());
                db.rollback();
                return;
            }

            db.commit();
            QMessageBox::information(this, "成功", "科室信息更新成功");
            on_b_clicked();
        } else {
            QMessageBox::information(this, "错误", "输入不合法");
        }
    } else {
        qDebug() << "不修改科室号";
        QSqlDatabase db = QSqlDatabase::database();
        db.transaction();

        // 调用存储过程更新office表的信息
        QSqlQuery queryUpdateOffice;
        queryUpdateOffice.prepare("CALL UpdateOfficeInfo2(:number, :name, :phone, :address, :leader)");
        queryUpdateOffice.bindValue(":number", number11);
        queryUpdateOffice.bindValue(":name", name1.isEmpty() ? QVariant(QVariant::String) : name1);
        queryUpdateOffice.bindValue(":leader", leader1.isEmpty() ? QVariant(QVariant::String) : leader1);
        queryUpdateOffice.bindValue(":address", address1.isEmpty() ? QVariant(QVariant::String) : address1);
        queryUpdateOffice.bindValue(":phone", phone1.isEmpty() ? QVariant(QVariant::String) : phone11);

        if (queryUpdateOffice.exec()) {
            db.commit();
            qDebug() << "Update successful!";
            on_b_clicked();
        } else {
            db.rollback();
            QMessageBox::information(this, "错误", "更新科室信息失败: " + queryUpdateOffice.lastError().text());
        }
    }
}


void office_sa::on_b_clicked()
{
    ui->name_2->clear();
    ui->number_2->clear();
    ui->leader_2->clear();
    ui->phone_2->clear();
    ui->address_2->clear();
    emit this->back();
}

