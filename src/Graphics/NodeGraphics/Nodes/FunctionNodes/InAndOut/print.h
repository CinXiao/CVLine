#ifndef PRINT_H
#define PRINT_H


#include "src/Graphics/NodeGraphics/node.h"
class Print:public Node
{
public:
    Print(QPointF pos);
    virtual void execute();
};

#endif // PRINT_H
