#ifndef GREATER_H
#define GREATER_H


#include "src/Graphics/NodeGraphics/node.h"
class greater:public Node
{
public:
    greater(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();
};

#endif // GREATER_H
