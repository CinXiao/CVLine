#ifndef IMAGENODE_H
#define IMAGENODE_H

#include <QVariant>
#include<QDebug>
#include <QImage>
#include<QObject>
#include<QFileDialog>
#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"
class ImageNode: public Node
{
public:
    ImageNode(QPointF pos=QPointF(0,0));
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image{""};

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void execute();
};

#endif // IMAGENODE_H
