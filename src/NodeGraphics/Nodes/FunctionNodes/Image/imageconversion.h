#ifndef IMAGECONVERSION_H
#define IMAGECONVERSION_H

#include "src/NodeGraphics/node.h"
class ImageConversion:public Node
{
public:
    ImageConversion(QPointF pos=QPointF(0,0));
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image;
    void execute();
};

#endif // IMAGECONVERSION_H
