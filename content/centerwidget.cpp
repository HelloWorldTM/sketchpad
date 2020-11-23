#include "centerwidget.h"
#include<QPainter>
#include<QStatusBar>
#include "mainwindow.h"
#include<QFileDialog>
#include<QTextStream>

CenterWidget::CenterWidget(QWidget *parent) :
    QWidget(parent){
    mousePosLabel=new QLabel;
    mousePosLabel->setText("");
    mousePosLabel->setFixedWidth(150);
    MainWindow *p=(MainWindow *)parent;
    p->statusBar()->addPermanentWidget(mousePosLabel);
    CenterWindowInit();
}


//中心画布窗口的初始化，主要是释放一些列表的内存，以及一些数据的初始化
void CenterWidget::CenterWindowInit(){
    for(auto shape:shapes)
        delete shape;
    shapes.clear();
    plist.clear();
    beginDraw=false;
    find_p2=false;
    colorType=Qt::black;
    drawType=0;
    isModified=false;
    fileName=tr("");
    setMinimumSize(500,400);
    setMouseTracking(true);
    QPalette pal(this->palette());
    const QBrush brush=pal.window();
    background_color=brush.color();
}


void CenterWidget::paintEvent(QPaintEvent *){
    QPainter p(this);
    for(auto shape:shapes)
    {
        if(shape->getShapeType()==5||shape->getShapeType()==6)
        {
            shape->setColor(background_color);
            shape->draw(&p);
        }
        else
        {
            shape->draw(&p);
        }
    }
    Shape *temp=nullptr;
    if(beginDraw==true)
    {
        switch(drawType)
        {
        case 0: temp=new Line(p1,p2,colorType); break;
        case 1: temp=new Ellipse(p1,p2,colorType); break;
        case 2: temp=new Rectangle(p1,p2,colorType); break;
        case 3:
            if(find_p2)
            {
                temp=new Triangle(p1,p2,p3,colorType);
                break;
            }
            else
            {
                temp=new Line(p1,p2,colorType);
                break;
            }
        case 4: temp=new Selfline(plist,colorType); break;
        case 6: temp=new Selferaser(plist,background_color);break;
        case 5: temp=new Rectangle(p1,p2,colorType);break;
        default: temp=new Line(p1,p2,colorType);
        }
        temp->draw(&p);
        delete temp;
    }
}

void CenterWidget::setDrawType(int type){
    drawType=type;
}

void CenterWidget::setcolorType(int color){
    switch(color)
    {
    case 0:colorType=Qt::black;break;
    case 1:colorType=Qt::green;break;
    case 2:colorType=Qt::yellow;break;
    case 3:colorType=Qt::red;break;
    default:colorType=Qt::black;break;
    }
}

void CenterWidget::mousePressEvent(QMouseEvent *e){
    if(drawType==3)                //将画三角形和其他形状分开处理
    {
        if(beginDraw==false)
        {
            p1=e->pos();                //鼠标按下得到第一个点
            p2=p1;
            find_p2=false;
            beginDraw=true;
        }
        else if(find_p2==true)
        {
            p3=e->pos();
            if(p3==p2||p3==p1)
                return;
            Shape* shape=new Triangle(p1,p2,p3,colorType);
            shapes.append(shape);
            isModified=true;
            beginDraw=false;
        }
        else
        {
            p1=e->pos();                //鼠标按下得到第一个点
            p2=p1;
            find_p2=false;
            beginDraw=true;
        }
    }
    else if(drawType==4)     //画自定义多分段线段
    {
        plist.clear();
        p1=e->pos();
        plist.append(p1);
        beginDraw=true;
    }
    else if(drawType==6)      //橡皮檫鼠标按下动作
    {
        plist.clear();
        p1=e->pos();
        plist.append(p1);
        beginDraw=true;
    }
    else                   //画其他形状
    {
        p1=e->pos();                //鼠标按下得到第一个点
        p2=p1;
        beginDraw=true;
    }
}
void CenterWidget::mouseReleaseEvent(QMouseEvent *e){
    if(drawType==3)
    {
        if(find_p2==false)
        {
            p2=e->pos();
            if(p1==p2)
            {
                beginDraw=false;
                return;
            }
            find_p2=true;
        }
    }
    else if(drawType==4)
    {
        p1=e->pos();
        plist.append(p1);
        if(plist.count()<=2)
        {
            beginDraw=false;
            return;
        }
        Shape *shape=new Selfline(plist,colorType);
        beginDraw=false;
        shapes.append(shape);
        isModified=true;
        update();
    }
    else if(drawType==6)
    {
        p1=e->pos();
        plist.append(p1);
        if(plist.count()<=2)
        {
            beginDraw=false;
            return;
        }
        Shape *shape=new Selferaser(plist,background_color);
        beginDraw=false;
        shapes.append(shape);
        isModified=true;
        update();
    }
    else
    {
        p2=e->pos();                  //鼠标松开得到第二个点
        if(p1==p2)
        {
            beginDraw=false;
            return;
        }
        Shape *shape=nullptr;
        switch(drawType)
        {
        case 0: shape=new Line(p1,p2,colorType); beginDraw=false; break;
        case 1: shape=new Ellipse(p1,p2,colorType); beginDraw=false; break;
        case 2: shape=new Rectangle(p1,p2,colorType); beginDraw=false; break;
        case 5: shape=new Deletebox(p1,p2,background_color);beginDraw=false;break;
        default: beginDraw=false;return;
        }
        shapes.append(shape);
        isModified=true;
        update();
    }
}

