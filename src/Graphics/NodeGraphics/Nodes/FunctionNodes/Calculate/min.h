#ifndef MIN_H
#define MIN_H

#include "src/Graphics/NodeGraphics/node.h"

class Min:public Node
{
public:
    Min(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();
};

#endif // MIN_H
