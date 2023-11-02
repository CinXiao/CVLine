#ifndef STREAMPORTINFO_H
#define STREAMPORTINFO_H

#include "src/Graphics/NodeGraphics/Port/Port.h"

class StreamPortinfo
{

public:
    enum StreamState {NotStream,InStreamAndOutStream,OnlyInStream, OnlyOutStream};
    Port *InStreamPort{nullptr};
    //节点会有多个程序控制输出端口
    QList<Port*>OutStreamPortList;
    StreamState streamState;
    StreamPortinfo( Port *InStreamPort, QList<Port*> OutStreamPortList):InStreamPort(InStreamPort),OutStreamPortList(OutStreamPortList)
    {
        if(InStreamPort==nullptr&&OutStreamPortList.count()==0)
            streamState=NotStream;
        if(InStreamPort!=nullptr&&OutStreamPortList.count()!=0)
            streamState=InStreamAndOutStream;
        if(InStreamPort!=nullptr&&OutStreamPortList.count()==0)
            streamState=OnlyInStream;
        if(InStreamPort==nullptr&&OutStreamPortList.count()!=0)
            streamState=OnlyOutStream;
    }
};



#endif // STREAMPORTINFO_H
