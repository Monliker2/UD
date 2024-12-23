#ifndef CHANGERECORD_H
#define CHANGERECORD_H

#include <QWidget>
#include <QSqlQuery>
#include <QFileDialog>

namespace Ui {
class ChangeRecord;
}

class ChangeRecord : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeRecord(QWidget *parent = nullptr);
    ~ChangeRecord();

    int catCombo;

private slots:
    void obr_sendID(int);

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_toolButton_clicked();

signals:
    void refreshTable();

private:
    Ui::ChangeRecord *ui;
};

#endif // CHANGERECORD_H
