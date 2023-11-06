#ifndef EQUAL_H
#define EQUAL_H


#include "src/Graphics/NodeGraphics/node.h"
class equal:public Node
{
public:
    equal(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();
};

#endif // EQUAL_H
