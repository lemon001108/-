#include "primary.h"
#include "ui_primary.h"

#include "govern.h"
#include "ui_govern.h"
#include "doct.h"
#include "ui_doct.h"
#include "medicine.h"
#include "ui_medicine.h"
#include "nurse.h"
#include "ui_nurse.h"
#include "office.h"
#include "ui_office.h"
#include "patience.h"
#include "ui_patience.h"



primary::primary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::primary),
      doctor1(nullptr),
      office1(nullptr),
      patience1(nullptr),
      nurse1(nullptr),
      medicine1(nullptr)
{
    ui->setupUi(this);
    initPage();

}

primary::~primary()
{
    delete ui;
}

/*void primary::switchPage(){
    QToolButton *button = qobject_cast<QToolButton*>(sender());
    if(button==ui->doctor_btn)
        ui->stackedWidget->setCurrentIndex(0);
    else if(button==ui->office_btn)
        ui->stackedWidget->setCurrentIndex(1);
    else if(button==ui->nurse_btn)
        ui->stackedWidget->setCurrentIndex(2);
    else if(button==ui->patience_btn)
        ui->stackedWidget->setCurrentIndex(3);
    else if(button==ui->medicine_btn)
        ui->stackedWidget->setCurrentIndex(4);

    int i = 0;
    ui->stackedWidget->widget(i);
}*/


void primary::initPage()
{
    doctor1 = new doct(this);
    ui->stackedWidget->addWidget(doctor1);

    office1 = new office(this);
    ui->stackedWidget->addWidget(office1);

    patience1 = new patience(this);
    ui->stackedWidget->addWidget(patience1);

    nurse1 = new nurse(this);
    ui->stackedWidget->addWidget(nurse1);

    medicine1 = new medicine(this);
    ui->stackedWidget->addWidget(medicine1);

    ui->stackedWidget->setCurrentIndex(0);

    /*auto childrenList = ui->widget->children();
    for(auto child : childrenList)
    {
        if (child->isWidgetType())
        {
            QPushButton* button = qobject_cast<QPushButton*>(child);
            if(button && button->objectName().contains("btn"))
            {
                connect(button, &QPushButton::clicked, this, &primary::dealMenu);
            }
        }
    }*/
    // 连接 stackedWidget 的 currentChanged 信号到槽函数
        //connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &primary::on_stackedWidget_currentChanged);

    // 连接按钮信号与槽函数
        connect(ui->doctor_btn, &QPushButton::clicked, this, &primary::dealMenu);
        connect(ui->office_btn, &QPushButton::clicked, this, &primary::dealMenu);
        connect(ui->patience_btn, &QPushButton::clicked, this, &primary::dealMenu);
        connect(ui->nurse_btn, &QPushButton::clicked, this, &primary::dealMenu);
        connect(ui->medicine_btn, &QPushButton::clicked, this, &primary::dealMenu);
}

void primary::dealMenu()
{
    QString str = sender()->objectName();
    if (str == "doctor_btn")
    {
        ui->stackedWidget->setCurrentIndex(0);
        doctor1->update1();
    }
    else if (str == "office_btn")
    {
        ui->stackedWidget->setCurrentIndex(1);
        office1->update1();
    }
    else if (str == "patience_btn")
    {
        ui->stackedWidget->setCurrentIndex(2);
        patience1->update1();
    }
    else if (str == "nurse_btn")
    {
        ui->stackedWidget->setCurrentIndex(3);
        nurse1->update1();
    }
    else if (str == "medicine_btn")
    {
        ui->stackedWidget->setCurrentIndex(4);
        medicine1->update1();
    }
}


void primary::on_back_clicked()
{
    emit this->back();
}



