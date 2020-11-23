#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include<QList>
#include<QPoint>
#include<QRect>
#include<QMouseEvent>
#include<QLabel>
#include"shape.h"
#include"line.h"
#include"ellipse.h"
#include"rectangle.h"
#include"triangle.h"
#include"selfline.h"
#include"deletebox.h"
#include"selferaser.h"
class CenterWidget : public QWidget
{
    Q_OBJECT
    ~CenterWidget();
public:
    explicit CenterWidget(QWidget *parent = 0);
    void CenterWindowInit();
    void paintEvent(QPaintEvent *);
    void setDrawType(int type);
    void setcolorType(int color);
    void newDrawing();
    void openDrawing();
    void saveDrawing();
    bool getModifiedFlag();           //获取当前的文档修改状态

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QList<Shape*> shapes;           //用于存放所有的部件
    QColor background_color;        //存放当前窗口的背景色
    QPoint p1,p2,p3;                //绘图过程的临时起点和终点,p3用于绘制三角形
    QList<QPoint> plist;            //专门用于自己绘制的多个点的线段图数据点
    int drawType;                   //当前绘图类型，0-直线，1-椭圆，2-矩形 3-三角形 4-自绘线段点图 5-矩形删除框 6-自绘橡皮檫
    QColor colorType;               //颜色类型
    bool beginDraw;
    bool find_p2;                   //指示第二个点是否找到
    QLabel* mousePosLabel;
    bool isModified;                 //标识文档是否发生了修改
    QString fileName;                //文件名，新建后为空
    void saveFile(QString fileName); //写文件的操作
    void openFile(QString fileName); //读文件的操作
};

#endif // CENTERWIDGET_H


