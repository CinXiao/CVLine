#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QMenu>
#include<QtTypes>
#include<QPainter>
#include <QAction>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QGraphicsView>




#include "src/NodeGraphics/node.h"
#include "src/Graphics/Menu/contextmenu.h"
#include "src/ConnectionModel/NodeManager.h"
#include "src/LineGraphics/beziercurveitem.h"
#include "src/NodeGraphics/Nodes/startnode.h"
#include "src/NodeGraphics/Nodes/DataNode/DataNode.h"
#include "src/NodeGraphics/Nodes/FunctionNodes/Calculate/Add.h"

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView();
    GraphicsView(QGraphicsScene* scene);

    void scaleView(qreal scaleFactor);

    void wheelEvent(QWheelEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void mousePressEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    bool viewportEvent(QEvent *event)override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void contextMenuEvent(QContextMenuEvent *event)override;

private:
    NodeManager nodeManager{this};//节点管理器

    ContextMenu contextMenu{this};
    //画线判断标识
    bool isDrawing=false;
    //鼠标右键按下标识
    bool rightButtonPressed =false;
    //鼠标左键按下标识
    bool leftButtonPressed =false;



    //画线预览
    BezierCurveItem PreviewLine{QPointF(0,0),QPointF(0,0)};
    //预览线的颜色
    QColor lineColor;
    //鼠标当前位置
    QPoint MouseCurrentPos;
    //鼠标点击位置
    QPoint MouseClikePos;
    //鼠标释放位置
    QPoint MouseReleasePos;



};





#endif // GRAPHICSVIEW_H
