#include "mainwidget.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSql>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;
    //w.sqlconnect();
    w.show();
    return a.exec();
}
