#ifndef GETIMAGEINFO_H
#define GETIMAGEINFO_H
#include "src/Graphics/NodeGraphics/node.h"


#include <QDialog>
#include <QLabel>

class GetImageInfo:public Node
{
public:
    GetImageInfo(QPointF pos=QPointF(0,0));
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QImage Image;
    void execute();
};

#endif // GETIMAGEINFO_H
