#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QLayout>
#include <QLabel>
#include <QSplitter>
#include <QMessageBox>
#include <QCursor>
#include "centerwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MainWindowInit();             //初始化窗口
    void AddActionToMenu();            //初始化action将相应的action添加到菜单
    void AddActionToToolbar();         //初始化action并且添加到相应的工具栏

private:
    CenterWidget* cenWidg;            //绘图的主窗口
    QMenuBar *main_menubar;            //菜单栏
    QToolBar *file_toolbar;            //文件操作的菜单栏
    QToolBar *paint_toolbar;           //画图用到的一些工具
    QStatusBar *main_statusbar;        //状态栏
    QMenu *file_menu;                  //文件菜单选项
    QMenu *about_menu;                 //关于菜单选项
    QAction *file_save;                //保存文件
    QAction *file_open;                //打开文件
    QAction *file_exit;                //保存并且退出
    QAction *file_new;                 //新建文件
    QAction *about_author;             //关于作者
    QAction *paint_choose;             //选择工具
    QAction *paint_pen;                //画图工具
    QAction *paint_eraser;             //橡皮檫
    QAction *paint_line;               //直线
    QAction *paint_triangle;           //三角形
    QAction *paint_rectangle;          //矩形
    QAction *paint_circle;             //圆形
    QAction *paint_black;
    QAction *paint_yellow;
    QAction *paint_green;
    QAction *paint_red;
    QCursor *eraserCur;

protected slots:
    void line();                       //绘制直线
    void ellipse();                    //绘制椭圆
    void rectangle();                  //绘制矩形
    void triangle();                   //绘制三角形
    void selfline();                   //画自画多点线段
    void deletebox();                  //画矩形删除框
    void selferaser();                 //橡皮檫
    void newDrawing();                 //新建画布
    void openDrawing();                //打开文件
    void saveDrawing();                //保存文件
    void closeEvent(QCloseEvent *);    //退出时的处理函数
    void black();                      //设置颜色为黑色
    void yellow();                     //设置颜色为黄色
    void green();                      //设置颜色为绿色
    void red();                        //设置颜色为红色
    void showAboutAuthorDialog();      //关于作者对话框

};

#endif // MAINWINDOW_H

