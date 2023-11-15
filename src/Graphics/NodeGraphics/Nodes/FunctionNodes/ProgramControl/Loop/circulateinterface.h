#ifndef CIRCULATEINTERFACE_H
#define CIRCULATEINTERFACE_H

#include "src/Graphics/NodeGraphics/node.h"
#include "src/Entity/Relations/PortInfo.h"
#include "src/Entity/Relations/LineInfo.h"

class CirculateInterface: public Node
{
public:
    CirculateInterface(QPointF pos=QPointF(0,0));
    virtual void executeCirculate()=0;
    QList<LineInfo> PortLineInfoList;


    void CirculateInterRun(QList<PortInfo> portnodeinfolist);
    QList<PortInfo> GetOutStreamPortInfoByNode(Node *node);
    QList<PortInfo> GetNodeAndPortListByPort(Port *port);
    PortInfo GetNodeAndPortByPort(Port *port);
};

#endif // CIRCULATEINTERFACE_H
