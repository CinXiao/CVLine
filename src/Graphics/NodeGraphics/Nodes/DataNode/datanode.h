#ifndef DATANODE_H
#define DATANODE_H
#include<QDebug>
#include<QObject>

#include "src/Graphics/NodeGraphics/node.h"
#include "src/Graphics/NodeGraphics/Nodes/DataNode/TextInput/textinput.h"
class DataNode: public Node
{
public:
    DataNode(QPointF pos=QPointF(0,0), QVariant Dat=0,Port::PortDataType datatype=Port::Int);

    void execute();


    TextInput* textItem;

};

#endif // DATANODE_H
