#include "node.h"


Node::Node(NodeType nodetype,QPointF pos):nodeType(nodetype)
{

    setPos(pos);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    TitleColor=TitleColorMap[nodeType];
}

QRectF Node::boundingRect() const
{

    //拿到最多端口的数量
    uint   inputcount=GetInputCount();
    uint   outputcount=GetOutCount();
    //节点高度是端口数量*50
    uint height=std::max(inputcount,outputcount);
    uint normalheight=80;
    return QRectF(0, 0, 160,std::max(height*55,normalheight));
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    qreal cornerRadius = 10.0; // 圆角的半径
    qreal titlecornerRadius = 10.0; // 圆角的半径
    QRectF titleBarRect(0, 0, boundingRect().width(), 40);
    // 根据选中状态设置节点的颜色
    if (isSelected()) {
        //选中设置笔，描绘边框颜色
          QPen pen;
          pen.setColor(Qt::white);
          pen.setWidth(4);
        //调整标题
          titlecornerRadius=7;
          titleBarRect=QRectF(2, 2, boundingRect().width()-4, 36);
          painter->setPen(pen);
          painter->setBrush(QColor(50,50,50,240));
    } else {
          //没选中不设置笔
          painter->setPen(Qt::NoPen);
          painter->setBrush(QColor(70,70,70,240));
    }
    // 使用 drawRoundedRect 绘制圆角矩形(底部)

    painter->drawRoundedRect(boundingRect(), cornerRadius, cornerRadius);

    //不设置笔
    painter->setPen(Qt::NoPen);
    // 绘制标题栏
    QLinearGradient gradient(titleBarRect.topLeft(), titleBarRect.bottomLeft());
    gradient.setColorAt(0, TitleColor); // 起始颜色
    gradient.setColorAt(1, QColor(70,70,70,150));   // 终止颜色
    QBrush titleBarBrush(gradient);
    painter->setBrush(titleBarBrush); // 设置标题栏的颜色
    painter->drawRoundedRect(titleBarRect,titlecornerRadius,titlecornerRadius);



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

              QPen pen(i->portColor,5);
              pen.setCapStyle(Qt::RoundCap); // 设置线帽为圆滑
              pen.setJoinStyle(Qt::RoundJoin);
              painter->setPen(pen);
              //未连接画实心圆
              if(!i->IsConnected)
              {
                  //设置笔，不设置刷子画空心圆
                  painter->setBrush(Qt::NoBrush);
                  painter->drawEllipse(i->portRect);
              }//已连接画实心圆
              else
              {
                  //不设置笔，画实心圆
                  painter->setBrush(QColor(i->portColor));
                  painter->drawEllipse(i->portRect);

              }
              //设置笔用于画文本
              painter->setPen(Qt::white);
              painter->drawText(i->portTextRect,i->TextAlign,i->Data.toString());


          }
          //流程控制输入输出端口
          if(i->portType==Port::InStream||i->portType==Port::OutStream)
          {

              // 根据端口类型绘制向右的实心三角形或空心三角形
              QPolygonF triangle;
              triangle << QPointF(i->portRect.right(), i->portRect.center().y())
                       << QPointF(i->portRect.left(), i->portRect.top())
                       << QPointF(i->portRect.left(), i->portRect.bottom());

              QPen pen(i->portColor, 4);
              pen.setCapStyle(Qt::RoundCap); // 设置线帽为圆滑
              pen.setJoinStyle(Qt::RoundJoin);
              painter->setPen(pen);
              if (!i->IsConnected) {
                   //未连接画空心三角形
                  painter->setBrush(Qt::NoBrush);
                  painter->drawPolygon(triangle);
              } else {
                  // 已连接，画实心三角形
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

QVariant Node::GetPortValue(uint portID, Port::PortType type)
{
    return GetPort(portID,type)->Data;
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


void Node::SetPortDataType(uint portId, Port::PortType porttype, Port::PortDataType datatype)
{

    TitleColor=Port::PortColorMap[datatype];
    Port *port=GetPort(portId,porttype);
    port->portDataType=datatype;
    port->update();
}

//拿到控制端口信息表
StreamPortinfo Node::GetStreamInfo()
{
    Port *in{nullptr};


    //输入端口只有一个
    auto in_it = std::find_if(portList.begin(), portList.end(), [](Port* port){
        return port->portType==Port::InStream;
    });
    if (in_it != portList.end())
    {
        in=*in_it;
    }

    StreamPortinfo info(in,OutputStreamLogicExecution());
    return info;
}

QList<Port *> Node::OutputStreamLogicExecution()
{
    QList<Port*>outList;
    // 控制输出端口有多个，默认全部添加，如果需要规定那几个输出端口激活，则需要重载这个函数  IF，Then节点之类的
    std::copy_if(portList.begin(), portList.end(),std::back_inserter(outList),[](Port* port){
        return port->portType==Port::OutStream;
    });
    return outList;
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
        return port->portType==Port::Input||port->portType==Port::InStream;
    });
}

uint Node::GetOutCount()const
{
      //使用了count_if
    return std::count_if(portList.begin(), portList.end(), []( Port* port) {
        return port->portType==Port::Output||port->portType==Port::OutStream;
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

    }
    else
    {
        setFlag(QGraphicsItem::ItemIsMovable, true);

    }

     QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

     QGraphicsItem::mouseReleaseEvent(event);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseMoveEvent(event);
}


void Node::execute()
{

     IsExecuted=true;
}






