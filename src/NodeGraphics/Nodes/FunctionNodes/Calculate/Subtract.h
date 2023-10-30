#ifndef SUBTRACT_H
#define SUBTRACT_H

#include "src/NodeGraphics/node.h"
class Subtract:public Node
{
public:
    Subtract(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();

};

#endif // SUBTRACT_H
