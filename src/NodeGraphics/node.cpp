#include "node.h"


Node::Node(NodeType nodetype,QPointF pos):nodeType(nodetype)
{

    setPos(pos);
    setFlag(QGraphicsItem::ItemIsMovable, true);

    // 添加一个变量来跟踪节点的高亮状态
    isHighlighted = false;


    TitleColor=TitleColorMap[nodeType];

}

QRectF Node::boundingRect() const
{

    //拿到最多端口的数量
    uint   inputcount=GetInputCount();
    uint   outputcount=GetOutCount();
    //节点高度是端口数量*50
    uint height=std::max(inputcount,outputcount);
    uint normalheight=50;
    return QRectF(0, 0, 150,std::max(height*50,normalheight));
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //不设置笔
    painter->setPen(Qt::NoPen);
    // 根据高亮状态设置节点的颜色
    if (isHighlighted) {
          painter->setBrush(QColor(20,20,20,240));
    } else {
          painter->setBrush(QColor(50,50,50,240));
    }
    // 使用 drawRoundedRect 绘制圆角矩形
    qreal cornerRadius = 10.0; // 圆角的半径
    painter->drawRoundedRect(boundingRect(), cornerRadius, cornerRadius);


    // 绘制标题栏
    QRectF titleBarRect(0, 0, boundingRect().width(), 20);
    painter->setBrush(TitleColor); // 设置标题栏的颜色
    painter->drawRoundedRect(titleBarRect,5,5);


    // 添加标题文本
    QFont titleFont = painter->font();
    titleFont.setBold(true);
    titleFont.setPixelSize(15);
    painter->setFont(titleFont);
    painter->setPen(Qt::white); // 设置标题文本颜色
    painter->drawText(titleBarRect, Qt::AlignCenter, NodeName);

    // 画端口
    for(const auto &i:portList)
    {

          //输入输出端口
          if(i->portType==Port::Input||i->portType==Port::Output)
          {
              //未连接画实心圆
              if(!i->IsConnected)
              {

                  //设置笔，不设置刷子画空心圆
                  QPen pen(i->portColor,2.3);
                  painter->setPen(pen);
                  painter->setBrush(Qt::NoBrush);
                  painter->drawEllipse(i->portRect);
              }//已连接画实心圆
              else
              {
                  //不设置笔，画实心圆
                  painter->setPen(Qt::NoPen);
                  painter->setBrush(QColor(i->portColor));
                  painter->drawEllipse(i->portRect);

              }
              //设置笔用于画文本
              painter->setPen(Qt::white);
              //文本
              //如果没有连接绘制端口名字，有数据绘制数据值
              if(!i->IsConnected)
              {
                  painter->drawText(i->portTextRect,i->TextAlign,i->Name);
              }else
              {
                   painter->drawText(i->portTextRect,i->TextAlign,i->Data.toString());
              }
          }
          //流程控制输入输出端口
          if(i->portType==Port::InStream||i->portType==Port::OutStream)
          {

              // 根据端口类型绘制向右的实心三角形或空心三角形
              QPolygonF triangle;
              triangle << QPointF(i->portRect.right(), i->portRect.center().y())
                       << QPointF(i->portRect.left(), i->portRect.top())
                       << QPointF(i->portRect.left(), i->portRect.bottom());

              if (!i->IsConnected) {
                  // 未连接，画空心三角形
                  QPen pen(i->portColor, 2.3);
                  painter->setPen(pen);
                  painter->setBrush(Qt::NoBrush);
                  painter->drawPolygon(triangle);
              } else {
                  // 已连接，画实心三角形
                  painter->setPen(Qt::NoPen);
                  painter->setBrush(i->portColor);
                  painter->drawPolygon(triangle);
              }

          }



    }





}

//添加端口
void Node::AddPort( Port *port)
{
    portList.push_back(port);
}

//给指定端口设置指定值
void Node::SetPortValue(uint portID, QVariant data, Port::PortType type)
{

    auto i=std::find_if(portList.begin(),portList.end(),[type,portID](Port* port){

        return port->ID==portID&&port->portType==type;

    });
    if(i!=portList.end())
    {
          Port *port=*i;
          port->Data=data;
    }


}

Port* Node::GetPort(uint portID, Port::PortType type)
{
    auto i=std::find_if(portList.begin(),portList.end(),[type,portID](Port* port){

        return port->ID==portID&&port->portType==type;


    });
    if(i!=portList.end())
    {
          return *i;
    }
    return nullptr;
}



