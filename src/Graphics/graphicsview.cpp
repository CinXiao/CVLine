#include "graphicsview.h"


GraphicsView::GraphicsView()
{

}

GraphicsView::GraphicsView(QGraphicsScene *scene): QGraphicsView(scene)
{
    // 设置框选模式
    setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);

    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing
                         | QPainter::LosslessImageRendering);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //添加连线预览线到场景
    scene->addItem(&PreviewLine);
    scene->setBackgroundBrush(QColor(192, 192, 192));
    PreviewLine.setVisible(false);


}
void GraphicsView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{

    MouseCurrentPos=event->pos();

    if(isDrawing)
    {
        PreviewLine.setVisible(true);
        QPointF startPoint(mapToScene(MouseClikePos));
        QPointF endPoint(mapToScene(MouseCurrentPos));
        PreviewLine.UpdatePoint(startPoint,endPoint);
        PreviewLine.LineColor=lineColor;
    }
    //鼠标移动时更新选中的节点
    nodeManager.UpDateSelectedNode();
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    // 禁用框选功能
    if(event->button() == Qt::RightButton)
    {
        rightButtonPressed=true;
        setDragMode(QGraphicsView::NoDrag);
    }

    MouseClikePos=event->pos();
    if(event->button() == Qt::LeftButton)
    {
        leftButtonPressed=true;
        // 启用框选功能
         setDragMode(QGraphicsView::RubberBandDrag);
       //尝试获取点击位置的端口信息
       PortInfo portinfo=nodeManager.GetPortByPos(MouseClikePos);
       if(!portinfo.IsEmpty())
       {
           setDragMode(QGraphicsView::NoDrag);
           //设置画线标识
           isDrawing=true;
           //设置画线颜色
           lineColor=portinfo.port->portColor;
       }
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    //不显示画线预览线
    PreviewLine.setVisible(false);
    MouseReleasePos=event->pos();

    if (event->button() == Qt::RightButton)
        rightButtonPressed=false;

    //左键释放
    if (event->button() == Qt::LeftButton)
    {
       leftButtonPressed=false;
       //尝试获取释放位置的端口信息
       PortInfo releaseportinfo=nodeManager.GetPortByPos(MouseReleasePos);

       //可以连接两个端口了
       if(!releaseportinfo.IsEmpty()&&isDrawing)
       {
           //因为isDrawing是true的话 点击位置的端口信息肯定是获取可以获取到的所以不用校验点击位置是否有节点
           //获取点击位置的端口信息
           PortInfo clickportinfo=nodeManager.GetPortByPos(MouseClikePos);


           //端口类型是否可以连接
           bool portcheck=nodeManager.PortTypeCheck(clickportinfo,releaseportinfo);
           //端口单调性检测
           bool monotonicitycheck=nodeManager.PortMonotonicityCheck(clickportinfo,releaseportinfo);
           //端口数据类型是否匹配
           bool portdatatype=nodeManager.PortDataTypeCheck(clickportinfo,releaseportinfo);

           //可以连接
           if(portcheck&&monotonicitycheck&&portdatatype)
           {
            //端点连接
            nodeManager.PortConnect(clickportinfo,releaseportinfo);
           }

           //单调性检测没通过，但是端口类型和端口数据类型是匹配的，则需要更改两个端口之间的连线
           if(portcheck&&!monotonicitycheck&&portdatatype)
           {
                //删除输入端口的连线，因为输入端口只能连一条线，所以只要删除与输入端口连接的那一条连接信息就行了
                //判断两个端口谁是输入端口
                if(clickportinfo.port->portType==Port::Input)
                {
                    nodeManager.DeletePortConnect(clickportinfo);
                }
                if(releaseportinfo.port->portType==Port::Input)
                {
                    nodeManager.DeletePortConnect(releaseportinfo);
                }

                //如果是控制流，端口之间的连线都删
                if(clickportinfo.port->portType==Port::InStream||releaseportinfo.port->portType==Port::InStream)
                {
                    nodeManager.DeletePortConnect(clickportinfo);
                    nodeManager.DeletePortConnect(releaseportinfo);
                }
                //连个端点重新连接
                nodeManager.PortConnect(clickportinfo,releaseportinfo);
           }
           //两个点击节点可以移动，因为最开始点击端口时，为了画线设置了节点不允许移动，所以这个地方要重新设置
           clickportinfo.node->setFlag(QGraphicsItem::ItemIsMovable, true);
       }
    }
    //重置画线标识
    isDrawing=false;
    QGraphicsView::mouseReleaseEvent(event);
}

bool GraphicsView::viewportEvent(QEvent *event)
{
    return QGraphicsView::viewportEvent(event);
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F5)
    {
       qDebug()<<"f5 run";
       nodeManager.Run();
    }
}

void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    //右键点击然后拖动了，就不弹出菜单了
    if(MouseClikePos!=MouseReleasePos)
       return;

    // 使用exec函数显示菜单
    QAction *selectedAction = contextMenu.exec(event->globalPos());
    //获取选中的菜单创建出来的节点
    Node *node=contextMenu.GetSelectedNode(selectedAction,mapToScene(event->pos()));
    if(node!=nullptr)
    {
       nodeManager.AddNode(node);
       node->setSelected(true);
    }
    event->accept();
}


void GraphicsView::scaleView(qreal scaleFactor)
{
    scale(scaleFactor, scaleFactor);
}

