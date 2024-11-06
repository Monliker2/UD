#include "anothertable.h"
#include "ui_anothertable.h"

AnotherTable::AnotherTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnotherTable)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    QShortcut *escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escShortcut, &QShortcut::activated, this, &QWidget::close);
}

AnotherTable::~AnotherTable()
{
    delete ui;
}

void AnotherTable::on_pushButton_clicked()
{
    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM "+ ui->lineEdit->text());


    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

