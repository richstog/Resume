#ifndef CANVAS_H
#define CANVAS_H

#include <QChartView>

#include <QChart>
#include <QtCharts>
#include <QValueAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include <QGraphicsTextItem>

#include <QRect>

#include <QMenu>
#include <QAction>

#include <QFile>

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <QtWidgets>

#include <addcity.h>
#include <addroads.h>
#include <result.h>


using namespace std;

class Canvas : public QChartView
{
public:
    Canvas();
    //---------------------------------------------------------------
    struct Town {
        QString name;
        int x;
        int y;
        int count;
    };
    struct VertexDistance {
        int vertex;
        int distance;

        VertexDistance(int v, int d) : vertex(v), distance(d) {}

        bool operator<(const VertexDistance &other) const {
            return distance > other.distance;
        }
    };

    QVector <Town> towns;
    QVector <QVector <int>> matrics;
    //---------------------------------------------------------------
    //---------------------------------------------------------------
    void addPointRoad(const QString name, const int x, const int y, const int count);
    void saveMatrics(const QVector <QVector <int>> mtrc);
    void exportData();
    void result();
    void clear();
    //---------------------------------------------------------------
private:
    //---------------------------------------------------------------
    QChart *chart {nullptr};
    QValueAxis *axisX {nullptr};
    QValueAxis *axisY {nullptr};
    //---------------------------------------------------------------
    //---------------------------------------------------------------
    void addContextMenu();
    void addMarkup();
    void addCity();
    void addRoad();
    void addRoadLines();
    void addLines();
    void drawLine(Town townFir, Town townSec);
    void drawCurPath(Town townFir, Town townSec);
    //---------------------------------------------------------------
    //---------------------------------------------------------------
     QVector <int> findShortPath(const QVector <QVector <int>> &matrcs, int start, int end);
    //---------------------------------------------------------------
};

#endif // CANVAS_H
