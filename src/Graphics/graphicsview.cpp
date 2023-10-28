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

    DataNode *data1,*data2,*data3;
    data1= new DataNode(QPointF(100,100));
    data2= new DataNode(QPointF(170,200));
    data3= new DataNode(QPointF(10,150));

    //data2->SetPortDataType(0,Port::Output,Port::Float);
    nodeManager.AddNode(data1);
    nodeManager.AddNode(data2);
    nodeManager.AddNode(data3);


    nodeManager.AddNode(new StartNode(QPointF(130,200)));
   nodeManager.AddNode(new AddIntNode(QPointF(150,250)));
   nodeManager.AddNode(new AddIntNode(QPointF(300,450)));
   nodeManager.AddNode(new AddIntNode(QPointF(-150,250)));

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
       //因为isDrawing是true的话 点击位置的端口信息肯定是获取可以获取到的所以不用再次获取点击位置的端口信息
       PortInfo releaseportinfo=nodeManager.GetPortByPos(MouseReleasePos);

       if(!releaseportinfo.IsEmpty()&&isDrawing)
       {

           //获取点击位置的端口信息
           PortInfo clickportinfo=nodeManager.GetPortByPos(MouseClikePos);
           //连线端口类型判断,输入输出端口类型检测
           bool check= nodeManager.EnableConnectCheck(clickportinfo,releaseportinfo);

           //可以连接
           if(check)
           {
           //获取开始点和结束点，即鼠标点击的位置和释放的位置
            QPointF startPoint(mapToScene(MouseClikePos));
            QPointF endPoint(mapToScene(MouseReleasePos));

            //线
            BezierCurveItem* curveItem = new BezierCurveItem(startPoint, endPoint);
            curveItem->LineColor=lineColor;

            //端口和连线信息
            LineInfo portline;
            portline.line=curveItem;
            portline.PortInfo1=clickportinfo;
            portline.PortInfo2=releaseportinfo;

            //节点连接
            nodeManager.NodeConnect(clickportinfo.node,releaseportinfo.node);


            //添加线
            scene()->addItem(curveItem);

            //添加一条节点和线的连接关系
            nodeManager.AddRelation(portline);
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


void GraphicsView::scaleView(qreal scaleFactor)
{
    scale(scaleFactor, scaleFactor);
}

