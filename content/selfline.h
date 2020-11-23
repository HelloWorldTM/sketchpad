#ifndef SELFLINE_H
#define SELFLINE_H
#include<QPoint>
#include<QList>
#include"shape.h"

class Selfline:public Shape{
public:
    Selfline(QList<QPoint> &pl,QColor c=Qt::black);
    int pointCount();
    virtual void draw(QPainter *p);
    virtual void save(QTextStream& out);
    static Shape* read(QTextStream& in);
    ~Selfline();
private:
    QList<QPoint> point_list;
};


#endif // SELFLINE_H
