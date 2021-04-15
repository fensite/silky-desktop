#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QVector>
#include <QStringList>
#include <QLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QDebug>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>
#include <line.h>
#include <getApp.h>
#include <getCapp.h>
#include <QPalette>
#include <QScroller>
#include <QGesture>
#include "itemdelegate.h"
#include "itemdef.h"
#include "TestListView.h"





Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //提供列表接口
    UkuiMenuInterface *pUkuiMenuIneterface = new UkuiMenuInterface;
    applist = pUkuiMenuIneterface -> createAppInfoVector();

    this->setWindowFlags(Qt::FramelessWindowHint);//无边框

    ui->setupUi(this);
    //设置鼠标光标
    QCursor cursor(QPixmap("../desktopdemo/pics/cursor.png"),-1,-1);
    setCursor(cursor);


    //显示时间
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(time_update()));
    timer->start(100); //0.1s执行一次,定时器

    //初始化数据
    initData();

    //设置list属性
    page->setMinimumSize(1200,996);
    page->viewport()->setAcceptDrops(true);
    page->setDragDropMode(QAbstractItemView::DragDrop);
    page->setStyleSheet("QListView {background-color: transparent;font-color:(255,255,255)}");


    display();

    //设置背景图片
    QPalette pal =this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap("../layout/pics/background.jpeg")));
    setPalette(pal);

    //安装事件过滤器
    ui->wid2->installEventFilter(this);
    ui->wid1->installEventFilter(this);


}

Widget::~Widget()
{
    delete ui;
}

//显示app图标
void Widget::initData()
{

    QStandardItemModel *  slm ;

   // TestItemDelegate *delegate = new TestItemDelegate();
   // page->setItemDelegate(delegate);

    //设置item属性
    page -> setViewMode ( QListView :: IconMode );
    page -> setFocusPolicy(Qt::NoFocus);
    page -> setIconSize ( QSize ( 112 , 112 ));
    page -> setGridSize ( QSize ( 216, 238));

    //实现滑动
    page->setFlow(QListView::TopToBottom);
    page->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    page->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    page->setHorizontalScrollMode(QListView::ScrollPerPixel);
    QScroller::grabGesture(page,QScroller::LeftMouseButtonGesture);
    page->setSelectionMode(QListView::ExtendedSelection);
   //QListView::Item:hover { background: rgba(255,255,255,20%); font-color: white; }
    page->setStyleSheet(R"(
                       QListView { outline: none; background-color: transparent; }
                       )");

    //设置模型
    slm=new QStandardItemModel(this);

    //获取图标等信息
    for (int i = 0; i < applist.size(); i++) {

        QStandardItem *s1;
        UkuiMenuInterface *pUkuiMenuInterface = new UkuiMenuInterface;
        QString name = pUkuiMenuInterface -> getAppName(applist[i][0]);
        QString iconstr = pUkuiMenuInterface->getAppIcon(applist[i][0]);

        QIcon icon;      
        QFileInfo iconFileInfo(iconstr);
        if(iconFileInfo.isFile() && (iconstr.endsWith(".png") || iconstr.endsWith(".svg")))
            icon=QIcon(iconstr);
        else
        {
            iconstr.remove(".png");
            iconstr.remove(".svg");
            icon=QIcon::fromTheme(iconstr);
            if(icon.isNull())
            {
                if(QFile::exists(QString("/usr/share/icons/hicolor/scalable/apps/%1.%2").arg(iconstr).arg("svg")))
                    icon=QIcon(QString("/usr/share/icons/hicolor/scalable/apps/%1.%2").arg(iconstr).arg("svg"));
                else if(QFile::exists(QString("/usr/share/icons/hicolor/scalable/apps/%1.%2").arg(iconstr).arg("png")))
                    icon=QIcon(QString("/usr/share/icons/hicolor/scalable/apps/%1.%2").arg(iconstr).arg("png"));
                else if(QFile::exists(QString("/usr/share/icons/hicolor/128x128/apps/%1.%2").arg(iconstr).arg("svg")))
                    icon=QIcon(QString("/usr/share/icons/hicolor/128x128/apps/%1.%2").arg(iconstr).arg("svg"));
                else if(QFile::exists(QString("/usr/share/icons/hicolor/128x128/apps/%1.%2").arg(iconstr).arg("png")))
                    icon=QIcon(QString("/usr/share/icons/hicolor/128x128/apps/%1.%2").arg(iconstr).arg("png"));
                else if(QFile::exists(QString("/usr/share/pixmaps/%1.%2").arg(iconstr).arg("png")))
                    icon=QIcon(QString("/usr/share/pixmaps/%1.%2").arg(iconstr).arg("png"));
                else if(QFile::exists(QString("/usr/share/pixmaps/%1.%2").arg(iconstr).arg("svg")))
                    icon=QIcon(QString("/usr/share/pixmaps/%1.%2").arg(iconstr).arg("svg"));
                else
                    icon=QIcon::fromTheme(QString("application-x-desktop"));
            }
        }

        //传入数据
        s1=new QStandardItem(icon,name);
        slm->appendRow(s1);

    }

    page->setModel(slm);

}


