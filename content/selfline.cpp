#include "selfline.h"

Selfline::Selfline(QList<QPoint>& pl,QColor c):Shape(c)
{
    QListIterator<QPoint> i(pl);
    while(i.hasNext())
    {
        point_list.append(i.next());
    }
    setShapeType(4);
}
Selfline::~Selfline(){
        point_list.clear();
}

int Selfline::pointCount()
{
    return point_list.count();
}

void Selfline::draw(QPainter *p){
    QPen pen(color,1,Qt::SolidLine);
    p->setPen(pen);
    QListIterator<QPoint> i(point_list);
    QPoint p2=i.next();
    QPoint p1;
    while(i.hasNext())
    {
        p1=p2;
        p2=i.next();
        if(p1==p2)
        {
            continue;
        }
        p->drawLine(p1,p2); //绘制线条
    }
}
void Selfline::save(QTextStream &out){
    QListIterator<QPoint> i(point_list);
    out<<"4 "<<pointCount()<<" ";
    QPoint temp;
    while(i.hasNext())
    {
        temp=i.next();
        out<<temp.x()<<" "<<temp.y()<<" ";
    }
    out<<getColor()<<endl;
}

Shape* Selfline::read(QTextStream &in)
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
    int colorNum;
    in>>colorNum;
    Selfline* p = new Selfline(tempList);
    p->setColor(colorNum);
    return p;
}


