#ifndef SOLUTION_H
#define SOLUTION_H
#include <QPointF>
#include <QVector>
#include <QtAlgorithms>
#include <QtMath>

struct RSZO {
    double x, y, d;
    RSZO(){};
    RSZO (double _x, double _y, double _d): x(_x), y(_y), d(_d){};
};

struct PRO {
    double x, y, r;
    PRO(){};
    PRO (double _x, double _y, double _r): x(_x), y(_y), r(_r){};
};

struct Target {
    double x, y;
    Target(){};
    Target (double _x, double _y): x(_x), y(_y){};
};

struct Liner {
    QPointF a, b;
    Liner(){};
    Liner(QPointF _a, QPointF _b): a(_a), b(_b){};
};

class Solution
{
public:
    Solution();
    static void solve(QVector <RSZO> _rszo, QVector <PRO> _pro, QVector <Target> _tar);
    static bool circle(RSZO a, PRO c, Target b);
    static QVector <Liner> retall ();
    static QVector <Liner> retopt ();
    static void optimum (int num, int res, QVector <int> &used, QVector  <QVector <bool>> &matr);
private:
    static int best;
    static QVector <QVector <bool>> matrix;
    static QVector <int> ans;
    static QVector <RSZO> rszo;
    static QVector <PRO> pro;
    static QVector <Target> tar;
};

#endif // SOLUTION_H
