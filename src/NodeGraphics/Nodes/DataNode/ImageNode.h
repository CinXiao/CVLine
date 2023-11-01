#ifndef IMAGENODE_H
#define IMAGENODE_H

#include <QVariant>
#include<QDebug>
#include <QImage>
#include<QObject>
#include "src/NodeGraphics/node.h"
#include "src/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"
class ImageNode: public Node
{
public:
    ImageNode(QPointF pos=QPointF(0,0));
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QImage Image{"C:\\Users\\Sun\\Pictures\\Image\\anno.jpg"};

    void execute();
};

#endif // IMAGENODE_H
