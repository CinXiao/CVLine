#include "graphicsview.h"










GraphicsView::GraphicsView()
{

}

GraphicsView::GraphicsView(QGraphicsScene *scene): QGraphicsView(scene)
{

    setRenderHint(QPainter::Antialiasing); // 提高渲染质量
    setRenderHint(QPainter::SmoothPixmapTransform);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);

    setRenderHint(QPainter::Antialiasing);
    //添加连线预览线到场景
    scene->addItem(&PreviewLine);
    scene->setBackgroundBrush(QColor(192, 192, 192));
    PreviewLine.setVisible(false);


}


void GraphicsView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(1.2, event->angleDelta().y() / 240.0));


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



    //鼠标移动时更新
    nodeManager.UpdateLine(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    MouseClikePos=event->pos();
    MouseCurrentPos=event->pos();

    if(event->button() == Qt::LeftButton)
    {
       //尝试获取点击位置的端口信息
       PortInfo portinfo=nodeManager.GetPortByPos(MouseClikePos);
       if(!portinfo.IsEmpty())
       {
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
    MouseReleasePos=event->pos();
    PreviewLine.setVisible(false);
    //左键释放
    if (event->button() == Qt::LeftButton)
    {

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

           //可以连接
           if(portcheck&&monotonicitycheck&&portdatatype)
           {
            //端点连接
            nodeManager.PortConnect(clickportinfo,releaseportinfo);
           }

           //单调性检测没通过，但是端口类型和端口数据类型是匹配的，更改线
           if(portcheck&&!monotonicitycheck&&portdatatype)
           {
                qDebug()<<"需要更改连线了！";
                //取消之前两个端点之间的连接关系

                //端点连接
                nodeManager.PortConnect(clickportinfo,releaseportinfo);

           }





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
    if (event->key() == Qt::Key_F5) {

       qDebug()<<"f5 run";
       nodeManager.Run();
    }
}

void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
{

    // 使用exec函数显示菜单
    QAction *selectedAction = contextMenu.exec(event->globalPos());

    //获取选中的菜单创建出来的节点
    Node *node=contextMenu.GetSelectedNode(selectedAction,mapToScene(event->pos()));
    if(node!=nullptr)
    {
       nodeManager.AddNode(node);
    }


    event->accept();
}


void GraphicsView::scaleView(qreal scaleFactor)
{
    scale(scaleFactor, scaleFactor);
}

