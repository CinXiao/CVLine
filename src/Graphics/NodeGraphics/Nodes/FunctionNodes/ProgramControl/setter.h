#ifndef SETTER_H
#define SETTER_H


#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"


class Setter:public Node
{
public:
    Setter(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);

    TextInput* varNameText;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void execute();

};

#endif // SETTER_H
