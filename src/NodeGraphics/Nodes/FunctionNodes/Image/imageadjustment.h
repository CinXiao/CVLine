#ifndef IMAGEADJUSTMENT_H
#define IMAGEADJUSTMENT_H
#include "src/NodeGraphics/node.h"
class ImageAdjustment:public Node
{
public:
    ImageAdjustment(QPointF pos=QPointF(0,0));
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image;
    void execute();
};

#endif // IMAGEADJUSTMENT_H
