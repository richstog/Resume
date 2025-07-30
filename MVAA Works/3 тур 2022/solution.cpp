#pragma once
#include "solution.h"
int Solution::best;
QVector <QVector <bool>> Solution::matrix;
QVector <int> Solution::ans;
QVector <RSZO> Solution::rszo;
QVector <PRO> Solution::pro;
QVector <Target> Solution::tar;

Solution::Solution()
{

}

void Solution::solve(QVector<RSZO> _rszo, QVector<PRO> _pro, QVector<Target> _tar)
{
    rszo = _rszo;
    pro = _pro;
    tar = _tar;
    best = 0;
    QVector <QVector <bool>> matr (rszo.size(), QVector <bool> (tar.size(), 0));
    for (int i(0); i<rszo.size(); i++)
    {
        for (int j(0); j<tar.size(); j++)
        {
            double dist = sqrt (pow (rszo[i].x - tar[j].x, 2) + pow (rszo[i].y - tar[j].y, 2));
            if (dist <= rszo[i].d)
            {
                matr[i][j] = true;
                for (int k(0); k<pro.size(); k++)
                {
                    if (circle(rszo[i], pro[k], tar[j]))
                    {
                        matr[i][j] = false;
                        break;
                    }
                }
            }
        }
    }

    QVector <int> used (tar.size(), -1);
    ans = used;
    optimum(0, 0, used, matr);
    matrix = matr;
}

bool Solution::circle(RSZO a, PRO c, Target b)
{
    double k = ((b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y)) / (pow (b.x - a.x, 2) + pow (b.y - a.y, 2));
    double x = a.x + k * (b.x - a.x);
    double y = a.y + k * (b.y - a.y);

    double d = qSqrt(qPow(c.x - x, 2) + qPow(c.y - y, 2));
    if (d > c.r)
    {
        return false;
    }

    if (x <= qMax(a.x, b.x) && x >= qMin(a.x, b.x) && y <= qMax(a.y, b.y) && y >= qMin(a.y, b.y))
    {
        return true;
    }

    if (qSqrt(qPow(c.x - a.x, 2) + qPow(c.y - a.y, 2)) > c.r && qSqrt(qPow(c.x - b.x, 2) + qPow(c.y - b.y, 2)) > c.r)
    {
        return false;
    }
    return true;
}

QVector <Liner> Solution::retall ()
{
    QVector <Liner> v;
    for (int i(0); i<rszo.size(); i++)
    {
        for (int j(0); j<tar.size(); j++)
        {
            if (matrix[i][j] == 1)
            {
                v.push_back(Liner ({rszo[i].x, rszo[i].y}, {tar[j].x, tar[j].y}));
            }
        }
    }
    return v;
}

QVector <Liner> Solution::retopt ()
{
    QVector <Liner> v;
    for (int i(0); i<ans.size(); i++)
    {
        if (ans[i] != -1)
        {
            v.push_back(Liner ({rszo[ans[i]].x, rszo[ans[i]].y}, {tar[i].x, tar[i].y}));
        }
    }
    return v;
}

void Solution::optimum (int num, int res, QVector <int> &used, QVector  <QVector <bool>> &matr)
{
    if (num == rszo.size())
    {
        if (res > best)
        {
            best = res;
            ans = used;
        }
        return;
    }

    for (int i(0); i<tar.size(); i++)
    {
        if (used[i] == -1 && matr[num][i] == 1)
        {
            used[i] = num;
            optimum(num+1, res+1, used, matr);
            used[i] = -1;
        }
    }
    optimum(num+1, res, used, matr);
}