void Widget::time_update() //显示系统时间的功能
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("hh:mm");
    QString str1 = time.toString("MM-dd");
    QString str2 = time.toString("dddd");
    ui->l_time->setText(str);
    ui->l_day->setText(str1);
    ui->l_week->setText(str2);
}


void Widget::pic_display(QLabel*l_pic)
{
    QPixmap pix("../layout/pics/disp.jpeg");
    QPixmap dest=pix.scaled(l_pic->size(),Qt::KeepAspectRatio);
    l_pic->setPixmap(dest);
}


void Widget::display()
{


    QGridLayout* layout_t = new QGridLayout();//时间组件布局

    ui->l_day->setText("03-08");
    ui->l_week->setText("星期一");
    ui->l_time->setText("20:34");

    ui->l_time->setStyleSheet("QLabel{font: 70 68pt Noto Sans CJK SC Black;color: rgb(255, 255, 255);padding-left:150px;}");
    ui->l_day->setStyleSheet("QLabel{font: 60 30pt  Noto Sans CJK SC Black;color: rgb(255, 255, 255);}");
    ui->l_week->setStyleSheet("QLabel{font: 60 28pt Noto Sans CJK SC Black;color: rgb(255, 255, 255);}");

    ui->l_week->setMinimumSize(112, 60);
    ui->l_day->setMinimumSize(112, 60);
    ui->l_time->setMinimumSize(250, 110);

    layout_t->addWidget(ui->l_time,0,0,2,2);
    layout_t->addWidget(ui->l_week,0,2);
    layout_t->addWidget(ui->l_day,1,2);

    ui->l_day->setAlignment(Qt::AlignTop);
    ui->l_week->setAlignment(Qt::AlignBottom);
    ui->l_time->setAlignment(Qt::AlignCenter);

    // 左侧伸缩栏
    QGridLayout* layout_p = new QGridLayout();
    QLabel *l_pic=new QLabel();
    l_pic->resize(400,800);
    l_pic->setMinimumSize(400,800);
    l_pic->setStyleSheet("QLabel{padding-left:130px;padding-bottom:200px}");
    pic_display(l_pic);
    layout_p->setColumnStretch(0, 3.2);
    layout_p->addLayout(layout_t,0,0);
    layout_p->addWidget(l_pic,1,0);
    ui->wid1->setLayout(layout_p);
    ui->wid1->setGeometry(QRect(0,0,610,1080));

    //右侧app布局
    QGridLayout* layout_a = new QGridLayout();
    QLabel *l_blet=new QLabel();
    QLabel *l_table1=new QLabel();
    QLabel *l_blet1=new QLabel();

    page->setMinimumSize(1200,996);

    layout_a->addWidget(page,1,0);
    layout_a->addWidget(l_blet,1,1);
    layout_a->addWidget(l_table1,0,0);
    layout_a->addWidget(l_blet1,0,1);

    layout_a->setRowStretch(0, 1);//设置行列比例系数
    layout_a->setRowStretch(1, 55);
    layout_a->setColumnStretch(0, 21.6);
    layout_a->setColumnStretch(1, 1);
    ui->wid2->setLayout(layout_a);
    ui->wid2->setGeometry(QRect(610,0,1300,1080));


//     QGridLayout* mainlayout = new QGridLayout();//总体布局
//     QLabel *l=new QLabel();
//     l->setStyleSheet("QLabel{background-color: rgb(255, 255, 255);}");
//     mainlayout->addLayout(layout_p,0,0);
//     mainlayout->addLayout(layout_a,0,1);
//     mainlayout->addWidget(l_blet1,1,0,1,2);

//     mainlayout->setRowStretch(0, 14.9);//设置行列比例系数
//     mainlayout->setRowStretch(1, 1);
//     mainlayout->setColumnStretch(0, 1);
//     mainlayout->setColumnStretch(1, 2.41);
//     mainlayout->setSpacing(0);



    resize(1920,1080);
 // setLayout(mainlayout);

}


