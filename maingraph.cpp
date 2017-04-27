#include "maingraph.h"
#include "ui_maingraph.h"
#include "QDebug"



mainGraph::mainGraph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainGraph)
{
    ui->setupUi(this);
    initGraph();
    nbrOfGraphs = 0;

    //Set the different scatter styles
    shapes << QCPScatterStyle::ssCross;
    shapes << QCPScatterStyle::ssPlus;
    shapes << QCPScatterStyle::ssCircle;
    shapes << QCPScatterStyle::ssDisc;
    shapes << QCPScatterStyle::ssSquare;
    shapes << QCPScatterStyle::ssDiamond;
    shapes << QCPScatterStyle::ssStar;
    shapes << QCPScatterStyle::ssTriangle;
    shapes << QCPScatterStyle::ssTriangleInverted;
    shapes << QCPScatterStyle::ssCrossSquare;
    shapes << QCPScatterStyle::ssPlusSquare;
    shapes << QCPScatterStyle::ssCrossCircle;
    shapes << QCPScatterStyle::ssPlusCircle;
    shapes << QCPScatterStyle::ssPeace;
}

mainGraph::~mainGraph()
{
    delete ui;
}

void mainGraph::initGraph()
{
    ui->radioBtnAll->setChecked(true);
    ui->graph->yAxis->ticker()->setTickCount(10);
    ui->graph->xAxis->ticker()->setTickCount(10);
    ui->graph->xAxis->setRangeLower(0);
    ui->graph->yAxis->setRangeLower(0);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->graph->axisRect()->setRangeZoom(Qt::Vertical);
}

/*************************************************
 *      PLOTTING FUNCTIONS
 */

/*
 * Reads the filepath and plots the graph (extension)
 */

void mainGraph::plotFromFile(QString filepath, QString fileName) {
    int graphNbr = getCurrentGraphNbr();
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
       ui->graph->graph(graphNbr)->setName(fileName + " reads: " + QString::number(count));
       ui->graph->graph(graphNbr)->setData(x,y);
       ui->graph->graph(graphNbr)->setPen(getPen());
       ui->graph->rescaleAxes();
       ui->graph->graph(graphNbr)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(graphNbr)->setScatterStyle(getScatterStyle());
       //ui->graph->yAxis->setRange(0, 0.0010);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}


/*
 * Reads the filepath and plots the graph (not invoked)
 */

void mainGraph::plotFromFileAll(QString filepath) {
    int graphNbr = getCurrentGraphNbr();
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
       QString tag = filepath.split("/")[filepath.length()];
       ui->graph->graph(graphNbr)->setName(tag);
       ui->graph->graph(graphNbr)->setData(x,y);
       ui->graph->graph(graphNbr)->setPen(getPen());

       //Tweak axes
       ui->graph->rescaleAxes();
       ui->graph->graph(graphNbr)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(graphNbr)->setScatterStyle(getScatterStyle());
       //ui->graph->yAxis->setRange(0, 0.0010);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}


// Plots the average readspeed per job (All)

void mainGraph::plotFromFileReadSpeed(QString filepath) {
    int graphNbr = getCurrentGraphNbr();

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
       ui->graph->graph(graphNbr)->setName(graphTag(filepath));
       ui->graph->graph(graphNbr)->setData(x,y);
       ui->graph->graph(graphNbr)->setPen(getPen());
       ui->graph->rescaleAxes();

       ui->graph->graph(graphNbr)->setLineStyle(QCPGraph::lsNone);
       ui->graph->graph(graphNbr)->setScatterStyle(getScatterStyle());

       //ui->graph->yAxis->setRange(0, 0.0010);
       ui->graph->replot();
       qDebug() << "Execution finished";
    } else {
       qDebug() << "Fail opening file";
    }
    inputFile.close();
}

/*************************************************
 *      UI EVENTS
 */

void mainGraph::on_uploadBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open plotfile"),
                                                    QDir::homePath(),
                                                    "All files (*.*)");
    ui->pathLineEdit->setText(filename);
    if (ui->radioBtnAll->isChecked()) {
         plotFromFileReadSpeed(filename);
    }

    else {
        QString extension = ui->nameLineEdit->text();
        plotFromFile(filename, extension);
    }
}


void mainGraph::on_radioBtnAll_toggled(bool checked)
{
    ui->nameLineEdit->setDisabled(checked);
}

void mainGraph::on_btnAddGraph_clicked()
{
    ui->graph->addGraph();
    ui->listGraphs->addItem("Graph " + QString::number(nbrOfGraphs++));
}

void mainGraph::on_btnRmvGraph_clicked()
{
    getCurrentGraphNbr();
    QList<QListWidgetItem*> items = ui->listGraphs->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        ui->graph->removeGraph(getCurrentGraphNbr());
        delete ui->listGraphs->takeItem(ui->listGraphs->row(item));
    }
    ui->graph->replot();
}


void mainGraph::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save graph as PDF"), "",
            tr("All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->graph->savePdf(fileName);
    }
}

void mainGraph::on_btnYzoom_clicked()
{
    ui->graph->axisRect()->setRangeZoom(Qt::Vertical);
}

void mainGraph::on_btnXzoom_clicked()
{
    ui->graph->axisRect()->setRangeZoom(Qt::Horizontal);
}




/***************************************************
 *      PRIVATE HELP FUNCTIONS
 */

int mainGraph::getCurrentGraphNbr() {
    QList<QListWidgetItem*> items = ui->listGraphs->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        return item->text().split(" ")[1].toInt();
    }
}

QCPScatterStyle::ScatterShape mainGraph::getScatterStyle() {
    if (styleIndex == 11) {
        styleIndex = 0;
        return shapes.at(styleIndex);
    }
    return shapes.at(styleIndex++);
}

QPen mainGraph::getPen() {
    pen.setColor(QColor(qSin(styleIndex*0.3)*100+100, qSin(styleIndex*0.6+0.7)*100+100, qSin(styleIndex*0.4+0.6)*100+100));
    return pen;
}

QString mainGraph::graphTag(QString filepath) {
    QStringList tags = filepath.split("/");
    return "" + tags[tags.length()-3] + "/" + tags[tags.length()-2];
}

/*************************************************
 *      DEBUGGING FUNCTIONS
 */

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

