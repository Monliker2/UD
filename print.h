#ifndef PRINT_H
#define PRINT_H

#include <QWidget>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QProcess>

#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Print;
}

class Print : public QWidget
{
    Q_OBJECT

public:
    explicit Print(QWidget *parent = nullptr);
    ~Print();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Print *ui;
};

#endif // PRINT_H