bool Widget::eventFilter(QObject *watched, QEvent *event)
{
     static int press_x;
     static int press_y;
     static int relea_x;  //鼠标释放时的位置
     static int relea_y;

    if(watched==ui->wid1&&flag==1)
    {
        QMouseEvent *eve = static_cast<QMouseEvent *>(event);

        if(eve->type()==QEvent::MouseButtonPress)
        {
            //QMouseEvent *ev = static_cast<QMouseEvent *>(event); //将之转换为鼠标事件
            press_x = eve->globalX();
            press_y = eve->globalY();

        }

        if(eve->type()==QEvent::MouseButtonRelease)
        {
            relea_x = eve->globalX();
            relea_y = eve->globalY();


            //左侧隐藏
           if((relea_x - press_x)==0 && (relea_y - press_y)==0)
            {
                QPropertyAnimation *ani=new QPropertyAnimation(ui->wid1,"geometry");
                ani->setDuration(300);
                ani->setStartValue(QRect(ui->wid1->geometry()));
                ani->setEndValue(QRect(-ui->wid1->width(),0,ui->wid1->width(),ui->wid1->height()));


                QPropertyAnimation *ani1=new QPropertyAnimation(ui->wid2,"geometry");
                ani1->setDuration(300);
                ani1->setStartValue(QRect(ui->wid2->geometry()));
                ani1->setEndValue(QRect(110,0,1820,1080));

                QPropertyAnimation *ani2=new QPropertyAnimation(page,"gridSize");
                ani2->setDuration(300);
                ani2->setStartValue(QSize(206, 238));
                ani2->setEndValue(QSize ( 306, 238));

                QParallelAnimationGroup *group=new QParallelAnimationGroup();
                group->addAnimation(ani);
                group->addAnimation(ani1);
                group->addAnimation(ani2);
                group->start();
                flag=0;
            }
        }
    }


    //左侧拉出
     if(watched==ui->wid2&&flag==0)
    {
         QMouseEvent *eve = static_cast<QMouseEvent *>(event);

        if(eve->type()==QEvent::MouseButtonPress)
        {
            //QMouseEvent *ev = static_cast<QMouseEvent *>(event); //将之转换为鼠标事件
            press_x = eve->globalX();
            press_y = eve->globalY();

        }

        if(eve->type()==QEvent::MouseButtonRelease)
        {
            relea_x = eve->globalX();
            relea_y = eve->globalY();

             if((relea_x - press_x)==0 && (relea_y - press_y)==0)
            {
                 QPropertyAnimation *ani=new QPropertyAnimation(ui->wid1,"geometry");
                 ani->setDuration(300);
                 ani->setStartValue(QRect(ui->wid1->geometry()));
                 ani->setEndValue(QRect(0,0,ui->wid1->width(),ui->wid1->height()));


                 QPropertyAnimation *ani1=new QPropertyAnimation(ui->wid2,"geometry");
                 ani1->setDuration(300);
                 ani1->setStartValue(QRect(ui->wid2->geometry()));
                 ani1->setEndValue(QRect(610,0,1300,1080));

                 QPropertyAnimation *ani2=new QPropertyAnimation(page,"gridSize");
                 ani2->setDuration(300);
                 ani2->setStartValue(QSize(306, 238));
                 ani2->setEndValue(QSize ( 206, 238));

                 QParallelAnimationGroup *group=new QParallelAnimationGroup();
                 group->addAnimation(ani);
                 group->addAnimation(ani1);
                 group->addAnimation(ani2);
                 group->start();
                 flag=1;

            }
        }
    }
     return QWidget::eventFilter(watched,event);
}



