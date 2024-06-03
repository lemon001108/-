#include "office.h"
#include "ui_office.h"

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

office::office(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::office)
{
    ui->setupUi(this);
    sqlconnect();

    this->office_sa1=new office_sa;
    connect(this->office_sa1,SIGNAL(back()),this,SLOT(comeBackTo()));

}

office::~office()
{
    delete ui;
}

void office::sqlconnect()
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
    if (!query.exec("SELECT * FROM office"))
    {
        qDebug() << "查询错误：" << query.lastError().text();
        return;
    }

    // 清空表格
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"科室号"<<"科室名称"<<"科室电话"<<"科室地址"<<"科室主任";
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

void office::comeBackTo()
{
    this->office_sa1->hide();
    this->show();
    //更新table
    update1();
}

void office::on_search_clicked()
{
    QString offnum=ui->lineEdit->text();
    int offnum1 = offnum.toInt();

    QSqlQuery query;
    query.prepare("SELECT * FROM office WHERE `科室号` = :number12");
    query.bindValue(":number12", offnum1);

    if (!query.exec()) {
        QMessageBox::information(this, "错误", "查询执行失败：: " + query.lastError().text());
        //qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }
    if (query.next())
    {
            ui->tableWidget->clearContents();
            //ui->tableWidget->insertRow(0);
            for (int col = 0; col < 5; ++col)
            {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                ui->tableWidget->setItem(0, col, item);
            }
            ui->lineEdit->clear();

    }
    //不存在
    else
    {
        QMessageBox::information(this,"提示","科室号不存在");
    }


}

void office::on_delete_2_clicked()
{
    QString offnum = ui->lineEdit->text();
    int offnum1 = offnum.toInt();

    if (offnum.isEmpty()) {
        QMessageBox::information(this, "错误", "科室号不能为空");
        return;
    }

    // 获取数据库连接并启动事务
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) {
        QMessageBox::information(this, "错误", "启动事务失败: " + db.lastError().text());
        return;
    }

    // 更新相关的医生记录
    QSqlQuery queryDeleteDoctor;
    //queryDeleteDoctor.prepare("DELETE FROM doctor WHERE `科室号` = :number");
    queryDeleteDoctor.prepare("UPDATE doctor SET `科室号` = NULL WHERE `科室号` = :number");
    queryDeleteDoctor.bindValue(":number", offnum1);
    // 执行更新医生记录的操作
    if (!queryDeleteDoctor.exec()) {
        QMessageBox::information(this, "错误", "删除医生记录失败: " + queryDeleteDoctor.lastError().text());
        db.rollback();  // 回滚事务
        return;
    }

    // 更新相关的护士记录
    QSqlQuery queryDeleteNurse;
    queryDeleteNurse.prepare("UPDATE nurse SET `科室号` = NULL WHERE `科室号` = :number");
    queryDeleteNurse.bindValue(":number", offnum1);
    // 执行更新护士记录的操作
    if (!queryDeleteNurse.exec()) {
        QMessageBox::information(this, "错误", "删除护士记录失败: " + queryDeleteNurse.lastError().text());
        db.rollback();  // 回滚事务
        return;
    }

    // 删除相关的科室记录
    QSqlQuery queryDeleteOffice;
    queryDeleteOffice.prepare("DELETE FROM office WHERE `科室号` = :number");
    queryDeleteOffice.bindValue(":number", offnum1);
    // 执行删除科室记录的操作
    if (!queryDeleteOffice.exec()) {
        QMessageBox::information(this, "错误", "删除科室记录失败: " + queryDeleteOffice.lastError().text());
        db.rollback();  // 回滚事务
        return;
    }

    // 提交事务
    if (!db.commit()) {
        QMessageBox::information(this, "错误", "提交事务失败: " + db.lastError().text());
        db.rollback();  // 回滚事务
    } else {
        QMessageBox::information(this, "提示", "删除成功");
        ui->lineEdit->clear();
        update1();  // 更新表格
    }
}


void office::on_modify_clicked()
{
    this->office_sa1->show();
    this->close();

}

void office::update1()
{
    ui->tableWidget->clearContents();
    QSqlQuery query("SELECT * FROM office");
    int row = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < 5; ++col)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        ++row;
    }
}

