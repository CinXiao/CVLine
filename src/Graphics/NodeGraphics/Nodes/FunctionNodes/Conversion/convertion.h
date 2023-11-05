#ifndef CONVERTION_H
#define CONVERTION_H


#include "src/Graphics/NodeGraphics/node.h"
class Convertion:public Node
{
public:
    Convertion(Port::PortDataType port1type,Port::PortDataType port2type,QPointF pos=QPointF(0,0));
    void execute();

};

#endif // CONVERTION_H
