#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>

namespace Ui {
class AddRecord;
}

class AddRecord : public QWidget
{
    Q_OBJECT

public:
    explicit AddRecord(QWidget *parent = nullptr);
    ~AddRecord();

private slots:
    void on_pushButton_clicked();

signals:
    void refresh_table();

private:
    Ui::AddRecord *ui;
};

#endif // ADDRECORD_H
