#ifndef MAINGRAPH_H
#define MAINGRAPH_H

#include <QMainWindow>
#include <QDebug>
#include "qcustomplot.h"

namespace Ui {
class mainGraph;
}

class mainGraph : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainGraph(QWidget *parent = 0);
    ~mainGraph();

private slots:
    void on_uploadBtn_clicked();
    void on_radioBtnAll_toggled(bool checked);
    void on_btnAddGraph_clicked();
    void on_btnRmvGraph_clicked();

    void on_btnSave_clicked();

    void on_btnYzoom_clicked();

    void on_btnXzoom_clicked();

private:
    Ui::mainGraph *ui;
    int nbrOfGraphs;
    void initGraph();
    int getCurrentGraphNbr();
    QString graphTag(QString);

    //Scatter styles
    QVector<QCPScatterStyle::ScatterShape> shapes;
    int styleIndex;
    QPen pen;

    QPen getPen();
    QCPScatterStyle::ScatterShape getScatterStyle();

    //Debug
    void debug_printOutFile(QString);
    void debug_checkRunTime(QString);

    //Plot functions
    void plotFromFileAll(QString);
    void plotFromFile(QString, QString);
    void plotFromFileReadSpeed(QString);





};

#endif // MAINGRAPH_H
