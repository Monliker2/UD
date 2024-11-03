#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->lineEdit->setEchoMode(QLineEdit::Password);
    mes = new QMessageBox();
}

Login::~Login()
{

    delete ui;
}

void Login::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QTDS");

    db.setHostName(ui->lineEdit_2->text());
    db.setPort(ui->lineEdit_5->text().toInt());
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit->text());
    db.setDatabaseName(ui->lineEdit_4->text());


    if(db.open()){
        mes->setText("Соединилось");
    }
    else{
        mes->setText("Не соединилось");
    }

    mes->show();
}

