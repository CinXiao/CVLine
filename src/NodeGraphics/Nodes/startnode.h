#ifndef STARTNODE_H
#define STARTNODE_H

#include "src/NodeGraphics/node.h"




class StartNode : public Node
{
public:
    StartNode(QPointF pos=QPointF(0,0));
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

};

#endif // STARTNODE_H
