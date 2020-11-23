#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindowInit();
}

MainWindow::~MainWindow()
{
}


void MainWindow::MainWindowInit()
{
    //部署主绘图窗口
    cenWidg=new CenterWidget(this);
    setCentralWidget(cenWidg);

    /*设置主窗口的图标及窗口大小等*/
    setWindowTitle(tr("Start Your Painting Easily"));
    resize(QSize(800,800));
    setMinimumSize(QSize(500,500));
    setWindowIcon(QIcon(":/icon/sketchpad.ico"));

    /*设置菜单栏的初始化*/
    main_menubar=menuBar();
    file_menu=main_menubar->addMenu(tr("  文件  "));
    about_menu=main_menubar->addMenu(tr("  关于  "));
    setMenuBar(main_menubar);
    AddActionToMenu();

    /*设置工具栏*/
    file_toolbar=addToolBar(tr("file"));
    paint_toolbar=addToolBar(tr("paint"));
    file_toolbar->setAllowedAreas(Qt::TopToolBarArea);
    paint_toolbar->setAllowedAreas(Qt::TopToolBarArea);
    file_toolbar->setMovable(false);
    paint_toolbar->setMovable(false);
    AddActionToToolbar();

    /*加载鼠标图标图片*/
    eraserCur=new QCursor(QPixmap(":/icon/EraserCursor.png"),-1,-1);

    connect(file_new,SIGNAL(triggered()),this,SLOT(newDrawing()));
    connect(file_open,SIGNAL(triggered()),this,SLOT(openDrawing()));
    connect(file_save,SIGNAL(triggered()),this,SLOT(saveDrawing()));
    connect(file_exit,SIGNAL(triggered()),this,SLOT(close()));
    connect(about_author,SIGNAL(triggered()),this,SLOT(showAboutAuthorDialog()));
    connect(paint_line,SIGNAL(triggered()),this,SLOT(line()));
    connect(paint_circle,SIGNAL(triggered()),this,SLOT(ellipse()));
    connect(paint_rectangle,SIGNAL(triggered()),this,SLOT(rectangle()));
    connect(paint_triangle,SIGNAL(triggered()),this,SLOT(triangle()));
    connect(paint_pen,SIGNAL(triggered()),this,SLOT(selfline()));
    connect(paint_choose,SIGNAL(triggered()),this,SLOT(deletebox()));
    connect(paint_eraser,SIGNAL(triggered()),this,SLOT(selferaser()));
    connect(paint_black,SIGNAL(triggered()),this,SLOT(black()));
    connect(paint_green,SIGNAL(triggered()),this,SLOT(green()));
    connect(paint_yellow,SIGNAL(triggered()),this,SLOT(yellow()));
    connect(paint_red,SIGNAL(triggered()),this,SLOT(red()));
}

//将动作添加到菜单
void MainWindow::AddActionToMenu()
{
    file_save=new QAction(tr("保存文件"),this);
    file_save->setIcon(QIcon(":/icon/savefile.png"));
    file_open=new QAction(tr("打开文件"),this);
    file_open->setIcon(QIcon(":/icon/openfile.png"));
    file_exit=new QAction(tr("保存并退出"),this);
    file_exit->setIcon(QIcon(":/icon/exit.png"));
    file_new=new QAction(tr("新建文件"),this);
    file_new->setIcon(QIcon(":/icon/newfile.png"));
    about_author=new QAction(tr("关于作者"),this);
    about_author->setIcon(QIcon(":/icon/author.png"));
    file_menu->addAction(file_new);
    file_menu->addAction(file_open);
    file_menu->addAction(file_save);
    file_menu->addAction(file_exit);
    about_menu->addAction(about_author);
}

//将动作添加到工具栏
void MainWindow::AddActionToToolbar()
{
    file_toolbar->addAction(file_new);
    file_toolbar->addAction(file_open);
    file_toolbar->addAction(file_save);
    file_toolbar->addAction(file_exit);
    paint_choose=new QAction(QIcon(":/icon/choose.png"),tr("choose"),this);
    paint_pen=new QAction(QIcon(":/icon/pen.png"),tr("pen"),this);
    paint_eraser=new QAction(QIcon(":/icon/eraser.png"),tr("eraser"),this);
    paint_line=new QAction(QIcon(":/icon/line.png"),tr("line"),this);
    paint_triangle=new QAction(QIcon(":/icon/triangle.png"),tr("triangle"),this);
    paint_rectangle=new QAction(QIcon(":/icon/rectangle.png"),tr("rectangle"),this);
    paint_circle=new QAction(QIcon(":/icon/ellipse.png"),tr("circle"),this);
    paint_black=new QAction(QIcon(":/icon/black.png"),tr("black"),this);
    paint_yellow=new QAction(QIcon(":/icon/yellow.png"),tr("yellow"),this);
    paint_green=new QAction(QIcon(":/icon/green.png"),tr("green"),this);
    paint_red=new QAction(QIcon(":/icon/red.png"),tr("red"),this);
    paint_toolbar->addAction(paint_choose);
    paint_toolbar->addAction(paint_pen);
    paint_toolbar->addAction(paint_eraser);
    paint_toolbar->addAction(paint_line);
    paint_toolbar->addAction(paint_triangle);
    paint_toolbar->addAction(paint_rectangle);
    paint_toolbar->addAction(paint_circle);
    paint_toolbar->addAction(paint_black);
    paint_toolbar->addAction(paint_yellow);
    paint_toolbar->addAction(paint_green);
    paint_toolbar->addAction(paint_red);
}

