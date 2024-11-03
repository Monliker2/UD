#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "ui_login.h"
#include <QSqlTableModel>

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
private slots:
    void on_action_triggered();

    void on_Print_data_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel* model;
};
#endif // MAINWINDOW_H
