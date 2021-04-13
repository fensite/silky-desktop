#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include<QLabel>
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include<QTableWidgetItem>
#include <QEvent>
#include <QMouseEvent>
#include <QDrag>
#include<QGraphicsItem>
#include"itemdelegate.h"
#include"TestListView.h"
#include"itemdef.h"

#endif // WIDGET_H


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public slots:
    void time_update();

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void display();
    void pic_display(QLabel*l_pic);
    void appicon_display(QTableView* tableView);
    void app_mouseenter(QTableView* tableView);



private:
    Ui::Widget *ui;
    QPoint offest;
    //ItemDelegate *m_delegate;
    QStandardItemModel *m_model;
    QVector <QStringList> applist;
    void initData();
    TestListView *page = new TestListView();

};

