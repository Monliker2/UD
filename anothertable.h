#ifndef ANOTHERTABLE_H
#define ANOTHERTABLE_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QShortcut>

namespace Ui {
class AnotherTable;
}

class AnotherTable : public QWidget
{
    Q_OBJECT

public:
    explicit AnotherTable(QWidget *parent = nullptr);
    ~AnotherTable();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AnotherTable *ui;
    QSqlQueryModel* model;
};

#endif // ANOTHERTABLE_H
