#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuReq(QPoint)));
    fl=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
 logwin = new Login();
 connect(logwin, &Login::refreshComboBox, this, &MainWindow::refresh_comboBox);
 logwin->show();
}


void MainWindow::on_Print_data_clicked()
{
        fl=1;
        //model = new QSqlTableModel();
        //model->setTable("product");
        //model->select();

        model = new QSqlQueryModel();
        model->setQuery("SELECT ID,Name,Category,PicAddr,FORMAT(dat, 'dd.MM.yyyy') FROM product");


        model->setHeaderData(0, Qt::Horizontal,"Номер");
        model->setHeaderData(1, Qt::Horizontal,"Название");
        model->setHeaderData(2, Qt::Horizontal,"Категория");
        model->setHeaderData(3, Qt::Horizontal,"Картинка");
        model->setHeaderData(4, Qt::Horizontal,"Дата");


        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->show();
}


void MainWindow::on_pushButton_clicked()
{
    dopzap = new AddRecord();
    connect(dopzap, SIGNAL(refresh_table()), this, SLOT(obr_ref_tab()));
    dopzap->show();
}

void MainWindow::obr_ref_tab(){
    on_Print_data_clicked();
}




void MainWindow::on_pushButton_2_clicked()
{
    anoTable = new AnotherTable();
    anoTable->show();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_num = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();

    ui->lineEdit->setText(QString::number(temp_num));

    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT Name, PicAddr, FORMAT(dat, 'dd.MM.yyyy'), Category FROM product WHERE ID=:id");
    query->bindValue(":id",temp_num);

    if(query->exec()){
        query->next();
        ui->lineEdit_2->setText(query->value(0).toString());


        ui->comboBox->setCurrentIndex(ui->comboBox->findText(query->value(3).toString()));

        ui->lineEdit_4->setText(query->value(1).toString());

        ui->dateEdit->setDate(QDate::fromString(query->value(2).toString(),"dd.MM.yyyy"));


        QSize maxSize = ui->label_4->maximumSize();
        QPixmap scaledPixmap = QPixmap(query->value(1).toString()).scaled(maxSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        ui->label_4->setScaledContents(true);
        ui->label_4->setPixmap(scaledPixmap);
    }
}


void MainWindow::on_change_button_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("UPDATE product SET Name=:name, Category=:category, PicAddr=:pic, dat=:dat WHERE ID=:id");
    query->bindValue(":name", ui->lineEdit_2->text());
    //query->bindValue(":category", ui->lineEdit_3->text());
    query->bindValue(":category", ui->comboBox->itemText(catCombo));
    query->bindValue(":id", ui->lineEdit->text());
    query->bindValue(":pic", ui->lineEdit_4->text());


    query->bindValue(":dat", ui->dateEdit->date().toString("yyyy-MM-dd"));

    if(query->exec()){
        on_Print_data_clicked();
    }
}


void MainWindow::on_delete_button_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID=:id");
    query->bindValue(":id", ui->lineEdit->text());
    if(query->exec()){
        on_Print_data_clicked();
    }
}

void MainWindow::customMenuReq(QPoint pos){
    if(fl){
        QModelIndex index = ui->tableView->indexAt(pos);
        globId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
        QMenu* menu = new QMenu(this);
        QAction* change = new QAction("Изменить",this);
        connect(change, SIGNAL(triggered()),this,SLOT(change_zap()));

        QAction* delet = new QAction("Удалить",this);
        connect(delet, SIGNAL(triggered()),this,SLOT(del_zap()));


        menu->addAction(change);
        menu->addAction(delet);
        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));

    }
}
void MainWindow::del_zap(){
    QSqlQuery* query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID=:id");
    query->bindValue(":id", globId);
    if(query->exec()){
        on_Print_data_clicked();
    }
}

void MainWindow::change_zap(){
    changeRec = new ChangeRecord();
    connect(changeRec, &ChangeRecord::refreshTable, this, &MainWindow::obr_refreshTable);

    connect(this,SIGNAL(sendID(int)),changeRec, SLOT(obr_sendID(int)));

    emit sendID(globId);
    changeRec->show();

    disconnect(this,SIGNAL(sendID(int)),changeRec, SLOT(obr_sendID(int)));
}

void MainWindow::obr_refreshTable(){
    on_Print_data_clicked();
}


void MainWindow::on_pushButton_3_clicked()
{
    pr = new Print();
    pr->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    QString str;

    str.append("<html><head></head><body><center>"+QString("Пример создания отчёта"));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("Номер")+"</td>");
    str.append("<td>"+QString("Название")+"</td>");
    str.append("<td>"+QString("Категория")+"</td>");
    str.append("<td>"+QString("Картинка")+"</td>");
    str.append("<td>"+QString("Дата")+"</td></tr>");

    QSqlQuery* query = new QSqlQuery();
    //query->exec("Select ID, Name, Category FROM product");
    query->exec("SELECT ID, Name, Category, PicAddr, FORMAT(dat, 'dd.MM.yyyy') FROM product");
    //qDebug()<<"1234"<< query->value(4).toString();
    while(query->next()){
        str.append("<tr>");
        str.append("<td>"+query->value(0).toString()+"</td>");
        str.append("<td>"+query->value(1).toString()+"</td>");
        str.append("<td>"+query->value(2).toString()+"</td>");
        str.append("<td>"+query->value(3).toString()+"</td>");
        str.append("<td>"+query->value(4).toString()+"</td>");

        str.append("</tr>");
    }
    str.append("</table></center></body></html>");


    QPrinter printer;
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QString path = QFileDialog::getSaveFileName(0,"Сохранить в PDF","Отчёт","PDF(*.pdf)");
    if(path.isEmpty()) return;

    printer.setOutputFileName(path);
    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&printer);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    catCombo = index;
}

void MainWindow::refresh_comboBox(){
    QSqlQuery* query = new QSqlQuery();
    query->exec("SELECT name FROM category");
    while(query->next()){
        ui->comboBox->addItem(query->value(0).toString());
    }

    catCombo = 0;
}


void MainWindow::on_action_2_triggered()
{
    PrintGR = new PrintGraph();
    PrintGR->show();
}


void MainWindow::on_toolButton_clicked()
{
    ui->lineEdit_4->setText(QFileDialog::getOpenFileName(0, "Открыть изображение","./","*.jpg *.jpeg *.png *.bmp"));
}

