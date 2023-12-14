#ifndef SET_H
#define SET_H


#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"


class Set:public Node
{
public:
    Set(QPointF pos=QPointF(0,0));

    TextInput* varNameText;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void execute();

};

#endif // SET_H
