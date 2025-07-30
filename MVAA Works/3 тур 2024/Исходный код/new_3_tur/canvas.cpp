#include "canvas.h"

Canvas::Canvas()
{
    //-----------------------------------------------------------------------------------
    chart = new QChart();
    chart->legend()->hide();
    chart->setMargins(QMargins(0, 0, 0, 0));
    setChart(chart);
    chart->resize(size());

    addContextMenu();
    addMarkup();
    //-----------------------------------------------------------------------------------
}

void Canvas::addPointRoad(const QString name, const int x, const int y, const int count)
{
    Town town;
    town.name = name;
    town.x = x;
    town.y = y;
    town.count = count;
    towns.push_back(town);
}

void Canvas::saveMatrics(const QVector<QVector<int>> mtrc)
{
    matrics = mtrc;

    addRoadLines();
    addLines();
}

void Canvas::exportData()
{
    QString fileName(QFileDialog::getSaveFileName(this, "Сохранить файл", QDir::currentPath(), "*.txt"));
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        out << towns.size() << Qt::endl;
        for (const Town town : towns) {
            out << town.name << Qt::endl;
            out << town.x << Qt::endl;
            out << town.y << Qt::endl;
            out << town.count << Qt::endl;
        }
        out << Qt::endl;

        for (int i(0); i < matrics.size(); i ++) {
            for (int j(0); j < matrics[i].size(); j ++) {
                out << matrics[i][j];
            }
            if (i + 1 < matrics.size()) out << Qt::endl;
        }
        file.close();
    }
}

void Canvas::result()
{
    QStringList list;
    for (int i(0); i < towns.size(); i ++) list.push_back(towns[i].name);

    Result result(list, towns.size());
    if (result.exec()) {
        auto data(result.result());

        QVector <int> shortPath(findShortPath(matrics, data.a, data.b));

        for (int i(0); i < shortPath.size() - 1; i ++) drawCurPath(towns[shortPath[i]], towns[shortPath[i + 1]]);

        addLines();
    }
}

void Canvas::clear()
{
    chart->removeAllSeries();
    towns.clear();
    matrics.clear();

}

void Canvas::addContextMenu()
{
    QMenu *menu = new QMenu;

    QAction *addRoadAct = new QAction("Добавить дорогу");
    menu->addAction(addRoadAct);
    connect(addRoadAct, &QAction::triggered, this, &Canvas::addRoad);

    QAction *addCityAct = new QAction("Добавить город");
    menu->addAction(addCityAct);
    connect(addCityAct, &QAction::triggered, this, &Canvas::addCity);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &Canvas::customContextMenuRequested, this, [=](){
        menu->move(cursor().pos());
        menu->exec();
    });
}

void Canvas::addMarkup()
{
    axisX = new QValueAxis;
    axisX->setRange(0, 500);
    axisX->setTickCount(10);
    axisX->setLabelsVisible(false);

    axisY = new QValueAxis;
    axisY->setRange(0, 500);
    axisY->setTickCount(10);
    axisY->setLabelsVisible(false);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
}

void Canvas::addCity()
{
    AddCity add;
    if (add.exec()) {
        auto data(add.value());

        Town town;
        town.name = data.name;
        town.x = data.x;
        town.y = data.y;
        town.count = data.count;
        towns.push_back(town);

        for (int i(0); i < matrics.size(); i ++) matrics[i].push_back(0);

        QScatterSeries *series = new QScatterSeries();

        if (data.count >= 1 && data.count <= 500000) series->setMarkerSize(15);
        else if (data.count >= 500001 && data.count <= 1000000) series->setMarkerSize(25);
        else series->setMarkerSize(40);

        series->append(data.x, data.y);

        chart->addSeries(series);

        series->attachAxis(axisX);
        series->attachAxis(axisY);

        QPen pen;
        pen.setColor(Qt::black);
        pen.setCosmetic(true);
        pen.setWidth(2);
        series->setPen(pen);

        QBrush brush;
        if (data.count >= 1 && data.count <= 500000) brush.setColor(Qt::green);
        else if (data.count >= 500001 && data.count <= 1000000) brush.setColor(Qt::red);
        else brush.setColor(Qt::blue);
        brush.setStyle(Qt::SolidPattern);
        series->setBrush(brush);

        series->setPointLabelsVisible(true);
        series->setPointLabelsFormat(data.name);
    }
}

