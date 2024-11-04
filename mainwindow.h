#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "ui_login.h"
#include "addrecord.h"
#include "ui_addrecord.h"
#include "anothertable.h"
#include "ui_anothertable.h"

//#include <QSqlTableModel>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    Login* logwin;
    AddRecord* dopzap;
    AnotherTable* anoTable;

private slots:
    void on_action_triggered();

    void on_Print_data_clicked();

    void on_pushButton_clicked();

    void obr_ref_tab();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    //QSqlTableModel* model;
    QSqlQueryModel* model;
};
#endif // MAINWINDOW_H
