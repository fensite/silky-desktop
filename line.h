#ifndef LINE_H
#define LINE_H

#endif // LINE_H
#include<QStyledItemDelegate>
#include<QTableView>
#include<QPainter>
#include<QStyle>
#include<QStyleOptionViewItemV4>
#include<QPen>
#include<QModelIndex>
#include<QColor>
#include<QRgb>


class QLineDelegate : public QStyledItemDelegate
{
public:
    QLineDelegate(QTableView* tableView)
    {
        int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
        QColor gridColor = static_cast<QRgb>(gridHint);
        pen = QPen(gridColor, 0, tableView->gridStyle());
        view = tableView;
    }
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        QStyledItemDelegate::paint(painter, option, index);
        QPen oldPen = painter->pen();
        painter->setPen(pen);
        painter->drawLine(option.rect.topRight(), option.rect.bottomRight());//显示垂直网格线
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());//显示水平网格线
        painter->setPen(oldPen);
    }
private:
    QPen pen;
    QTableView* view;
};