void Canvas::addRoad()
{
    QStringList list;
    for (int i(0); i < towns.size(); i ++) list.push_back(towns[i].name);

    AddRoads add(list);
    if (add.exec()) {
        auto data(add.value());

        QLineSeries *lineSeries = new QLineSeries; 
        lineSeries->append(towns[data.x].x, towns[data.x].y);
        lineSeries->append(towns[data.y].x, towns[data.y].y);

        QPen pen;
        pen.setColor(Qt::black);
        pen.setCosmetic(true);
        pen.setWidth(2);
        lineSeries->setPen(pen);
        QBrush brush;
        brush.setColor(Qt::green);
        brush.setStyle(Qt::Dense4Pattern);
        lineSeries->setBrush(brush);

        chart->addSeries(lineSeries);

        lineSeries->attachAxis(axisX);
        lineSeries->attachAxis(axisY);

        matrics[data.x][data.y] = 1;
        matrics[data.y][data.x] = 1;

        addLines();
    }
}

void Canvas::addRoadLines()
{
    for (int i(0); i < matrics.size(); i ++) {
        for (int j(0); j < matrics[i].size(); j ++) {
            if (matrics[i][j] >= 1 || matrics[j][i] >= 1) {
                drawLine(towns[i], towns[j]);
            }
        }
    }
}

void Canvas::addLines()
{
    for (int i(0); i < towns.size(); i ++) {
        QScatterSeries *series = new QScatterSeries;

        if (towns[i].count >= 1 && towns[i].count <= 500000) series->setMarkerSize(15);
        else if (towns[i].count >= 500001 && towns[i].count <= 1000000) series->setMarkerSize(25);
        else series->setMarkerSize(40);

        series->append(towns[i].x, towns[i].y);

        QPen pen;
        pen.setColor(Qt::black);
        pen.setCosmetic(true);
        pen.setWidth(2);
        series->setPen(pen);

        QBrush brush;
        if (towns[i].count >= 1 && towns[i].count <= 500000) brush.setColor(Qt::green);
        else if (towns[i].count >= 500001 && towns[i].count <= 1000000) brush.setColor(Qt::red);
        else brush.setColor(Qt::blue);
        brush.setStyle(Qt::SolidPattern);
        series->setBrush(brush);

        series->setPointLabelsVisible(true);
        series->setPointLabelsFormat(towns[i].name);

        chart->addSeries(series);

        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
}

void Canvas::drawLine(Town townFir, Town townSec)
{
    QLineSeries *line = new QLineSeries;
    line->append(townFir.x, townFir.y);
    line->append(townSec.x, townSec.y);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setCosmetic(true);
    pen.setWidth(2);
    line->setPen(pen);
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::Dense4Pattern);
    line->setBrush(brush);

    chart->addSeries(line);

    line->attachAxis(axisX);
    line->attachAxis(axisY);
}

void Canvas::drawCurPath(Town townFir, Town townSec)
{
    QLineSeries *line = new QLineSeries;
    line->append(townFir.x, townFir.y);
    line->append(townSec.x, townSec.y);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setCosmetic(true);
    pen.setWidth(4);
    line->setPen(pen);
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::Dense4Pattern);
    line->setBrush(brush);

    chart->addSeries(line);

    line->attachAxis(axisX);
    line->attachAxis(axisY);
}

QVector<int> Canvas::findShortPath(const QVector<QVector<int> > &matrcs, int start, int end)
{
    int numVert(matrcs.size());

    QVector <int> distance(numVert, numeric_limits <int>::max());
    QVector <bool> visited(numVert, false);
    QVector <int> predes(numVert, -1);

    priority_queue <VertexDistance> priorityQueue;

    distance[start] = 0;
    priorityQueue.push(VertexDistance(start, 0));

    while (!priorityQueue.empty()) {
        VertexDistance curVertex(priorityQueue.top());
        priorityQueue.pop();

        int u(curVertex.vertex);

        if (visited[u]) continue;

        visited[u] = true;

        if (u == end) {
            stack <int> path;
            int curr(end);
            while (curr != -1) {
                path.push(curr);
                curr = predes[curr];
            }

            vector <int> shortPath;
            while (!path.empty()) {
                shortPath.push_back(path.top());
                path.pop();
            }
            QVector <int> vec;
            for (int i(0); i < shortPath.size(); i ++) vec.push_back(shortPath[i]);

            return vec;
        }

        for (int v(0); v < numVert; v ++) {
            if (matrcs[u][v] != 0) {
                int newDist(distance[u] + matrcs[u][v]);

                if (newDist < distance[v]) {
                    distance[v] = newDist;
                    predes[v] = u;
                    priorityQueue.push(VertexDistance(v, newDist));
                }
            }
        }
    }

    return {};
}




