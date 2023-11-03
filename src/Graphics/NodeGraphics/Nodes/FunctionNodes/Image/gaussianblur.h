#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H
#include "src/Graphics/NodeGraphics/node.h"
#include"src/Utils/ImageConversionUtil.h"

class GaussianBlur:public Node
{
public:
    GaussianBlur(QPointF pos);
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image;
    void execute();
};

#endif // GAUSSIANBLUR_H
