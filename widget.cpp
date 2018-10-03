#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
//    QMessageBox::information(this, "Title here", "Hello");
//    ui->label->setText("asdf");
//    ui->label->setText(ui->label->text() + "asdf\n");
//    (*((*ui).label)).setText("asdf");
}

void Widget::on_pushButton_2_clicked()
{

}
