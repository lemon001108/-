#include "patience.h"
#include "ui_patience.h"

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

patience::patience(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patience)
{
    ui->setupUi(this);
    sqlconnect();

    this->patience_sa1=new patience_sa;
    connect(this->patience_sa1,SIGNAL(back()),this,SLOT(comeBackTo()));
}

patience::~patience()
{
    delete ui;
}

void patience::sqlconnect()
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


    QSqlQuery query(db);
    // 执行查询语句
    if (!query.exec("SELECT * FROM doctor"))
    {
        qDebug() << "查询错误：" << query.lastError().text();
        return;
    }

    // 清空表格
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"病历号"<<"医生编号"<<"姓名"<<"性别"<<"血型"<<"看诊时间"<<"联系电话"<<"既往病史"<<"诊断结果"<<"出生日期";
    ui->tableWidget->setColumnCount(headerText.count());
    for (int i=0; i<ui->tableWidget->columnCount(); i++)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setBold(false);     //设置字体加粗
        font.setPointSize(10);  //设置字体字号
        headerItem->setTextColor(Qt::black); //设置颜色
        headerItem->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
    //  ui->tableWidget ->setGeometry (0,58,825,342);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑

    // 填充数据
    int row = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < headerText.count(); ++col)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        ++row;
    }
}

void patience::on_modify_clicked()
{
    this->patience_sa1->show();
    this->close();

}

void patience::comeBackTo()
{
    this->patience_sa1->hide();
    this->show();
    //更新table
    update1();
}

void patience::on_search_clicked()
{
    QString panum=ui->lineEdit->text();
    int panum1 = panum.toInt();

    QSqlQuery query;
    query.prepare("SELECT * FROM patience WHERE `病历号` = :number12");
    query.bindValue(":number12", panum);

    if (!query.exec()) {
        qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }
    if (query.next())
    {
            ui->tableWidget->clearContents();
            //ui->tableWidget->insertRow(0);
            for (int col = 0; col < 10; ++col)
            {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                ui->tableWidget->setItem(0, col, item);
            }
            ui->lineEdit->clear();

    }
    //不存在
    else
    {
        QMessageBox::information(this,"提示","编号不存在");
    }


}

void patience::on_delete_2_clicked()
{
    QString panum=ui->lineEdit->text();
    int panum1 = panum.toInt();

    QSqlQuery query1;
    query1.prepare("SELECT * FROM patience WHERE `病历号` = :number12");
    query1.bindValue(":number12", panum);

        QString str=QString("delete from patience where `病历号`='%1'").arg(panum1);

        //编写删除sql语句
        if (!query1.exec(str)) {    //执行删除语句
            qDebug() << "删除失败：" << query1.lastError().text();
        }
        else {
            QMessageBox::information(this,"提示","删除成功");
            ui->lineEdit->clear();
            //更新table
            update1();
        }


}

void patience::update1()
{
    //更新table
    ui->tableWidget->clearContents();
    QSqlQuery query("SELECT * FROM patience");
    int row = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < 10; ++col)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        ++row;
    }
}

