#ifndef ADD_H
#define ADD_H

#include "src/NodeGraphics/node.h"


class AddNode:public Node
{
public:
    AddNode(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();



};

#endif // ADD_H
