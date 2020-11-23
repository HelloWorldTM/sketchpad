#ifndef SHAPE_H
#define SHAPE_H
#include<QColor>
#include<QPainter>
#include<QTextStream>
class Shape{
public:
    Shape(QColor c);
    int getColor()const;
    void setColor(int colorType);
    void setColor(QColor c);
    void setShapeType(int m);
    int getShapeType()const;
    virtual void draw(QPainter *p)=0;
    virtual void save(QTextStream& s)=0;
    virtual ~Shape(){} 
protected:
    int shapeType;
    QColor color;
};

#endif // SHAPE_H