//画直线
void MainWindow::line(){
    cenWidg->setDrawType(0);
    cenWidg->setCursor(Qt::ArrowCursor);
}

//画椭圆
void MainWindow::ellipse(){
    cenWidg->setDrawType(1);
    cenWidg->setCursor(Qt::ArrowCursor);
}

//画矩形
void MainWindow::rectangle(){
    cenWidg->setDrawType(2);
    cenWidg->setCursor(Qt::ArrowCursor);
}

//画三角形
void MainWindow::triangle(){
    cenWidg->setDrawType(3);
    cenWidg->setCursor(Qt::ArrowCursor);
}

//画多点自划线
void MainWindow::selfline(){
    cenWidg->setDrawType(4);
    cenWidg->setCursor(Qt::CrossCursor);
}

//画矩形删除框
void MainWindow::deletebox(){
    cenWidg->setDrawType(5);
    cenWidg->setCursor(Qt::CrossCursor);
}

//橡皮檫
void MainWindow::selferaser(){
    cenWidg->setDrawType(6);
    cenWidg->setCursor(*eraserCur);
}

//新建画布
void MainWindow::newDrawing()
{
    if(cenWidg->getModifiedFlag()==true)       //文档已修改
    {
        switch(QMessageBox::question(this,tr("文档保存提示"),
                            tr("文档已经修改，是否保存文档"),
                            QMessageBox::Ok|
                            QMessageBox::Cancel|
                            QMessageBox::No,
                            QMessageBox::Ok))
        {
        case QMessageBox::Ok: cenWidg->saveDrawing(); break;
        case QMessageBox::Cancel: return;
        case QMessageBox::No: break;
        default: break;
        }
    }
    cenWidg->newDrawing();
}

//打开已有的文档
void MainWindow::openDrawing(){
    if(cenWidg->getModifiedFlag()==true){ //文档已修改
        switch(QMessageBox::question(this,tr("文档保存提示"),
                                     tr("文档已经修改，是否保存文档"),
                                     QMessageBox::Ok|QMessageBox::Cancel |
                                     QMessageBox::No, QMessageBox::Ok)){
        case QMessageBox::Ok: cenWidg->saveDrawing(); break;
        case QMessageBox::Cancel: return;
        case QMessageBox::No: break;
        default: break;
        }
    }
    cenWidg->openDrawing();
}

//保存文档
void MainWindow::saveDrawing(){
    cenWidg->saveDrawing();
}

//退出并且保存
void MainWindow::closeEvent(QCloseEvent *event){
    if(cenWidg->getModifiedFlag()==true){ //文档已修改
        switch(QMessageBox::question(this,tr("文档保存提示"),
                                     tr("文档已经修改，是否保存文档"),
                                     QMessageBox::Ok|
                                     QMessageBox::Cancel |
                                     QMessageBox::No, QMessageBox::Ok)){
        case QMessageBox::Ok: cenWidg->saveDrawing(); event->accept(); break;
        case QMessageBox::Cancel: event->ignore(); break;
        case QMessageBox::No: event->accept(); break;
        default: event->accept(); break;
        }
    }
}

//设置黑色
void MainWindow::black(){
    cenWidg->setcolorType(0);
}

//设置绿色
void MainWindow::green(){
    cenWidg->setcolorType(1);
}

//设置黄色
void MainWindow::yellow(){
    cenWidg->setcolorType(2);
}

//设置红色
void MainWindow::red(){
    cenWidg->setcolorType(3);
}

//关于作者对话框
void MainWindow::showAboutAuthorDialog(){
    QMessageBox::information(this,tr("关于作者"),tr("作者：骆俊\n学号：PB15030820\n@Copyrights All Reserved."));
    return;
}




