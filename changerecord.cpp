#include "changerecord.h"
#include "ui_changerecord.h"

ChangeRecord::ChangeRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeRecord)
{
    ui->setupUi(this);

    QSqlQuery* query = new QSqlQuery();
    query->exec("SELECT name FROM category");
    while(query->next()){
        ui->comboBox->addItem(query->value(0).toString());
    }

    catCombo = 0;


}

ChangeRecord::~ChangeRecord()
{
    delete ui;
}

void ChangeRecord::obr_sendID(int a){
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT Name, Category, PicAddr, FORMAT(dat, 'dd.MM.yyyy') FROM product WHERE ID=:id");
    query->bindValue(":id", a);


    if(query->exec()){
        query->next();
        ui->lineEdit->setText(query->value(0).toString());

        //ui->lineEdit_2->setText(query->value(1).toString());
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(query->value(1).toString()));


        ui->lineEdit_4->setText(query->value(2).toString());
        ui->lineEdit_3->setText(QString::number(a));

        ui->dateEdit->setDate(QDate::fromString(query->value(3).toString(),"dd.MM.yyyy"));
    }
}

void ChangeRecord::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("UPDATE product SET Name=?, Category=?, PicAddr=?, dat=? WHERE ID=?");
    query->bindValue(0, ui->lineEdit->text());

    //query->bindValue(1, ui->lineEdit_2->text());
    query->bindValue(1, ui->comboBox->itemText(catCombo));

    query->bindValue(2, ui->lineEdit_4->text());
    query->bindValue(4, ui->lineEdit_3->text().toInt());

    query->bindValue(3, ui->dateEdit->date().toString("yyyy-MM-dd"));

    if(query->exec()){
        emit refreshTable();
        delete this;
    }
}


void ChangeRecord::on_comboBox_currentIndexChanged(int index)
{
    catCombo = index;
}


void ChangeRecord::on_toolButton_clicked()
{
    ui->lineEdit_4->setText(QFileDialog::getOpenFileName(0, "Открыть изображение","./","*.jpg *.jpeg *.png *.bmp"));
}

