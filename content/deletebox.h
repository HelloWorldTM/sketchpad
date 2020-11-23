#ifndef DELETEBOX_H
#define DELETEBOX_H

#include"shape.h"
class Deletebox : public Shape{
private:
    QPoint point1;
    QPoint point2;
public:
    Deletebox(QPoint p1,QPoint p2,QColor c=Qt::black);
    QPoint topLeft()const;
    QPoint bottomRight()const;
    virtual void draw(QPainter *p);
    virtual void save(QTextStream& out);
    static Shape* read(QTextStream& in);
    ~Deletebox();
};



#endif // DELETEBOX_H
