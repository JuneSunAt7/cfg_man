#ifndef CPU_USAGE_GRAPH_H
#define CPU_USAGE_GRAPH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QFile>
#include <QProcess>
#include <QPainterPath>
#include <QGraphicsTextItem>
class CPUUsageGraph : public QGraphicsView {
    Q_OBJECT

public:
    CPUUsageGraph(QWidget *parent = nullptr);
    ~CPUUsageGraph();

private slots:
    void updateGraph();

private:
    QGraphicsScene *scene;
    QTimer *timer;
    float getCPUUsage();
};

#endif // CPU_USAGE_GRAPH_H