void Node::SetInStreamPort()
{

    Port *port=new Port(-1,"",Port::InStream,Port::Stream);
    //端口类型不正确
    if(port->portType!=Port::InStream)
          return;

    auto it = std::find_if(portList.begin(), portList.end(), []( Port* port) {
        return port->portType==Port::InStream;
    });

    //找到了原本的流程输入口，已经有了，就不添加了
    if (it != portList.end())
    {
          return;
    }else //没找到了原本的流程输入口，直接设置流程输入口
    {
        AddPort(port);

    }

}


void Node::SetOutStreamPort()
{
    Port *port=new Port(-1,"",Port::OutStream,Port::Stream);
    //端口类型不正确
    if(port->portType!=Port::OutStream)
         return;

    auto it = std::find_if(portList.begin(), portList.end(), [](Port* port) {
        return port->portType==Port::OutStream;
    });

    //找到了原本的流程输入口，已经有了，就不添加了
    if (it != portList.end())
    {
         return;
    }else //没找到了原本的流程输入口，直接设置流程输入口
    {
        AddPort(port);
    }

}




StreamPortinfo Node::GetStreamInfo()
{


    Port *in{nullptr},*out{nullptr};
    auto in_it = std::find_if(portList.begin(), portList.end(), [](Port* port){
        return port->portType==Port::InStream;
    });
    if (in_it != portList.end())
    {
        in=*in_it;
    }
    auto out_it = std::find_if(portList.begin(), portList.end(), [](Port *port){
            return port->portType==Port::OutStream;
    });
    if (out_it != portList.end())
    {
        out=*out_it;
    }

    StreamPortinfo info(in,out);
    return info;
}



//检测是点是否在端口上
bool Node::CheckPortByPos(QPointF pos)
{
        //用到了any_of
        return std::any_of(portList.begin(), portList.end(), [pos]( Port* port) {
            return port->portRect.contains(pos);
        });
}

//获取包含点的端口
Port *Node::GetPortByPos(QPointF pos)
{
    //用到了find_if
    auto it = std::find_if(portList.begin(), portList.end(), [pos](Port* port) {
        return port->portRect.contains(pos);
    });
    //判空
    if (it != portList.end()) {
        return *it;
    }
    return nullptr;
}

uint Node::GetInputCount()const
{
    //使用了count_if
    return std::count_if(portList.begin(), portList.end(), [](  Port *port) {
        return port->portType==Port::Input;
    });
}

uint Node::GetOutCount()const
{
      //使用了count_if
    return std::count_if(portList.begin(), portList.end(), []( Port* port) {
        return port->portType==Port::Output;
    });
}

QList<Port*> Node::GetInport()
{
    QList<Port*> result;

    std::copy_if(portList.begin(),portList.end(),std::back_inserter(result),[]( Port* port)
        {

        return port->portType==Port::Input;
        }
    );
    return result;
}



QList<Port*> Node::GetConnectedInport()
{
    QList<Port*> result;

    std::copy_if(portList.begin(),portList.end(),std::back_inserter(result),[]( Port *port)
                 {

                     return port->portType==Port::Input&&port->IsConnected;
                 }
                 );
    return result;
}

QList<Port *> Node::GetOutport()
{
    QList<Port*> result;

    std::copy_if(portList.begin(),portList.end(),std::back_inserter(result),[]( Port* port)
                 {

                     return port->portType==Port::Output;
                 }
                 );
    return result;
}

QList<Port *> Node::GetConnectedOutport()
{
    QList<Port*> result;

    std::copy_if(portList.begin(),portList.end(),std::back_inserter(result),[]( Port *port)
                 {

                     return port->portType==Port::Output&&port->IsConnected;
                 }
                 );
    return result;
}



void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    static uint z=0;
    //设置置顶
    setZValue(++z);
    if(CheckPortByPos(event->pos()))
    {
        setFlag(QGraphicsItem::ItemIsMovable, false);
        setHighlighted(false);
    }
    else
    {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setHighlighted(true);
    }

     QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    setHighlighted(false);
     QGraphicsItem::mouseReleaseEvent(event);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseMoveEvent(event);
}



void Node::setHighlighted(bool highlight)
{
    if (isHighlighted != highlight)
    {
        isHighlighted = highlight;
        update();
    }
}



void Node::execute()
{

    IsExecuted=true;
}


