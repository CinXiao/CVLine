#ifndef MOD_H
#define MOD_H


#include "src/Graphics/NodeGraphics/node.h"
class Mod:public Node
{
public:
    Mod(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();
};

#endif // MOD_H
