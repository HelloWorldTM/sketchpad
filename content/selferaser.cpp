#include "selferaser.h"

Selferaser::Selferaser(QList<QPoint>& pl,QColor c):Shape(c)
{
    QListIterator<QPoint> i(pl);
    while(i.hasNext())
    {
        point_list.append(i.next());
    }
    setShapeType(6);
}
Selferaser::~Selferaser(){
        point_list.clear();
}

int Selferaser::pointCount()
{
    return point_list.count();
}

void Selferaser::draw(QPainter *p){
    QPen pen(color,1,Qt::SolidLine);
    p->setPen(pen);
    QListIterator<QPoint> i(point_list);
    QPoint p1,p2,p3;
    while(i.hasNext())
    {
        p1=i.next();
        for(int i=p1.x()-13;i<=p1.x()+13;i++)
        {
            p2.setX(i);
            p2.setY(p1.y()-13);
            p3.setX(i);
            p3.setY(p1.y()+13);
            p->drawLine(p2,p3);
        }
    }
}
void Selferaser::save(QTextStream &out){
    QListIterator<QPoint> i(point_list);
    out<<"6 "<<pointCount()<<" ";
    QPoint temp;
    while(i.hasNext())
    {
        temp=i.next();
        out<<temp.x()<<" "<<temp.y()<<" ";
    }
    out<<endl;
}

Shape* Selferaser::read(QTextStream &in)
{
    int count;
    in>>count;
    int x,y;
    QList<QPoint> tempList;
    for(int i=0;i<count;i++)
    {
        in>>x;
        in>>y;
        tempList.append(QPoint(x,y));
    }
    return new Selferaser(tempList);
}


