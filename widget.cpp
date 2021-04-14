#include "widget.h"
#include "ui_widget.h"
#include<QApplication>
#include<QVector>
#include<QStringList>
#include<QLayout>
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QTextEdit>
#include<QVBoxLayout>
#include <QApplication>
#include<QFileSystemModel>
#include<QTreeView>
#include<QListView>
#include<QDebug>
#include<QStandardItemModel>
#include<QHeaderView>
#include<QTableView>
#include<line.h>
#include<getApp.h>
#include<getCapp.h>
#include<QPalette>
#include<QScroller>
#include<QGesture>
#include "itemdelegate.h"
#include "itemdef.h"
#include "TestListView.h"





Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    UkuiMenuInterface *pUkuiMenuIneterface = new UkuiMenuInterface;
    applist = pUkuiMenuIneterface -> createAppInfoVector();



    this->setWindowFlags(Qt::FramelessWindowHint);//无边款

    ui->setupUi(this);
    //设置鼠标光标
    QCursor cursor(QPixmap("../desktopdemo/pics/cursor.png"),-1,-1);
    setCursor(cursor);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(time_update()));
    timer->start(100); //0.1s执行一次,定时器


    initData();


   // m_delegate = new ItemDelegate(this);
   // ui->listView->setItemDelegate(m_delegate);       //为视图设置委托
    //page->setMovement(QListView::Snap);

    page->setMinimumSize(1200,996);
   // page->setMaximumSize(1200,996);

    //page->setSpacing(72);                   //为视图设置控件间距
    //ui->listView->setModel(m_model);                  //为委托设置模型
   // ui->listView->setViewMode(QListView::IconMode); //设置Item图标显示

    page->setDragEnabled(true);            //控件不允许拖动

    page->viewport()->setAcceptDrops(true);
    //ui->listView->setDropIndicatorShown(true);
    page->setDragDropMode(QAbstractItemView::DragDrop);
    page->setStyleSheet("QListView {background-color: transparent;font-color:(255,255,255)}");




       display();

      QPalette pal =this->palette();
      pal.setBrush(QPalette::Background,QBrush(QPixmap("../layout/pics/background.jpeg")));
      setPalette(pal);

      ui->wid2->installEventFilter(this);
      ui->wid1->installEventFilter(this);



}

Widget::~Widget()
{
    delete ui;
}

void Widget::initData()//显示app图标
{
    /*
    m_model = new QStandardItemModel();
    for (int i = 0; i < 24; i++) {
        QStandardItem *Item = new QStandardItem;
        ItemData itemData;
        itemData.name = QString("Name");
        itemData.icon = QPixmap("../layout/pics/icon.jpeg");
        Item->setData(QVariant::fromValue(itemData),Qt::UserRole+1);//整体存取
        m_model->appendRow(Item);      //追加Item
    }*/
    QStandardItemModel *  slm ;

    TestItemDelegate *delegate = new TestItemDelegate();

    //page->setItemDelegate(delegate);

    page -> setViewMode ( QListView :: IconMode );
    page -> setFocusPolicy(Qt::NoFocus);
    page -> setIconSize ( QSize ( 112 , 112 ));
    page -> setGridSize ( QSize ( 216, 238));

   //ui->listView -> setResizeMode ( QListView :: Adjust );

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


    slm=new QStandardItemModel(this);

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




        s1=new QStandardItem(icon,name);

        //qDebug() << icon;
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
   // QLabel *l_day=new QLabel();
   // QLabel *l_week=new QLabel();
    //QLabel *l_time=new QLabel();
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
    //l_time->setAlignment(Qt::AlignRight);
    ui->l_time->setAlignment(Qt::AlignCenter);



    QGridLayout* layout_p = new QGridLayout();// 左侧伸缩栏
    QLabel *l_pic=new QLabel();
    l_pic->resize(400,800);
    l_pic->setMinimumSize(400,800);
    l_pic->setStyleSheet("QLabel{padding-left:130px;padding-bottom:200px}");
    pic_display(l_pic);
    layout_p->setColumnStretch(0, 3.2);
    layout_p->addLayout(layout_t,0,0);
    layout_p->addWidget(l_pic,1,0);
    //l_pic->setAlignment(Qt::AlignCenter);
    ui->wid1->setLayout(layout_p);
    ui->wid1->setGeometry(QRect(0,0,610,1080));


    QGridLayout* layout_a = new QGridLayout();//右侧app布局


    QLabel *l_blet=new QLabel();
    QLabel *l_table1=new QLabel();
    QLabel *l_blet1=new QLabel();

    page->setMinimumSize(1200,996);
    //tableView->resize(1300,996);
    //tableView->horizontalHeader()->setVisible(false);// 水平不可见
    //tableView->verticalHeader()->setVisible(false);// 垂直不可见


    l_blet->setStyleSheet("QLabel{background-color: rgb(255, 255, 127);}");
   // l_table1->setStyleSheet("QLabel{background-color: rgb(127, 255, 255);}");
    //l_blet1->setStyleSheet("QLabel{background-color: rgb(255, 127, 127);padding:0;}");
   // l_blet->setMaximumWidth(100);
   // l_blet1->setMaximumWidth(100);

    //appicon_display(tableView);

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


     //QGridLayout* mainlayout = new QGridLayout();//总体布局
     //QLabel *l=new QLabel();
     //l->setStyleSheet("QLabel{background-color: rgb(255, 255, 255);}");
    // mainlayout->addLayout(layout_p,0,0);
     //mainlayout->addLayout(layout_a,0,1);
     //mainlayout->addWidget(l_blet1,1,0,1,2);

     //mainlayout->setRowStretch(0, 14.9);//设置行列比例系数
     //mainlayout->setRowStretch(1, 1);
   // mainlayout->setColumnStretch(0, 1);
   //  mainlayout->setColumnStretch(1, 2.41);
    // mainlayout->setSpacing(0);



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
               // QRect(610,0,1300,1080)

                QPropertyAnimation *ani2=new QPropertyAnimation(page,"gridSize");
                ani2->setDuration(300);
                // setGridSize ( QSize ( 206, 238));
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
                 // setGridSize ( QSize ( 206, 238));
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





