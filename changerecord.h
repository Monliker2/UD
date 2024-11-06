#ifndef CHANGERECORD_H
#define CHANGERECORD_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class ChangeRecord;
}

class ChangeRecord : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeRecord(QWidget *parent = nullptr);
    ~ChangeRecord();

private slots:
    void obr_sendID(int);

    void on_pushButton_clicked();

signals:
    void refreshTable();

private:
    Ui::ChangeRecord *ui;
};

#endif // CHANGERECORD_H
