#include "NodeManager.h"

NodeManager::NodeManager(QGraphicsView *view):view(view)
{

}

PortInfo NodeManager::GetPortByPos(QPoint pos)
{
    PortInfo result;
    QGraphicsItem* clickedItem = view->itemAt(pos);

    if (clickedItem != nullptr)
    {
        Node *node=dynamic_cast<Node*>(clickedItem);
            //如果获取到节点
        if(node!=nullptr)
        {
            //尝试获取节点点击位置的端口
            Port *port=node->GetPortByPos(node->mapFromScene(view->mapToScene(pos)));
            if(port!=nullptr)
            {
                result.node=node;
                result.port=port;
            }
        }
    }
    return result;
}

Node* NodeManager::GetNodeByPos(QPoint pos)
{
    QGraphicsItem* clickedItem = view->itemAt(pos);
    if (clickedItem != nullptr)
    {
        Node *node=dynamic_cast<Node*>(clickedItem);
            //如果获取到节点
        if(node!=nullptr)
        {
            return node;
        }
    }
    return nullptr;
}

QList<PortInfo> NodeManager::GetNodeAndPortListByPort(Port *port)
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

   //获取连接到节点上输入端口上的所有端口信息
QList<PortInfo> NodeManager::GetConnectedInPortInfo(Port *port)
{
    QList<PortInfo> result;
    for( auto info:PortLineInfoList)
    {
        if(info.PortInfo1.port==port||info.PortInfo2.port==port)
            result.append(info.GetOtherPortNodeInfoByPort(port));
    }

    return result;
}

PortInfo NodeManager::GetNodeAndPortByPort(Port *port)
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

QList<PortInfo> NodeManager::GetOutStreamPortInfoByNode(Node *node)
{
    QList<PortInfo> PortInfolist;
    //拿到节点控制端口信息
    StreamPortinfo stream=node->GetStreamInfo();

    //如果只有程序控制输入口或者无程序控制端口那么自然不会有与该节点程序控制输出端口连接的端口
    if(stream.streamState==StreamPortinfo::NotStream||stream.streamState==StreamPortinfo::OnlyInStream)
        return PortInfolist;

    //通过端口拿到与他连接的另外的端口信息列表
    PortInfolist=GetNodeAndPortListByPort(stream.OutStreamPort);

    return PortInfolist;
}

PortInfo NodeManager::GetInStreamPortInfoByNode(Node *node)
{
    PortInfo info;

    QList<PortInfo> PortInfolist;
    //拿到节点控制端口信息
    StreamPortinfo stream=node->GetStreamInfo();

    //如果只有程序控制输出口或者无程序控制端口那么自然不会有与该节点程序控制输出端口连接的端口
    if(stream.streamState==StreamPortinfo::NotStream||stream.streamState==StreamPortinfo::OnlyOutStream)
        return info;

    PortInfolist=GetNodeAndPortListByPort(stream.OutStreamPort);

    if(!PortInfolist.isEmpty())
        info=PortInfolist[0];
    return info;
}

bool NodeManager::EnableConnectCheck(PortInfo info1, PortInfo info2)
{
    //端口是否能连接匹配
    if(!info1.port->PortEnableConnectCheck(info2.port->portType))
        return false;
    //回环检测，不能节点输入连自己的输出
    if(info1.node==info2.node)
        return false;
    //输入输出单调性检测   一个输出可以连多个输入，但是一个输入只能连一个输出
    if(info1.port->IsConnected&&info1.port->portType==Port::Input)
        return false;
    if(info2.port->IsConnected&&info2.port->portType==Port::Input)
        return false;
    if(info1.port->IsConnected&&info1.port->portType==Port::InStream)
        return false;
    if(info2.port->IsConnected&&info2.port->portType==Port::InStream)
        return false;

    return true;
}

bool NodeManager::CycleCheck()
{


    return true;
}

void NodeManager::UpdateLine(QPoint pos)
{
    //尝试拿到这个点的节点
     Node *node=GetNodeByPos(pos);

    if(node==nullptr)
        return;

    //待更新的信息表
    QList<LineInfo> updatainfolist;

    //查找该节点的端口连接信息
     std::copy_if(PortLineInfoList.begin(),PortLineInfoList.end(),std::back_inserter(updatainfolist),[node](const LineInfo& info){
       return info.PortInfo1.node==node|| info.PortInfo2.node==node;
    });

    //更新该节点的端口连接信息
    for(auto i:updatainfolist)
    {

        QPointF startPos=i.PortInfo1.node->mapToScene(i.PortInfo1.port->portRect.center());
        QPointF endPos=i.PortInfo2.node->mapToScene(i.PortInfo2.port->portRect.center());
        i.PortInfo1.port->IsConnected=true;
        i.PortInfo2.port->IsConnected=true;
        i.line->UpdatePoint(startPos,endPos);
    }



}

void NodeManager::AddRelation(LineInfo info)
{
    PortLineInfoList.append(info);
}

void NodeManager::Run()
{
    //找到开始节点
    auto it =std::find_if(NodeList.begin(),NodeList.end(),[](Node *node){
        return node->nodeType==Node::StartNode;
    });

    if(it==NodeList.end())
        return;

    //拿到开始节点
    Node* startNode = *it;

    //检测输入输出端口是不是回环

    //通过开始节点拿到和它程序控制线连接的下一个端口和节点信息列表
    QList<PortInfo> portnodeinfolist=GetOutStreamPortInfoByNode(startNode);

    //回环检测
    if(CycleCheck())
    {
        //节点执行
        NodeRun(portnodeinfolist);
    }
    //刷新各个节点已经执行标识
    NodeReflush();


}



void NodeManager::NodeRun(QList<PortInfo> portnodeinfolist)
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
         NodeRun(NotExportinfo);

        //该节点没有执行就执行该节点
        if( !portInfo.node->IsExecuted)
        {
            //执行改节点的运算逻辑
            portInfo.node->execute();
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
                    inportinfo.port->Data= outPort->Data;
             }
          }
        //拿到这个节点程序控制输出的端口和节点连接信息列表
        QList<PortInfo> portnodelist=GetOutStreamPortInfoByNode(portInfo.node);
        NodeRun(portnodelist);
    }
}

void NodeManager::NodeReflush()
{
    for(auto i:NodeList)
    {
        i->IsExecuted=false;
    }
}

void NodeManager::AddNode(Node *node)
{
    NodeList.append(node);
    view->scene()->addItem(node);
}
