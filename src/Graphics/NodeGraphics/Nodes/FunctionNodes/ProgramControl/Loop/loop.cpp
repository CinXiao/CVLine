#include "loop.h"




Loop::Loop(QPointF pos):CirculateInterface(pos)
{
    NodeName="Loop";

    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //循环体内容
    AddPort(new Port(1,"循环体",Port::OutStream,Port::Stream));


    //数据端口
    AddPort(new Port(1,"循环次数",Port::Input,Port::Int,0));

}

QList<Port *> Loop::OutputStreamLogicExecution()
{
    //第二个控制输出端口是循环体端口，不添加到输出控制端口列表
    QList<Port*>outList;
    outList.append(GetPort(0,Port::OutStream));
    return outList;
}

void Loop::executeCirculate()
{


    Port*port=GetPort(1,Port::OutStream);
    PortInfo info;
    //找到改端口连接的节点
    if(port->IsConnected)
    {

        for(auto i:PortLineInfoList)
        {
            if(i.PortInfo1.port==port||i.PortInfo2.port==port)
            {
                info=i.GetOtherPortNodeInfoByPort(port);
            }
        }

        //找到执行循环体端口连接的节点
        QList<PortInfo> portinfo;
        portinfo.append(info);
        //如果循环体端口连接了节点就执行循环
        if(info.node!=nullptr)
        {

            int circulatecount=GetPortValue(1,Port::Input).toInt();
            //执行指定循环次数
            for(int i=0;i<circulatecount;++i)
            CirculateInterRun(portinfo);


        }
    }






}

