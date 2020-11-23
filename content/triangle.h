#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QPoint>
#include "shape.h"

class Triangle:public Shape{
public:
    Triangle(QPoint p1,QPoint p2,QPoint p3,QColor c=Qt::black);
    QPoint p1()const;
    QPoint p2()const;
    QPoint p3()const;
    virtual void draw(QPainter *p);
    virtual void save(QTextStream& out);
    static Shape* read(QTextStream& in);
    ~Triangle();
private:
    QPoint point1;
    QPoint point2;
    QPoint point3;
};




#endif // TRIANGLE_H
