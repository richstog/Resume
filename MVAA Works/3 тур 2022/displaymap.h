#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H

#include <QObject>
#include <QtCharts>

#include "solution.h"

class Displaymap : public QObject
{
    Q_OBJECT
public:
    explicit Displaymap(QObject *parent = nullptr);
    QChart *getChart();
    void drawChart(QVector < RSZO >, QVector < PRO >, QVector < Target >, QVector < Liner > = QVector < Liner > (), int color = 0);
    void clearSeries();
    int max_xy = 0;

public slots:
    void deleteChart(QPointF);

private:
    QChart *chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QScatterSeries *seriesRSZO;
    QScatterSeries *seriesPRO;
    QScatterSeries *seriesTAR;
    QVector < QScatterSeries* > v_scatter;
    QVector < QLineSeries* > v_line;

signals:
    void deleteSignal(QString, QPointF);
};

#endif // DISPLAYMAP_H
