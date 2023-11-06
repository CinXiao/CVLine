#ifndef DIVISION_H
#define DIVISION_H

#include "src/Graphics/NodeGraphics/node.h"
class Division:public Node
{
public:
    Division(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();

};

#endif // DIVISION_H
