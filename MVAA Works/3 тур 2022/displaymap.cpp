#pragma once
#include "displaymap.h"

Displaymap::Displaymap(QObject *parent) : QObject(parent)
{
    chart = new QChart();
    chart->legend()->hide();

    axisX = new QValueAxis();
    axisX->setRange(0, 0);
    axisX->setTickCount(10);
    axisX->setLabelsVisible(false);

    axisY = new QValueAxis();
    axisY->setRange(0, 0);
    axisY->setTickCount(10);
    axisY->setLabelsVisible(false);

    seriesRSZO = new QScatterSeries();
    seriesRSZO->setObjectName("RSZO");
    seriesRSZO->setBorderColor(Qt::red);
    seriesRSZO->setColor(Qt::red);
    seriesRSZO->setMarkerSize(10.0);

    seriesPRO = new QScatterSeries();
    seriesPRO->setObjectName("PRO");
    seriesPRO->setBorderColor(Qt::black);
    seriesPRO->setColor(Qt::black);
    seriesPRO->setMarkerSize(10.0);

    seriesTAR = new QScatterSeries();
    seriesTAR->setObjectName("TAR");
    seriesTAR->setBorderColor(Qt::blue);
    seriesTAR->setColor(Qt::blue);
    seriesTAR->setMarkerSize(10.0);

    chart->addSeries(seriesRSZO);
    chart->addSeries(seriesPRO);
    chart->addSeries(seriesTAR);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    seriesRSZO->attachAxis(axisX);
    seriesRSZO->attachAxis(axisY);
    seriesPRO->attachAxis(axisX);
    seriesPRO->attachAxis(axisY);
    seriesTAR->attachAxis(axisX);
    seriesTAR->attachAxis(axisY);

    connect(seriesRSZO, SIGNAL(clicked(QPointF)), this, SLOT(deleteChart(QPointF)));
    connect(seriesPRO, SIGNAL(clicked(QPointF)), this, SLOT(deleteChart(QPointF)));
    connect(seriesTAR, SIGNAL(clicked(QPointF)), this, SLOT(deleteChart(QPointF)));
}

QChart *Displaymap::getChart() {

    return chart;
}

void Displaymap::clearSeries() {

    chart->removeSeries(seriesRSZO);
    chart->removeSeries(seriesPRO);
    chart->removeSeries(seriesTAR);

    for(int i = 0; i < v_scatter.size(); i ++) {
        chart->removeSeries(v_scatter[i]);
    }

    for(int i = 0; i < v_line.size(); i ++) {
        chart->removeSeries(v_line[i]);
    }

    seriesRSZO->clear();
    seriesPRO->clear();
    seriesTAR->clear();
    v_scatter.clear();
    v_line.clear();

    max_xy = 0;
    axisX->setLabelsVisible(false);
    axisY->setLabelsVisible(false);
}

void Displaymap::drawChart(QVector < RSZO > v_rszo, QVector < PRO > v_pro, QVector < Target > v_tar, QVector < Liner > v_liner, int color) {

    clearSeries();
    if(v_rszo.size() == 0 && v_pro.size() == 0 && v_tar.size() == 0) return;

    for(int i = 0; i < v_rszo.size(); i ++) {

        seriesRSZO->append(v_rszo[i].x, v_rszo[i].y);
        int mx = qMax(v_rszo[i].x, v_rszo[i].y);
        max_xy = qMax(max_xy, mx);
    }

    for(int i = 0; i < v_pro.size(); i ++) {

        seriesPRO->append(v_pro[i].x, v_pro[i].y);
        int mx = qMax(v_pro[i].x, v_pro[i].y);
        max_xy = qMax(max_xy, mx);
    }

    for(int i = 0; i < v_tar.size(); i ++) {

        seriesTAR->append(v_tar[i].x, v_tar[i].y);
        int mx = qMax(v_tar[i].x, v_tar[i].y);
        max_xy = qMax(max_xy, mx);
    }

    for(int i = 0; i < v_pro.size(); i ++) {

        v_scatter.push_back(new QScatterSeries());
        v_scatter.back()->setBorderColor(Qt::green);
        v_scatter.back()->setColor(Qt::green);
        v_scatter.back()->setMarkerSize(chart->plotArea().height() / (max_xy + 1) * v_pro[i].r * 2);
        v_scatter.back()->append(v_pro[i].x, v_pro[i].y);

        chart->addSeries(v_scatter.back());
        v_scatter.back()->attachAxis(axisX);
        v_scatter.back()->attachAxis(axisY);
    }

    if(color == 1) {

        for(int i = 0; i < v_liner.size(); i ++) {

            v_line.push_back(new QLineSeries());
            v_line.back()->setColor(Qt::magenta);
            v_line.back()->append(v_liner[i].a);
            v_line.back()->append(v_liner[i].b);

            chart->addSeries(v_line.back());
            v_line.back()->attachAxis(axisX);
            v_line.back()->attachAxis(axisY);
        }
    }

    if(color == 2) {

        for(int i = 0; i < v_liner.size(); i ++) {

            v_line.push_back(new QLineSeries());
            v_line.back()->setColor(QColor(255, 170, 0));
            v_line.back()->append(v_liner[i].a);
            v_line.back()->append(v_liner[i].b);

            chart->addSeries(v_line.back());
            v_line.back()->attachAxis(axisX);
            v_line.back()->attachAxis(axisY);
        }
    }

    chart->addSeries(seriesRSZO);
    chart->addSeries(seriesPRO);
    chart->addSeries(seriesTAR);

    seriesRSZO->attachAxis(axisX);
    seriesRSZO->attachAxis(axisY);
    seriesPRO->attachAxis(axisX);
    seriesPRO->attachAxis(axisY);
    seriesTAR->attachAxis(axisX);
    seriesTAR->attachAxis(axisY);

    axisX->setRange(0, max_xy + 1);
    axisY->setRange(0, max_xy + 1);

    axisX->setLabelsVisible(true);
    axisY->setLabelsVisible(true);
}

void Displaymap::deleteChart(QPointF point) {

    QString name = sender()->objectName();
    emit deleteSignal(name, point);
}
