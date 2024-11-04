#include "addrecord.h"
#include "ui_addrecord.h"

AddRecord::AddRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRecord)
{
    ui->setupUi(this);
}

AddRecord::~AddRecord()
{
    delete ui;
}

void AddRecord::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("INSERT INTO product (Name,Category) VALUES(:name,:category)");
    query->bindValue(":name", ui->lineEdit->text());
    query->bindValue(":category", ui->lineEdit_2->text());

    QMessageBox* mess = new QMessageBox();

    if(!query->exec()){
        mess->setText("Не верный запрос");
        mess->exec();
    }

    delete mess;
    emit refresh_table();
}

