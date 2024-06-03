#include "medicine_sa.h"
#include "ui_medicine_sa.h"

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

medicine_sa::medicine_sa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medicine_sa)
{
    ui->setupUi(this);
    sqlconnect();

    QPalette palette = this->palette();
    QPixmap background("D:/Qt/database system/hospital.jpg");
    palette.setBrush(QPalette::Window, background);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

medicine_sa::~medicine_sa()
{
    delete ui;
}

void medicine_sa::sqlconnect()
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

void medicine_sa::on_b_clicked()
{
    ui->name_2->clear();
    ui->store_2->clear();
    ui->count_2->clear();
    emit this->back();
}

void medicine_sa::on_add_clicked()
{
    QString name1=ui->name_2->text();
    QString count1 = ui->count_2->text();
    int count11 = count1.toInt();
    QString store1=ui->store_2->text();


    QSqlQuery query;
    query.prepare("SELECT `药品名称` FROM medicine WHERE `药品名称` = :name12 and `生产厂家` = :store12");
    query.bindValue(":name12", name1);
    query.bindValue(":store12", store1);


    if (!query.exec()) {
        qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }
    if (query.next())
    {
        QString medicine = query.value(0).toString();
        QString storednumber = query.value(2).toString();
        if (medicine==name1 and storednumber == store1) {
            qDebug() << "该药品已存在";
            QMessageBox::information(this,"提示","该药品已存在");
        }
        else {
        }
    }
    //不存在
    else
    {
        qDebug()<<"here1";
        if(!ui->name_2->text().isEmpty() && !ui->store_2->text().isEmpty())
        {
            qDebug()<<"here2";
            QSqlQuery query1;
            query1.prepare("INSERT INTO medicine (`药品名称`, `库存量`, `生产厂家`) VALUES (:name12, :count12,:store12)");
            query1.bindValue(":count12", count11);
            query1.bindValue(":store12", store1);
            query1.bindValue(":name12", name1);

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

void medicine_sa::on_modify_clicked()
{
    QString name1=ui->name_2->text();
    QString count1 = ui->count_2->text();
    int count11 = count1.toInt();
    QString store1=ui->store_2->text();

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    QSqlQuery query;
    query.prepare("UPDATE medicine SET `药品名称` = COALESCE(:name, `药品名称`), "
                  "`库存量` = COALESCE(:count, `库存量`), "
                  "`生产厂家` = COALESCE(:store, `生产厂家`) "
                  "WHERE `药品名称` = :name and `生产厂家` = :store");

    query.bindValue(":name", name1.isEmpty() ? QVariant(QVariant::String) : name1);
    query.bindValue(":store", store1.isEmpty() ? QVariant(QVariant::String) : store1);
    query.bindValue(":count", count1.isEmpty() ? QVariant(QVariant::Int) : count11);


    if (query.exec()) {
        db.commit();
        qDebug() << "Update successful!";
        on_b_clicked();
    } else {
        db.rollback();
        qDebug() << "Update error: " << query.lastError();
    }

}
