#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "ui_login.h"

#include "addrecord.h"
#include "ui_addrecord.h"

#include "anothertable.h"
#include "ui_anothertable.h"

#include "changerecord.h"
#include "ui_changerecord.h"

#include "print.h"
#include "ui_print.h"

#include "printgraph.h"
#include "ui_printgraph.h"

#include <QSqlQueryModel>

#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QDate>

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

    ChangeRecord* changeRec;

    AnotherTable* anoTable;
    int globId;
    bool fl;

    Print* pr;

    int catCombo;

    PrintGraph* PrintGR;

private slots:
    void on_action_triggered();

    void on_Print_data_clicked();

    void on_pushButton_clicked();

    void obr_ref_tab();
    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_change_button_clicked();

    void on_delete_button_clicked();

    void customMenuReq(QPoint);

    void del_zap();

    void change_zap();

    void obr_refreshTable();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void refresh_comboBox();

    void on_action_2_triggered();

    void on_toolButton_clicked();

signals:
    void sendID(int);


private:
    Ui::MainWindow *ui;
    //QSqlTableModel* model;
    QSqlQueryModel* model;
};
#endif // MAINWINDOW_H
