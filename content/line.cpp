#include "line.h"

Line::Line(QPoint p1,QPoint p2,QColor c): point1(p1),point2(p2),Shape(c){
    setShapeType(0);
}
Line::~Line(){
}
QPoint Line::p1()const{
    return point1;
}
QPoint Line::p2()const{
    return point2;
}
void Line::draw(QPainter *p){
    QPen pen(color,1,Qt::SolidLine);
    p->setPen(pen);
    p->drawLine(point1,point2); //绘制线条
}
void Line::save(QTextStream &out){
    out<<"0 "<<p1().x()<<" "<<p1().y()<<" "<<p2().x()<<" "<<p2().y()<<" ";
    out<<getColor()<<endl;
}
Shape* Line::read(QTextStream &in){
    int x1,y1,x2,y2;
    in>>x1>>y1>>x2>>y2;
    int colorNum;
    in>>colorNum;
    Line* p = new Line(QPoint(x1,y1),QPoint(x2,y2));
    p->setColor(colorNum);
    return p;
}
