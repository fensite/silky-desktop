#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyle>
#include <QSize>
#include <QEvent>
#include <QDebug>
#include <QPropertyAnimation>
#include "itemdef.h"
#include "itemdelegate.h"
#include "TestListView.h"

TestItemDelegate::TestItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void TestItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    if(index.isValid())
    {
        if(option.state.testFlag(QStyle::State_MouseOver))
        {
            QRectF rect;
            rect.setX(option.rect.x());
            rect.setY(option.rect.y());
            rect.setWidth( option.rect.width()-1);
            rect.setHeight(option.rect.height()-1);

           //QPainterPath画圆角矩形
            const qreal radius = 7;
            QPainterPath path;
            path.moveTo(rect.topRight() - QPointF(radius, 0));
            path.lineTo(rect.topLeft() + QPointF(radius, 0));
            path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
            path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
            path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
            path.lineTo(rect.bottomRight() - QPointF(radius, 0));
            path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
            path.lineTo(rect.topRight() + QPointF(0, radius));
            path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));
            painter->setPen(QPen(Qt::green));
            painter->setPen(QPen());

            QBrush brush;

            brush.setColor(QColor(255,255,255,0.6));
            brush.setStyle(Qt::SolidPattern);//画刷填充样式
            painter->setBrush(brush);
            painter->drawPath(path);

        }
    }

    QStyledItemDelegate::paint(painter, option, index);
}
