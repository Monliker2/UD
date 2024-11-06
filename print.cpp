#include "print.h"
#include "ui_print.h"

Print::Print(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Print)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    QShortcut *escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escShortcut, &QShortcut::activated, this, &QWidget::close);
}

Print::~Print()
{
    delete ui;
}

void Print::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(0,"Выберите файл", "./", "*.html"));
}


void Print::on_pushButton_clicked()
{
    QFile* file = new QFile();
    file->setFileName(ui->lineEdit->text());
    file->open(QIODevice::WriteOnly);

    QTextStream in(file);

    in<<"<html><head></head><body><center>"+QString("Пример создания отчёта");
    in<<"<table border=1><tr>";
    in<<"<td>"+QString("Номер")+"</td>";
    in<<"<td>"+QString("Название")+"</td>";
    in<<"<td>"+QString("Категория")+"</td></tr>";

    QSqlQuery* query = new QSqlQuery();
    query->exec("Select * FROM product");

    while(query->next()){
        in<<"<tr>";
        in<<"<td>"+query->value(0).toString()+"</td>";
        in<<"<td>"+query->value(1).toString()+"</td>";
        in<<"<td>"+query->value(2).toString()+"</td>";
        in<<"</tr>";
    }
    in<<"</table></center></body></html>";
    file->close();

    QProcess *process = new QProcess;
    QStringList args;
    args << "-f" << "docx" << ui->lineEdit->text() << "-o" << QFileInfo(ui->lineEdit->text()).absolutePath();

    process->start("unoconv", args);
    process->waitForFinished();

    args.clear();
    args<<"--writer"<<QFileInfo(ui->lineEdit->text()).absolutePath()+"/"+QFileInfo(ui->lineEdit->text()).baseName()+".docx";

    process->start("libreoffice", args);
    process->waitForFinished();
    process->close();

}

