#include "login.h"
#include "ui_login.h"



void Login::saveSettings() {
    QSettings settings("Evgeny", "BD_App");

    settings.setValue("host", ui->lineEdit_2->text().isEmpty() ? settings.value("host") : ui->lineEdit_2->text());
    settings.setValue("port", ui->lineEdit_5->text().isEmpty() ? settings.value("port") : ui->lineEdit_5->text());
    settings.setValue("username", ui->lineEdit_3->text().isEmpty() ? settings.value("username") : ui->lineEdit_3->text());
    settings.setValue("BD_name", ui->lineEdit_4->text().isEmpty() ? settings.value("BD_name") : ui->lineEdit_4->text());
}


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // Создание валидатора для разрешения всех символов, кроме пробела
    QRegularExpression regExp("[^\\s]*");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);
    //5ui->lineEdit->setValidator(validator);
    ui->lineEdit_4->setValidator(validator);

    // Создание валидатора для разрешения только цифр
    QRegularExpression regExp1("\\d*");
    QRegularExpressionValidator *validator1 = new QRegularExpressionValidator(regExp1, this);
    ui->lineEdit_5->setValidator(validator1);

    //Загрузка настроек
    QSettings settings("Evgeny", "BD_App");
    ui->lineEdit_2->setText(settings.value("host").toString());
    ui->lineEdit_5->setText(settings.value("port").toString());
    ui->lineEdit_3->setText(settings.value("username").toString());
    ui->lineEdit_4->setText(settings.value("BD_name").toString());


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

    saveSettings();

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

