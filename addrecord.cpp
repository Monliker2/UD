#include "addrecord.h"
#include "ui_addrecord.h"

AddRecord::AddRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRecord)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    QShortcut *escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escShortcut, &QShortcut::activated, this, &QWidget::close);

    ui->dateEdit->setDate(QDate::currentDate());
}

AddRecord::~AddRecord()
{
    delete ui;
}

void AddRecord::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("INSERT INTO product (Name, Category, PicAddr, dat) VALUES(:name, :category, :picAddr, :dat)");
    query->bindValue(":name", ui->lineEdit->text());
    query->bindValue(":category", ui->lineEdit_2->text());
    query->bindValue(":picAddr", ImgAddr);
    query->bindValue(":dat", ui->dateEdit->date().toString("yyyy-MM-dd"));

    QMessageBox* mess = new QMessageBox();

    if(!query->exec()){
        mess->setText("Ошибка выполнения запроса: " + query->lastError().text());
        mess->exec();
    }

    delete mess;
    emit refresh_table();
}


void AddRecord::on_toolButton_clicked()
{
    ImgAddr = QFileDialog::getOpenFileName(0, "Открыть изображение","./","*.jpg *.jpeg *.png *.bmp");

    QSize maxSize = ui->label_3->maximumSize();
    QPixmap scaledPixmap = QPixmap(ImgAddr).scaled(maxSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(scaledPixmap);
}

