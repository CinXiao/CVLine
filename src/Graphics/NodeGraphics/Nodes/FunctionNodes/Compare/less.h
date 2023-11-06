#ifndef LESS_H
#define LESS_H


#include "src/Graphics/NodeGraphics/node.h"
namespace Compare {


class less:public Node
{
public:
    less(QPointF pos=QPointF(0,0),Port::PortDataType datatype=Port::Int);
    void execute();
};
}
#endif // LESS_H
