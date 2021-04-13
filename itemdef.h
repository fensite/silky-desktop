#ifndef ITEMDEF_H
#define ITEMDEF_H
#include <QMetaType>
#include<QIcon>
#include<QStandardItem>

class TestListViewItem : public QStandardItem
{
public:
    explicit TestListViewItem();
    explicit TestListViewItem(const QIcon &icon, const QIcon &icon_hover, const QString &text);

    QIcon Img;
    QIcon Img_hover;
};


#endif // ITEMDEF_H
