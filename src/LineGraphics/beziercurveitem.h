#ifndef BEZIERCURVEITEM_H
#define BEZIERCURVEITEM_H

#include <QPointF>
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>

//#include "src/NodeGraphics/node.h"

class BezierCurveItem : public QGraphicsItem
{
public:
    BezierCurveItem(const QPointF& startPoint, const QPointF& endPoint);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void UpdatePoint(const QPointF& startPoint, const QPointF& endPoint);
    QColor LineColor{Qt::blue};
private:
    QPointF start;
    QPointF end;
    QPointF control1;
    QPointF control2;

};


#endif // BEZIERCURVEITEM_H
