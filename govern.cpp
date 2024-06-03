#include "govern.h"
#include "ui_govern.h"

govern::govern(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::govern)
{
    ui->setupUi(this);
}

govern::~govern()
{
    delete ui;
}
