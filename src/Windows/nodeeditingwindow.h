#ifndef NODEEDITINGWINDOW_H
#define NODEEDITINGWINDOW_H
#include <QWidget>
#include<QGraphicsView>
#include<QGraphicsScene>

#include "src/Graphics/graphicsview.h"

//节点编辑窗口
namespace Ui {
class NodeEditingWindow;
}

class NodeEditingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NodeEditingWindow(QWidget *parent = nullptr);
    ~NodeEditingWindow();

private:
    Ui::NodeEditingWindow *ui;
    GraphicsView *view;
    QGraphicsScene scene;

};

#endif // NODEEDITINGWINDOW_H
