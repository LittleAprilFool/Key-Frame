#ifndef SHAPE_H
#define SHAPE_H

#include <QVector>
#include <QPoint>

class Shape
{
public:
    Shape();
    QVector<QPoint> point;
    void add_point(QPoint p);
    void undo();
    void clear();

};

#endif // SHAPE_H
