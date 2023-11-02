#ifndef READIMAGE_H
#define READIMAGE_H


#include <QFileDialog>

#include "src/Graphics/NodeGraphics/node.h"
#include <QImage>
#include <QList>
class ReadImage:public Node
{
public:
    ReadImage(QPointF pos);
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QImage CurrentImage;
    QList<QImage> ImageList;
    void execute();
};

#endif // READIMAGE_H
