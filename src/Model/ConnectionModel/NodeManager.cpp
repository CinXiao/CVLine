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

PortInfo NodeManager::GetInStreamPortInfoByNode(Node *node)
{
    PortInfo info;

    QList<PortInfo> PortInfolist;

    //拿到该节点控制端口信息
    StreamPortinfo stream=node->GetStreamInfo();

    //如果只有程序控制输出口或者无程序控制端口那么自然不会有与该节点程序控制输出端口连接的端口
    if(stream.streamState==StreamPortinfo::NotStream||stream.streamState==StreamPortinfo::OnlyOutStream)
        return info;

  //  PortInfolist=GetNodeAndPortListByPort(stream.OutStreamPort);

    if(!PortInfolist.isEmpty())
        info=PortInfolist[0];
    return info;
}

bool NodeManager::PortTypeCheck(PortInfo info1, PortInfo info2)
{
    //端口类型是否能连接匹配
    if(!info1.port->PortTypeCheck(info2.port->portType))
        return false;
    //回环检测，不能节点输入连自己的输出
    if(info1.node==info2.node)
        return false;

    return true;
}

bool NodeManager::PortMonotonicityCheck(PortInfo info1, PortInfo info2)
{
    //端口类型单调性检测   一个数据输出可以连多个数据输入，但是一个数据输入只能连一个数据输出   程序控制则只能输入输出都只能连一个
    if(info1.port->IsConnected&&info1.port->portType==Port::Input)
        return false;
    if(info2.port->IsConnected&&info2.port->portType==Port::Input)
        return false;


    if(info1.port->IsConnected&&info1.port->portType==Port::InStream)
        return false;
    if(info2.port->IsConnected&&info2.port->portType==Port::InStream)
        return false;
    if(info1.port->IsConnected&&info1.port->portType==Port::OutStream)
        return false;
    if(info2.port->IsConnected&&info2.port->portType==Port::OutStream)
        return false;

    return true;
}

bool NodeManager::PortDataTypeCheck(PortInfo info1, PortInfo info2)
{


    //端口数据类型是否能匹配
    return info1.port->portDataType==info2.port->portDataType;
}



bool NodeManager::CycleCheck()
{

    return true;
}

void NodeManager::UpdateNode(QPoint pos)
{
    //尝试拿到这个点的节点
     Node *node=GetNodeByPos(pos);
    UpDateNode(node);
}

void NodeManager::UpDateNode(Node *node)
{
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

void NodeManager::UpDateSelectedNode()
{
     if(view->scene()->selectedItems().count()==0)
        return;
     QList<QGraphicsItem *> selecteditem=view->scene()->selectedItems();
     QList<QGraphicsItem *> nodelist;

     std::copy_if(selecteditem.begin(),selecteditem.end(),std::back_inserter(nodelist),[](QGraphicsItem * item){
         return dynamic_cast<Node *>(item)!=nullptr;
     });

     for(auto node:nodelist)
     {
        UpDateNode(dynamic_cast<Node *>(node));
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

    //通过开始节点拿到和它控制线连接的下一个端口和节点信息列表
    QList<PortInfo> portnodeinfolist=GetOutStreamPortInfoByNode(startNode);

    //回环检测
    if(CycleCheck())
    {
        //节点执行
        NodeRun(portnodeinfolist);
    }
    //刷新各个节点已经执行标识
    NodeReflush();

    //刷新场景
    view->scene()->update();
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
                    //类型检测
                    if(inportinfo.port->Data.type()==outPort->Data.type())
                        inportinfo.port->Data= outPort->Data;
                    else
                        qDebug()<<"端口类型异常："<<inportinfo.port->Data<<outPort->Data;
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

void NodeManager::PortConnect(PortInfo port1,PortInfo port2)
{
    //获取开始点和结束点，即鼠标点击的位置和释放的位置
    QPointF startPoint(port1.node->mapToScene(port1.port->portRect.center()));
    QPointF endPoint(port2.node->mapToScene(port2.port->portRect.center()));
    //线
    BezierCurveItem* curveItem = new BezierCurveItem(startPoint, endPoint);
    //这时候线的颜色是port1的端口颜色，所已port1要是鼠标点击的端口
    curveItem->LineColor=port1.port->portColor;
    //端口和连线信息
    LineInfo portline;
    portline.line=curveItem;
    portline.PortInfo1=port1;
    portline.PortInfo2=port2;
    //添加线
    view->scene()->addItem(curveItem);
    //添加一条节点和线的连接关系
     AddRelation(portline);

}

void NodeManager::DeletePortConnect(PortInfo portinfo1)
{

     auto i=std::find_if(PortLineInfoList.begin(),PortLineInfoList.end(),[portinfo1](const LineInfo &lineinfo)
     {
         return lineinfo.PortInfo1.port==portinfo1.port||lineinfo.PortInfo2.port==portinfo1.port;
     });

     if(i!=PortLineInfoList.end())
     {
        LineInfo lineinfo=*i;
        // 计算迭代器位置
        const auto index = std::distance(PortLineInfoList.begin(), i);
        //从场景移除连接线  删除线
          BezierCurveItem *line=PortLineInfoList[index].line;
             delete line;
          line=nullptr;
          //更新两个端口连接状态
          lineinfo.PortInfo1.port->IsConnected=false;
          lineinfo.PortInfo2.port->IsConnected=false;

        // 删除找到连线信息
        PortLineInfoList.erase(PortLineInfoList.constBegin() + index);

     }


}
