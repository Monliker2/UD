#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QWidget>

namespace Ui {
class AddRecord;
}

class AddRecord : public QWidget
{
    Q_OBJECT

public:
    explicit AddRecord(QWidget *parent = nullptr);
    ~AddRecord();

private:
    Ui::AddRecord *ui;
};

#endif // ADDRECORD_H
