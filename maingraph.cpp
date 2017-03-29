#include "maingraph.h"
#include "ui_maingraph.h"



mainGraph::mainGraph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainGraph)
{
    ui->setupUi(this);
    initGraph();
}

mainGraph::~mainGraph()
{
    delete ui;
}


/*
 * Debugging purposes: outputLine
 */
void mainGraph::debug_printOutFile(QString filepath) {
    QFile inputFile(filepath);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          qDebug() << line;

       }
       inputFile.close();
    } else {
        qDebug() << "Fail opening file";
    }
}

/*
 * Debugging purposes: checkTime
 */
void mainGraph::debug_checkRunTime(QString filepath) {
    QTime T1;
    T1.start();
    QFile inputFile(filepath);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
       }
       inputFile.close();
       qDebug("Time elapsed: %d ms", T1.elapsed());
    } else {
        qDebug() << "Fail opening file";
    }
}


/*
 * Deprecated: Reads the filepath and plots the graph (All)
 */

void mainGraph::plotFileAll(QString filepath) {
    QFile inputFile(filepath);
    QVector<double> x;
    QVector<double> y;
    //Initiates the graph
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList xy = line.split(',');
          if (xy[5].compare("all") == 0) {
              QDateTime qdt = qdt.fromString(xy[0], "yyyy-MM-ddThh:mm:ssZ");
              x.append(qdt.toTime_t());
              y.append(xy[7].toDouble());
          }
       }
       ui->graph->graph(0)->setData(x,y);
       ui->graph->rescaleAxes();
       ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
       ui->graph->yAxis->setRange(0, 0.05);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}

/*
 * Deprecated: Reads the filepath and plots the graph (File). Reads original PerfData
 */

void mainGraph::plotFile(QString filepath, QString fileName) {
    int count = 0;
    QFile inputFile(filepath);
    QVector<double> x;
    QVector<double> y;
    //Initiates the graph
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          qDebug() << filepath;

          QStringList xy = line.split(',');
          if (xy[6].compare(fileName) == 0) {
              count++;
              QDateTime qdt = qdt.fromString(xy[0], "yyyy-MM-ddThh:mm:ssZ");
              x.append(qdt.toTime_t());
              y.append(xy[7].toDouble());
          }
       }
       ui->graph->legend->setVisible(true);
       ui->graph->graph(0)->setName(fileName + " reads: " + QString::number(count));
       ui->graph->graph(0)->setData(x,y);
       ui->graph->rescaleAxes();
       ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
       ui->graph->yAxis->setRange(0, 0.0010);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}

/*
 * Reads the filepath and plots the graph (File)
 */

void mainGraph::plotFromFile(QString filepath, QString fileName) {
    int count = 0;
    QFile inputFile(filepath);
    QVector<double> x;
    QVector<double> y;
    //Initiates the graph
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList xy = line.split(',');
          if (xy[6].compare(fileName) == 0) {
              count++;
              //qDebug() << xy[].toDouble();
              x.append(xy[8].toDouble());
              y.append(xy[7].toDouble());
          }
       }
       ui->graph->legend->setVisible(true);
       ui->graph->graph(0)->setName(fileName + " reads: " + QString::number(count));
       ui->graph->graph(0)->setData(x,y);
       ui->graph->rescaleAxes();
       ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
       //ui->graph->yAxis->setRange(0, 0.0010);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}


/*
 * Reads the filepath and plots the graph (All)
 */

void mainGraph::plotFromFileAll(QString filepath) {
    int count = 0;
    QFile inputFile(filepath);
    QVector<double> x;
    QVector<double> y;
    //Initiates the graph
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList xy = line.split(',');
          if (xy[6].compare("jobtotal") == 0) {
              count++;
              x.append(xy[8].toDouble());
              y.append(xy[7].toDouble());
          }
       }

       //Legend Setup
       ui->graph->legend->setVisible(true);
       ui->graph->graph(0)->setName("Reads: " + QString::number(count));

       ui->graph->graph(0)->setData(x,y);

       //Tweak axes
       ui->graph->rescaleAxes();
       ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
       //ui->graph->yAxis->setRange(0, 0.0010);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}

void mainGraph::plotFromFileReadSpeed(QString filepath) {
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    fixedTicker->setTickStep(250);
    ui->graph->xAxis->setTicker(fixedTicker);

    int jobPerSec = 0;
    int readCount = 0;
    QFile inputFile(filepath);
    QVector<double> x;
    QVector<double> y;

    //Comparator: checks if timestamp has changed
    QString comp = "";

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       //Main read line-by-line loop
       while (!in.atEnd())
       {

          QString line = in.readLine();
          QStringList xy = line.split(',');

          //Assumes there is a one to one correspondance between jobtotal-line and a job (ID)
          if (xy[6].compare("jobtotal") == 0) {
              readCount++;
              if (xy[0].compare(comp) != 0) {
                  x.append(readCount);
                  y.append(jobPerSec);
                  comp = xy[0];
                  jobPerSec = 1;
              } else {
                  jobPerSec++;
              }
          }
       }
       ui->graph->legend->setVisible(true);
       ui->graph->graph(0)->setName("Jobs read: " + QString::number(readCount));
       ui->graph->graph(0)->setData(x,y);
       ui->graph->rescaleAxes();
       ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
       //ui->graph->yAxis->setRange(0, 0.0010);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}



void mainGraph::on_uploadBtn_clicked()
{
    QString filepath = QDir::homePath() + ui->pathLineEdit->text();
    if (ui->radioBtnAll->isChecked()) {
         plotFromFileReadSpeed(filepath);
    } else {
        QString filename = ui->nameLineEdit->text();
        plotFromFile(filepath, filename);
    }
}

void mainGraph::initGraph()
{
    ui->graph->addGraph();
    ui->graph->xAxis->setRange(QDateTime::currentDateTime().toTime_t(), QDateTime::currentDateTime().toTime_t() + 3600*24*10);
    ui->graph->yAxis->setRange(0, 0.01);
    ui->graph->replot();
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss:zzz");
    ui->graph->xAxis->setTicker(dateTicker);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->radioBtnAll->setChecked(true);
}

void mainGraph::on_radioBtnAll_toggled(bool checked)
{
    ui->nameLineEdit->setDisabled(checked);
}


void mainGraph::on_btnZoomIn_clicked()
{

}
