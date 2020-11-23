#include "triangle.h"

Triangle::Triangle(QPoint p1,QPoint p2,QPoint p3,QColor c): point1(p1),point2(p2),point3(p3),Shape(c){
    setShapeType(3);
}
Triangle::~Triangle(){
}
QPoint Triangle::p1()const{
    return point1;
}
QPoint Triangle::p2()const{
    return point2;
}
QPoint Triangle::p3()const{
    return point3;
}
void Triangle::draw(QPainter *p){
    QPen pen(color,1,Qt::SolidLine);
    p->setPen(pen);
    p->drawLine(point1,point2);
    p->drawLine(point2,point3);
    p->drawLine(point3,point1);
}
void Triangle::save(QTextStream &out){
    out<<"3 "<<p1().x()<<" "<<p1().y()<<" "<<p2().x()<<" "<<p2().y()<<" "<<p3().x()<<" "<<p3().y()<<" ";
    out<<getColor()<<endl;
}
Shape* Triangle::read(QTextStream &in){
    int x1,y1,x2,y2,x3,y3;
    in>>x1>>y1>>x2>>y2>>x3>>y3;
    int colorNum;
    in>>colorNum;
    Triangle *p = new Triangle(QPoint(x1,y1),QPoint(x2,y2),QPoint(x3,y3));
    p->setColor(colorNum);
    return p;
}
