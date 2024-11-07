#include "changerecord.h"
#include "ui_changerecord.h"

ChangeRecord::ChangeRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeRecord)
{
    ui->setupUi(this);


}

ChangeRecord::~ChangeRecord()
{
    delete ui;
}

void ChangeRecord::obr_sendID(int a){
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT Name, Category, PicAddr FROM product WHERE ID=:id");
    query->bindValue(":id", a);


    if(query->exec()){
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        ui->lineEdit_2->setText(query->value(1).toString());
        ui->lineEdit_4->setText(query->value(2).toString());
        ui->lineEdit_3->setText(QString::number(a));
    }
}

void ChangeRecord::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("UPDATE product SET Name=?, Category=?, PicAddr=? WHERE ID=?");
    query->bindValue(0, ui->lineEdit->text());
    query->bindValue(1, ui->lineEdit_2->text());
    query->bindValue(2, ui->lineEdit_4->text());
    query->bindValue(3, ui->lineEdit_3->text().toInt());

    if(query->exec()){
        emit refreshTable();
        delete this;
    }
}

