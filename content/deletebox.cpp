#include "deletebox.h"

Deletebox::Deletebox(QPoint p1,QPoint p2,QColor c): point1(p1),point2(p2),Shape(c){
    setShapeType(5);
}
Deletebox::~Deletebox(){
}
QPoint Deletebox::topLeft()const{
    return point1;
}
QPoint Deletebox::bottomRight()const{
    return point2;
}
void Deletebox::draw(QPainter *p){
    QPen pen(color,1,Qt::SolidLine);
    p->setPen(pen);
    QPoint temp1,temp2;
    for(int i=point1.x();i<=point2.x();i++)
    {
        temp1.setX(i);
        temp1.setY(point1.y());
        temp2.setX(i);
        temp2.setY(point2.y());
        p->drawLine(temp1,temp2);
    }
}
void Deletebox::save(QTextStream &out){
    out<<"5 "<<topLeft().x()<<" "<<topLeft().y()<<" " <<bottomRight().x()<<" "<<bottomRight().y()<<endl;
}
Shape* Deletebox::read(QTextStream &in){
    int x1,y1,x2,y2;
    in>>x1>>y1>>x2>>y2;
    return new Deletebox(QPoint(x1,y1),QPoint(x2,y2));
}





