#include "graphicsview.h"




GraphicsView::GraphicsView()
{
    // 设置框选模式
    setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing
                   | QPainter::LosslessImageRendering);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QGraphicsScene *scene=new QGraphicsScene();
    setScene(scene);
    //添加连线预览线到场景
    scene->addItem(&PreviewLine);
    scene->setBackgroundBrush(QColor(192, 192, 192));
    PreviewLine.setVisible(false);

    nodeManager.AddNode(new StartNode(QPoint(0,0)));
}


void GraphicsView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{

    MouseCurrentPos=event->pos();
    if (event->buttons()&Qt::RightButton)
    {
        moveviewflag=true;
        setDragMode(QGraphicsView::ScrollHandDrag);
        QPointF delta = mapToScene(event->pos()) - mapToScene(MouseClikePos);
        setSceneRect(sceneRect().translated(-delta));
        MouseClikePos=MouseCurrentPos;
    }

    //鼠标移动时更新选中的节点
    nodeManager.UpDateSelectedNode();
    if(isDrawing)
    {
        PreviewLine.setVisible(true);
        QPointF startPoint(mapToScene(MouseClikePos));
        QPointF endPoint(mapToScene(MouseCurrentPos));
        PreviewLine.UpdatePoint(startPoint,endPoint);
        PreviewLine.LineColor=lineColor;
    }

    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    MouseClikePos=event->pos();
    // 禁用右键框选功能
    if(event->button() == Qt::RightButton)
    {
        rightButtonPressed=true;
    }
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
    {
         rightButtonPressed=false;
       setDragMode(QGraphicsView::NoDrag);
    }


    //左键释放
    if (event->button() == Qt::LeftButton)
    {
       leftButtonPressed=false;
       //尝试获取释放位置的端口信息
       PortInfo releaseportinfo=nodeManager.GetPortByPos(MouseReleasePos);

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

            //输入输出端口匹配，但是数据类型不匹配,如果可以转换 创建转换节点
           if(portcheck&&!portdatatype&&nodeManager.PortIsConvertion(clickportinfo,releaseportinfo))
           {
               //单调性没过，先断开之前的连接
               if(!monotonicitycheck)
               {
                   if(clickportinfo.port->portType==Port::Input)
                   {
                       nodeManager.DeletePortConnect(clickportinfo);
                   }
                   if(releaseportinfo.port->portType==Port::Input)
                   {
                       nodeManager.DeletePortConnect(releaseportinfo);
                   }
               }
               //尝试连接两个类型不同的端口
               nodeManager.PortConvertConnect(clickportinfo,releaseportinfo);
           } //可以连接
           if(portcheck&&monotonicitycheck&&portdatatype)
           {
            //端点连接
            nodeManager.PortConnect(clickportinfo,releaseportinfo);
           }
           //单调性检测没通过，但是端口类型和端口数据类型是匹配的，则需要更改两个端口之间的连线
           else if(portcheck&&!monotonicitycheck&&portdatatype)
           {
             nodeManager.RePortConnect(clickportinfo,releaseportinfo);
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
       nodeManager.Run();
    }else if(event->key() == Qt::Key_Delete)
    {
       //删除选中的
       nodeManager.DeleteSelected();
    }
}

void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    //拖动了
    if(moveviewflag)
    {
       moveviewflag=false;
        return;
    }
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

