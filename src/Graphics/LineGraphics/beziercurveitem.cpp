#include "beziercurveitem.h"

#include <QGraphicsSceneHoverEvent>

BezierCurveItem::BezierCurveItem(const QPointF& startPoint, const QPointF& endPoint)
    : start(startPoint), end(endPoint)
{

}

QRectF BezierCurveItem::boundingRect() const
{
    // 返回包围贝塞尔曲线的矩形
    qreal minX = qMin(qMin(start.x(), end.x()), qMin(control1.x(), control2.x()));
    qreal minY = qMin(qMin(start.y(), end.y()), qMin(control1.y(), control2.y()));
    qreal maxX = qMax(qMax(start.x(), end.x()), qMax(control1.x(), control2.x()));
    qreal maxY = qMax(qMax(start.y(), end.y()), qMax(control1.y(), control2.y()));
    return QRectF(minX, minY, maxX - minX, maxY - minY);
}

void BezierCurveItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    setZValue(-1);
    if(start.x()>=end.x())
    {
        control1= QPointF (start.x() - 30, start.y()); // 偏离起点的第一个控制点
        control2= QPointF (end.x() +30, end.y());   // 偏离终点的第二个控制点
    }else
    {
         control1= QPointF (start.x() + 60, start.y()); // 偏离起点的第一个控制点
         control2= QPointF (end.x() -60, end.y());   // 偏离终点的第二个控制点
    }
    // 贝塞尔曲线
    QPainterPath bezierPath;
    bezierPath.moveTo(start);
    bezierPath.cubicTo(control1, control2, end);
    painter->setPen(QPen(LineColor, linewidth));
    painter->drawPath(bezierPath);
}

void BezierCurveItem::UpdatePoint(const QPointF &startPoint, const QPointF &endPoint)
{
    start=startPoint;
    end=endPoint;
    update();
}

void BezierCurveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsItem::mousePressEvent(event);
}


