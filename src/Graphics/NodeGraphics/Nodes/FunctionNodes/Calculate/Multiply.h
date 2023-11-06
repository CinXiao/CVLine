#ifndef MUL_H
#define MUL_H

#include "src/Graphics/NodeGraphics/node.h"


class Multiply:public Node
{
public:
    Multiply(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();



};

#endif // ADD_H
