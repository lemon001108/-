#include "nurse.h"
#include "ui_nurse.h"

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

nurse::nurse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nurse)
{
    ui->setupUi(this);
    sqlconnect();

    this->nurse_sa1=new nurse_sa;
    connect(this->nurse_sa1,SIGNAL(back()),this,SLOT(comeBackTo()));

}

nurse::~nurse()
{
    delete ui;
}

void nurse::sqlconnect()
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
    if (!query.exec("SELECT * FROM nurse"))
    {
        qDebug() << "查询错误：" << query.lastError().text();
        return;
    }

    // 清空表格
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"护士编号"<<"科室号"<<"姓名"<<"性别"<<"年龄"<<"电话";
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

void nurse::on_modify_clicked()
{
    this->nurse_sa1->show();
    this->close();

}

void nurse::comeBackTo()
{
    this->nurse_sa1->hide();
    this->show();
    //更新table
    update1();
}

void nurse::on_search_clicked()
{
    QString nurnum=ui->lineEdit->text();
    int nurnum1 = nurnum.toInt();

    QSqlQuery query;
    query.prepare("SELECT * FROM nurse WHERE `护士编号` = :number12");
    query.bindValue(":number12", nurnum);

    if (!query.exec()) {
        qDebug() << "查询执行失败：" << query.lastError().text();
        return;
    }
    if (query.next())
    {
            ui->tableWidget->clearContents();
            //ui->tableWidget->insertRow(0);
            for (int col = 0; col < 6; ++col)
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

void nurse::on_delete_2_clicked()
{
    QString nurnum=ui->lineEdit->text();
    int nurnum1 = nurnum.toInt();

    QSqlQuery query1;
    query1.prepare("SELECT * FROM nurse WHERE `护士编号` = :number12");
    query1.bindValue(":number12", nurnum);

    QString str=QString("delete from nurse where `护士编号`='%1'").arg(nurnum1);

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

void nurse::update1()
{
    //更新table
    ui->tableWidget->clearContents();
    QSqlQuery query("SELECT * FROM nurse");
    int row = 0;
    while (query.next())
    {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < 6; ++col)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget->setItem(row, col, item);
        }
        ++row;
    }
}


void nurse::on_search_office_clicked()
{
    QString nurnum=ui->lineEdit->text();
    int nurnum1 = nurnum.toInt();

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    // 查询视图中的数据
    query.prepare("SELECT department_id, department_name FROM nurse_department_view WHERE nurse_id = :nurseId");
    query.bindValue(":nurseId", nurnum1);

    if (!query.exec()) {
        QMessageBox::information(this, "错误", "查询失败: " + query.lastError().text());
        return;
    }

    // 处理查询结果
    if (query.next()) {
        int departmentId = query.value("department_id").toInt();
        QString departmentName = query.value("department_name").toString();

        // 使用 QMessageBox 显示查询结果
        QMessageBox::information(this, "科室信息",
                                 "Department ID: " + QString::number(departmentId) + "\n"
                                 "Department Name: " + departmentName);
        ui->lineEdit->clear();
    } else {
        QMessageBox::information(this, "提示", "未找到相关记录");
    }
}