void CenterWidget::mouseMoveEvent(QMouseEvent *e){
    mousePosLabel->setText("X:"+QString::number(e->x())+",Y:" +QString::number(e->y()));
    if(beginDraw==false)
        return;
    if(drawType==3)
    {
        if(find_p2==false)
        {
            p2=e->pos();
            update();
        }
        else
        {
            p3=e->pos();
            update();
        }
    }
    else if(drawType==4)
    {
        p1=e->pos();
        p2=plist[plist.count()-1];
        if(p2!=p1)
        {
            plist.append(p1);
            update();
        }
    }
    else if(drawType==6)
    {
        p1=e->pos();
        p2=plist[plist.count()-1];
        if(p2!=p1)
        {
            plist.append(p1);
            update();
        }
    }
    else
    {
        p2=e->pos();
        update();
    }
}

bool CenterWidget::getModifiedFlag(){
    return isModified;
}

void CenterWidget::newDrawing(){                //新建绘图
    CenterWindowInit();
    parentWidget()->setWindowTitle(tr("New Canvas"));
    update(); //更新窗口显示
}

void CenterWidget::openDrawing(){ //打开绘图
    fileName=QFileDialog::getOpenFileName(this, tr("打开文件"),"/",tr("绘图文件(*.draw)"));
    if(fileName==tr(""))
        return;
    for(auto shape:shapes)
        delete shape;
    shapes.clear();
    beginDraw=false;
    isModified=false;
    openFile(fileName); //存储文件
    parentWidget()->setWindowTitle(tr("Open File@")+fileName);
    update();
}

void CenterWidget::saveDrawing(){
    if(fileName==tr("")){
        fileName=QFileDialog::getSaveFileName(this,tr("保存文件"),"/",tr("绘图文件(*.draw)"));
        if(fileName==tr(""))
            return ;
    }
    saveFile(fileName);
    parentWidget()->setWindowTitle(tr("Save File@")+fileName);
    isModified=false;
}

void CenterWidget::saveFile(QString fileName){ //写文件操作
    QFile file(fileName);
    if(file.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream out(&file);
        out<<shapes.length()<<endl;
        for(auto shape:shapes)
            shape->save(out);
        file.close();
    }
}

void CenterWidget::openFile(QString fileName){ //读文件操作
    QFile file(fileName);
    if(file.open(QFile::ReadOnly)){ //只读方式打开
        QTextStream in(&file);
        int nums;
        in>>nums;
        int type;
        Shape *curShape;
        for(int i=0;i<nums;++i){
            in>>type;
            switch(type)
            {
            case 0: curShape=Line::read(in); break;
            case 1: curShape=Ellipse::read(in); break;
            case 2: curShape=Rectangle::read(in); break;
            case 3: curShape=Triangle::read(in);break;
            case 4: curShape=Selfline::read(in);break;
            case 5: curShape=Deletebox::read(in);break;
            case 6: curShape=Selferaser::read(in);break;
            default: continue;
            }
            shapes.append(curShape);
        }
        file.close();
    }
}

CenterWidget::~CenterWidget()
{
    for(auto shape:shapes)
        delete shape;
}


