#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QShortcut>

#include <QFileDialog>

namespace Ui {
class AddRecord;
}

class AddRecord : public QWidget
{
    Q_OBJECT

public:
    explicit AddRecord(QWidget *parent = nullptr);
    ~AddRecord();

    QString ImgAddr;

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

signals:
    void refresh_table();

private:
    Ui::AddRecord *ui;
};

#endif // ADDRECORD_H
