#ifndef BINARIZATION_H
#define BINARIZATION_H

#include "src/NodeGraphics/node.h"
#include <QImage>
class Binarization:public Node
{
public:
    Binarization(QPointF pos);
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image;
    void execute();
};

#endif // BINARIZATION_H
