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
