#ifndef MAINGRAPH_H
#define MAINGRAPH_H

#include <QMainWindow>
#include <QDebug>

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

    void on_btnZoomIn_clicked();

private:
    Ui::mainGraph *ui;
    void debug_printOutFile(QString);
    void debug_checkRunTime(QString);
    void plotFileAll(QString); //Deprecated, see plotFromFileAll
    void plotFile(QString, QString); //Deprecated, see plotFromFile
    void plotFromFileAll(QString);
    void plotFromFile(QString, QString);
    void plotFromFileReadSpeed(QString);
    void initGraph();
};

#endif // MAINGRAPH_H
