#ifndef GET_H
#define GET_H

#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"


class Get : public Node
{
public:
    Get(QPointF pos=QPointF(0,0));

    TextInput* varNameText;
    void execute();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // GET_H
