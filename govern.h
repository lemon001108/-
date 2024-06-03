#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>
#include <QMainWindow>


namespace Ui {
class govern;
}

class govern : public QWidget
{
    Q_OBJECT

public:
    explicit govern(QWidget *parent = nullptr);
    ~govern();

signals:
    void back();

private:
    Ui::govern *ui;
};

#endif // DOCTOR_H
