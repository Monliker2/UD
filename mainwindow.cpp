#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
 logwin = new Login();
 logwin->show();
}


void MainWindow::on_Print_data_clicked()
{
    //model = new QSqlTableModel();
    //model->setTable("product");
    //model->select();

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM product");


    model->setHeaderData(0, Qt::Horizontal,"Номер");
    model->setHeaderData(1, Qt::Horizontal,"Название");
    model->setHeaderData(2, Qt::Horizontal,"Категория");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}

