#ifndef PRINTGRAPH_H
#define PRINTGRAPH_H

#include <QWidget>
#include <QSqlQuery>
#include "qcpdocumentobject.h"

namespace Ui {
class PrintGraph;
}

class PrintGraph : public QWidget
{
    Q_OBJECT

public:
    explicit PrintGraph(QWidget *parent = nullptr);
    ~PrintGraph();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PrintGraph *ui;
};

#endif // PRINTGRAPH_H
