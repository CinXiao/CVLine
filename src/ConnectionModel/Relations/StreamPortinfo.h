#ifndef STREAMPORTINFO_H
#define STREAMPORTINFO_H

#include "src/NodeGraphics/Port/Port.h"


class StreamPortinfo
{

public:
    enum StreamState {NotStream,FullPort,OnlyInStream, OnlyOutStream};
    Port *InStreamPort{nullptr};
    //节点会有多个程序控制输出端口
    Port *OutStreamPort;
    StreamState streamState;
    StreamPortinfo( Port *InStreamPort,Port *OutStreamPort):InStreamPort(InStreamPort),OutStreamPort(OutStreamPort)
    {
        if(InStreamPort==nullptr&&OutStreamPort==nullptr)
            streamState=NotStream;
        if(InStreamPort!=nullptr&&OutStreamPort!=nullptr)
            streamState=FullPort;
        if(InStreamPort!=nullptr&&OutStreamPort==nullptr)
            streamState=OnlyInStream;
        if(InStreamPort==nullptr&&OutStreamPort!=nullptr)
            streamState=OnlyOutStream;
    }
};



#endif // STREAMPORTINFO_H
