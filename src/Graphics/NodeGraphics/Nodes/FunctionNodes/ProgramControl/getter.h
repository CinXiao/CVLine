#ifndef GETTER_H
#define GETTER_H

#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"


class Getter : public Node
{
public:
    Getter(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);

    TextInput* varNameText;
    void execute();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // GETTER_H
