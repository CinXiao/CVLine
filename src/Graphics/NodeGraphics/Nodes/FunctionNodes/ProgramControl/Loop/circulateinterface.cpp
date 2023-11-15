#include "circulateinterface.h"

CirculateInterface::CirculateInterface(QPointF pos):Node(Node::ProgrammeLoopControlNode, pos)
{


}

void CirculateInterface::CirculateInterRun(QList<PortInfo> portnodeinfolist)
{
    for(auto i:portnodeinfolist)
    {

        PortInfo portInfo=i;


        //拿到这个节点所有已经连接的输入端口连接的端口节点 信息 并且输入端口的节点是没有执行完成的
        QList<Port*>inports =portInfo.node->GetConnectedInport();

        //挑选没有执行的端口节点信息
        QList<Port*> notExPortList;
        std::copy_if(inports.begin(),inports.end(),std::back_inserter(notExPortList),[this](Port*port)
                     {
                         PortInfo info=GetNodeAndPortByPort(port);
                         return !info.node->IsExecuted;
                     });
        //获取没有执行完成的节点的端口节点信息
        QList<PortInfo> NotExportinfo;
        for(int i=0;i<notExPortList.count();++i)
        {
            Port *port=notExPortList[i];
            PortInfo info=GetNodeAndPortByPort(port);
            if(!info.IsEmpty())
                NotExportinfo.append(info);
        }

        //递归执行之前未执行的节点信息  节点输入口的节点
        CirculateInterRun(NotExportinfo);

        //该节点没有执行就执行该节点
        if( !portInfo.node->IsExecuted)
        {
            //如果是循环节点，则先执行循环节点的循环体逻辑
            if(dynamic_cast<CirculateInterface*>(portInfo.node)!=nullptr)
            {
                //循环体逻辑执行
                CirculateInterface *cirnode=dynamic_cast<CirculateInterface*>(portInfo.node);
                    //把连接信息传给循环体
                cirnode->PortLineInfoList=PortLineInfoList;
                cirnode->executeCirculate();
            }


            //执行改节点的运算逻辑
            portInfo.node->NodeRun();

            //重置节点执行，方便下一次循环才会继续执行这个节点
            i.node->IsExecuted=false;
        }

        //这个时候已经算出来节点输出端口的值了
        //获取这个节点的输出端口列表，遍历列表   （已连接的输出端口列表）
        QList<Port*>outports =portInfo.node->GetConnectedOutport();
        for(int i=0;i<outports.count();i++)
        {

            Port* outPort=outports[i];
            QList<PortInfo> connectinportlist=GetNodeAndPortListByPort(outPort);

            //获取与这个节点输出端口拿到连接的输入端口，给输入端口赋值
            //遍历所有与端口连接的输入端口，把端口的值给各个输入端口
            for(auto i:connectinportlist)
            {
                PortInfo inportinfo=i;
                //把输出端口的值给与这个端口连接的输入端口
                //类型检测
                if(inportinfo.port->Data.type()==outPort->Data.type())
                    inportinfo.port->Data= outPort->Data;
                else
                    qDebug()<<"端口类型异常："<<inportinfo.port->Data<<outPort->Data;

            }
        }
        //拿到这个节点程序控制输出的端口和节点连接信息列表
        QList<PortInfo> portnodelist=GetOutStreamPortInfoByNode(portInfo.node);
        CirculateInterRun(portnodelist);
    }
}


QList<PortInfo> CirculateInterface::GetOutStreamPortInfoByNode(Node *node)
{
    //默认会返回所有控制输出节点
    QList<PortInfo> PortInfolist;
    //拿到节点控制端口信息
    StreamPortinfo stream=node->GetStreamInfo();

    //如果只有程序控制输入口或者无程序控制端口那么自然不会有与该节点程序控制输出端口连接的端口
    if(stream.streamState==StreamPortinfo::NotStream||stream.streamState==StreamPortinfo::OnlyInStream)
        return PortInfolist;

    //遍历控制输出端口
    for(auto i:stream.OutStreamPortList)
    {
        //拿到其中一个输出端口连接的端口列表
        QList<PortInfo> outstreamportlist=GetNodeAndPortListByPort(i);
        //将这个输出端口连接的段口列表添加到返回列表中
        std::copy(outstreamportlist.begin(),outstreamportlist.end(),std::back_inserter(PortInfolist));
    }


    return PortInfolist;
}

PortInfo CirculateInterface::GetNodeAndPortByPort(Port *port)
{
    PortInfo  portInfo;
    //拿到和这个端口连接的所有端口和节点信息
    for( auto info:PortLineInfoList)
    {
        if(info.PortInfo1.port==port||info.PortInfo2.port==port)
        {
            portInfo=info.GetOtherPortNodeInfoByPort(port);
        }
    }
    return portInfo;
}

QList<PortInfo> CirculateInterface::GetNodeAndPortListByPort(Port *port)
{
    //拿到和这个端口连接的所有端口和节点信息
    QList<PortInfo> result;
    for( auto info:PortLineInfoList)
    {
        if(info.PortInfo1.port==port||info.PortInfo2.port==port)
            result.append(info.GetOtherPortNodeInfoByPort(port));
    }

    return result;
}
