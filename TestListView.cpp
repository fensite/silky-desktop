#include<TestListView.h>
#include<QAbstractAnimation>
#include<QDragMoveEvent>
#include<QStandardItemModel>
#include<QMimeData>
#include<QDrag>
#include<QDebug>
#include<widget.h>
#include<getApp.h>
#include<QSettings>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDir>
#include <QSvgRenderer>
#include <QHeaderView>
#include<QFile>

TestListView::TestListView(QWidget *parent) :
    QListView(parent)
{
    UkuiMenuInterface *pUkuiMenuIneterface = new UkuiMenuInterface;
    applist = pUkuiMenuIneterface -> createAppInfoVector();

//    setMouseTracking(true);
    setDragEnabled(true);
    setAcceptDrops(true);
    //setDropIndicatorShown(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TestListView::dragEnterEvent(QDragEnterEvent *event)
{
    TestListView *source = qobject_cast<TestListView *>(event->source());
    if (source && source == this) {
        IsDraging = true;  //IsDraging(标志位)判断是否正在拖拽
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void TestListView::dragLeaveEvent(QDragLeaveEvent *event)
{
    oldHighlightedRow = theHighlightedRow;
    theHighlightedRow = -2;

    //之前QListWidget用的是update(QRect)，这里用的是update(QModelIndex)，当然这里也可以使用update(QRect)，只是想换一种方法而已
    update(model()->index(oldHighlightedRow, 0));
    update(model()->index(oldHighlightedRow + 1, 0));

    IsDraging = false;

    theInsertRow = -1;
    event->accept();
}

void TestListView::dragMoveEvent(QDragMoveEvent *event)
{
    TestListView *source = qobject_cast<TestListView *>(event->source());
    if (source && source == this) {

        oldHighlightedRow = theHighlightedRow;
        theHighlightedRow = indexAt(event->pos() - QPoint(0, offset())).row();


        if(event->pos().y() >= offset()){
            if(theHighlightedRow == -1)
            {

                update(model()->index(theHighlightedRow, 0));
                update(model()->index(theHighlightedRow + 1, 0));

                theInsertRow = oldHighlightedRow + 1;


            }
            else
            {
                if(oldHighlightedRow != theHighlightedRow){

                    //qDebug() << theHighlightedRow << oldHighlightedRow;
                    //刷新旧区域使dropIndicator消失
                    update(model()->index(oldHighlightedRow, 0));
                    update(model()->index(oldHighlightedRow + 1, 0));

                    //刷新新区域使dropIndicator显示
                    update(model()->index(theHighlightedRow, 0));
                    update(model()->index(theHighlightedRow + 1, 0));

                }else{
                    update(model()->index(theHighlightedRow, 0));
                    update(model()->index(theHighlightedRow + 1, 0));
                }



                theInsertRow = theHighlightedRow + 1;
            }
        }else{
            theHighlightedRow = -1;
            update(model()->index(0, 0));
            update(model()->index(1, 0));
            theInsertRow = 0;
        }

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void TestListView::dropEvent(QDropEvent *event)
{
    TestListView *source = qobject_cast<TestListView *>(event->source());
    if (source && source == this){

        IsDraging = false;  //完成拖拽

        oldHighlightedRow = theHighlightedRow;
        theHighlightedRow = -2;

        //qDebug() << oldHighlightedRow << theDragRow;


        //改变applist内容
        if(oldHighlightedRow > theDragRow)
        {
            QStringList  temp = applist[oldHighlightedRow];
            applist[oldHighlightedRow] = applist[theDragRow];
            for(int i = theDragRow; i < oldHighlightedRow - 1; i++)
            {
                applist[i] = applist[i + 1];
            }
            applist[oldHighlightedRow - 1] = temp;
        }
        if(oldHighlightedRow < theDragRow)
        {
            QStringList  temp = applist[theDragRow];
            for(int i = theDragRow; i > oldHighlightedRow + 1; i--)
            {
                applist[i] = applist[i - 1];
            }
            applist[oldHighlightedRow + 1] = temp;
        }

        QFile file("../layout/applist.txt");
        file.open(QIODevice::WriteOnly);
        file.write("");
        file.close();

        file.open(QIODevice::Append | QIODevice::Text);
        for(int i = 0; i < applist.size(); i++)
        {
            //qDebug() << applist[i];
            for(int j = 0; j < 6; j++)
            {
                file.write(applist[i][j].toUtf8());
                file.write("\n");
            }

        }
        file.close();


        //刷新以使dropIndicator消失
        update(model()->index(oldHighlightedRow, 0));
        update(model()->index(oldHighlightedRow + 1, 0));

        if(theInsertRow == theDragRow || theInsertRow == theDragRow + 1) return;



//[1]从event->mimeData()取出拖拽数据
        QString text;
        QIcon icon;
        QByteArray itemData = event->mimeData()->data(myMimeType());
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        dataStream >> text >> icon;
//[1]

        model()->insertRow(theInsertRow);  //插入新行

        QStandardItemModel *listModel = qobject_cast<QStandardItemModel *>(model());
        listModel->setItem(theInsertRow, 0, new QStandardItem(icon, text));

        setCurrentIndex(model()->index(theInsertRow, 0));  //插入行保持选中状态

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

//使用startDrag()则不需要判断拖拽距离
void TestListView::startDrag(Qt::DropActions)
{
    theDragRow = currentIndex().row();

    QStandardItemModel *listModel = qobject_cast<QStandardItemModel *>(model());
    QStandardItem *theDragItem = listModel->item(theDragRow);

//[1]把拖拽数据放在QMimeData容器中
        QString text = theDragItem->text();
        QIcon icon = theDragItem->icon();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << text << icon;

        QMimeData *mimeData = new QMimeData;
        mimeData->setData(myMimeType(), itemData);
//[1]

//[2]设置拖拽时的缩略图
        QPixmap pixmap = icon.pixmap(100,100);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
//[2]

    //删除的行需要根据theInsertRow和theDragRow的大小关系来判断(这个也是我根据实际情况测试发现的)
    if(drag->exec(Qt::MoveAction) == Qt::MoveAction){
        int theRemoveRow = -1;
        if(theInsertRow < theDragRow) theRemoveRow = theDragRow + 1;
        else theRemoveRow = theDragRow;
        model()->removeRow(theRemoveRow);
    }
}


void TestListView:: mouseDoubleClickEvent(QMouseEvent *event)
{
    int runIndex = currentIndex().row();
    UkuiMenuInterface *pUkuiMenuIneterface = new UkuiMenuInterface;

    QString appexec = pUkuiMenuIneterface -> getAppExec(applist[runIndex][0]);


//    Q_EMIT sendHideMainWindowSignal();
//    QString desktopfp=applist[runIndex][0];
//    GDesktopAppInfo * desktopAppInfo=g_desktop_app_info_new_from_filename(desktopfp.toLocal8Bit().data());
//    g_app_info_launch(G_APP_INFO(desktopAppInfo),nullptr, nullptr, nullptr);
//    g_object_unref(desktopAppInfo);
  //  qDebug() << applist[runIndex][0];
}
