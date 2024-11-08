#include "printgraph.h"
#include "ui_printgraph.h"

PrintGraph::PrintGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintGraph)
{
    ui->setupUi(this);


    QCPDocumentObject* plotObjectHandler = new QCPDocumentObject(this);
    ui->textEdit->document()->documentLayout()->registerHandler(QCPDocumentObject::PlotTextFormat, plotObjectHandler);
    ui->textEdit->setVisible(false);

    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0,0,new QCPTextElement(ui->widget, "График выручки"));

    QVector<double> dx,dy;
    double minX=0, minY=0;
    double maxX=0,maxY=0;

    QSqlQuery* query = new QSqlQuery();

    if(query->exec("SELECT * FROM chart")){
        while(query->next()){
            minX =  query->value(0).toDouble() < minX ? query->value(0).toDouble():minX;
            minY =  query->value(1).toDouble() < minY ? query->value(1).toDouble():minY;
            maxX =  query->value(0).toDouble() > maxX ? query->value(0).toDouble():maxX;
            maxY =  query->value(1).toDouble() > maxY ? query->value(1).toDouble():maxY;

            dx<<query->value(0).toDouble();
            dy<<query->value(1).toDouble();

        }
        QCPBars* bar = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);

        bar->setName("Значение");
        bar->setBrush(QColor(255,0,0,255));
        bar->setData(dx,dy);
        bar->setWidth(0.2);

        ui->widget->xAxis->setLabel("Месяц");
        ui->widget->yAxis->setLabel("Выручка (млн)");

        ui->widget->xAxis->setRange(minX,maxX+0.2);
        ui->widget->yAxis->setRange(minY,maxY+1);

        QSharedPointer<QCPAxisTickerFixed> tic(new QCPAxisTickerFixed);
        tic->setTickStep(1);

        ui->widget->xAxis->setTicker(tic);
        ui->widget->yAxis->setTicker(tic);

        ui->widget->replot();
    }

    QTextCursor cur = ui->textEdit->textCursor();
    cur.insertText(QString(QChar::ObjectReplacementCharacter), QCPDocumentObject::generatePlotFormat(ui->widget, 480, 520));
}

PrintGraph::~PrintGraph()
{
    delete ui;
}

void PrintGraph::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(0,"Сохранить в PDF","./","*.pdf");
    if(!fileName.isEmpty()){
        QPrinter print;
        print.setFullPage(true);
        print.setPageOrientation(QPageLayout::Portrait);
        print.setOutputFormat(QPrinter::PdfFormat);
        print.setPageSize(QPageSize(QPageSize::A4));
        print.setOutputFileName(fileName);

        ui->textEdit->document()->print(&print);
    }
}

