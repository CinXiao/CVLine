#ifndef GETIMAGEINFO_H
#define GETIMAGEINFO_H
#include "src/Graphics/NodeGraphics/node.h"

class GetImageInfo:public Node
{
public:
    GetImageInfo(QPointF pos=QPointF(0,0));
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image;
    void execute();
};

#endif // GETIMAGEINFO_H
