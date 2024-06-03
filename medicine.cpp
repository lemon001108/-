#include "medicine.h"
#include "ui_medicine.h"

#include<QHeaderView>
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
#include <QTableWidget>
#include <QWidget>

medicine::medicine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medicine)
{
    ui->setupUi(this);
    sqlconnect();

    this->medicine_sa1=new medicine_sa;
    connect(this->medicine_sa1,SIGNAL(back()),this,SLOT(comeBackTo()));
}

medicine::~medicine()
{
    delete ui;
}

void medicine::sqlconnect()
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
    if (!query.exec("SELECT * FROM medicine"))
    {
        qDebug() << "查询错误：" << query.lastError().text();
        return;
    }

    // 清空表格
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"药品名称"<<"库存量"<<"生产厂家";
    ui->tableWidget->setColumnCount(headerText.count());
    for (int i=0; i<ui->tableWidget->columnCount(); i++)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setBold(false);     //设置字体加粗
        font.setPointSize(9);  //设置字体字号
        headerItem->setTextColor(Qt::black); //设置颜色
        headerItem->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
    //  ui->tableWidget ->setGeometry (0,58,825,342);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
//    int width = ui->tableWidget->width();
//       ui->tableWidget->setColumnWidth(0, width/3);
//       ui->tableWidget->setColumnWidth(1, width/3);
//       ui->tableWidget->setColumnWidth(2, width/3);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 280);


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
    // 调整列宽
    /*for (int col = 0; col < headerText.count(); ++col)
    {
        ui->tableWidget->resizeColumnToContents(col);
    }
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);*/


}

void medicine::on_search_clicked()
{
    QString name=ui->lineEdit->text();
    QString storename=ui->lineEdit_2->text();


    //QString sql = QString("SELECT * FROM doctor WHERE `医生编号` = '%1'").arg(doctnum);
    QSqlQuery query;
    query.prepare("SELECT * FROM medicine WHERE `药品名称` = :number12 and `生产厂家` = :store12");
    query.bindValue(":number12", name);
    query.bindValue(":store12", storename);

    if (!query.exec()) {
        qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }
    if (query.next())
    {
            ui->tableWidget->clearContents();
            //ui->tableWidget->insertRow(0);
            for (int col = 0; col < 3; ++col)
            {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                ui->tableWidget->setItem(0, col, item);
            }
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();

    }
    //不存在
    else
    {
        QMessageBox::information(this,"提示","编号不存在");
    }
}

void medicine::on_delete_2_clicked()
{
    QString name=ui->lineEdit->text();
    QString storename=ui->lineEdit_2->text();


        QSqlQuery query1;
        query1.prepare("SELECT * FROM medicine WHERE `药品名称` = :number12 and `生产厂家` = :store12");
        query1.bindValue(":number12", name);
        query1.bindValue(":store12", storename);

        QString str=QString("delete from medicine where `药品名称`='%1' and `生产厂家`='%3'" ).arg(name).arg(storename);

        //编写删除sql语句
        if (!query1.exec(str)) {    //执行删除语句
            QMessageBox::information(this,"错误","删除失败");
        }
        else {
            QMessageBox::information(this,"提示","删除成功");
            ui->lineEdit->clear();
            //更新table
           update1();
        }

}

void medicine::on_modify_clicked()
{
    this->medicine_sa1->show();
    this->close();
}

void medicine::comeBackTo()
{
    this->medicine_sa1->hide();
    this->show();
    //更新table
    update1();
}

void medicine::update1()
{
    //更新table
    ui->tableWidget->clearContents();
    QSqlQuery query("SELECT * FROM medicine");
    int row = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < 3; ++col)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        ++row;
    }
}

