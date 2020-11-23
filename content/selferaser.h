#ifndef SELFERASER_H
#define SELFERASER_H
#include<QPoint>
#include<QList>
#include"shape.h"

class Selferaser:public Shape{
public:
    Selferaser(QList<QPoint> &pl,QColor c=Qt::black);
    int pointCount();
    virtual void draw(QPainter *p);
    virtual void save(QTextStream& out);
    static Shape* read(QTextStream& in);
    ~Selferaser();
private:
    QList<QPoint> point_list;
};



#endif // SELFERASER_H
