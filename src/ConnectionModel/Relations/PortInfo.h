#ifndef PORTINFO_H
#define PORTINFO_H
#include "src/NodeGraphics/node.h"
#include "src/LineGraphics/beziercurveitem.h"


//端口和这个端口所在的节点信息
class PortInfo
{
public:
    Node *node{nullptr};//端口所在的节点
    Port *port{nullptr};//端口
    bool IsEmpty()//判空
    {
        return node==nullptr||port==nullptr;
    }
};
#endif // PORTINFO_H
