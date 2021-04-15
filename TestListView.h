#ifndef TESTLISTVIEW_H
#define TESTLISTVIEW_H

#include<QListView>
#include<QSettings>
#include<QDir>





class TestListView : public QListView
{
    Q_OBJECT

public:
    explicit TestListView(QWidget *parent = nullptr);

    bool isDraging() const {return IsDraging;}
    int offset() const {return 19;}
    int highlightedRow() const {return theHighlightedRow;}
    int dragRow() const {return theDragRow;}
    static QString myMimeType() { return QStringLiteral("TestListView/text-icon"); }
    void mouseDoubleClickEvent(QMouseEvent *event);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;

private:
    bool IsDraging = false;
    int theHighlightedRow = -2;
    int oldHighlightedRow = -2;
    int theDragRow = -1;
    int theInsertRow = -1;
    QVector<QStringList> applist;

};

#endif // TESTLISTVIEW_H
