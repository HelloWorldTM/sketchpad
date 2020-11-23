#include "shape.h"

Shape::Shape(QColor c):color(c){
}
void Shape::setColor(int colorType){
    switch(colorType)
    {
    case 0: color=Qt::black; break;
    case 1: color=Qt::green; break;
    case 2: color=Qt::yellow; break;
    case 3: color=Qt::red; break;
    default: color=Qt::black; break;
    }
}
void Shape::setColor(QColor c){
    color=c;
}
void Shape::setShapeType(int m){
    shapeType=m;
}
int Shape::getShapeType()const{
    return shapeType;
}
int Shape::getColor()const{
    if(color==Qt::black) return 0;
    else if(color==Qt::green) return 1;
    else if(color==Qt::yellow) return 2;
    else if(color==Qt::red) return 3;
    else return 0;
}

