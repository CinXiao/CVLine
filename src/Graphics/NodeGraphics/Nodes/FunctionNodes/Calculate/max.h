#ifndef MAX_H
#define MAX_H


#include "src/Graphics/NodeGraphics/node.h"
class Max:public Node
{
public:
    Max(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();

};
#endif // MAX_H
