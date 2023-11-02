#include "nodeeditingwindow.h"
#include "ui_nodeeditingwindow.h"

#include <QGraphicsRectItem>

#include "src/Graphics/NodeGraphics/node.h"

#include "src/Graphics/LineGraphics/beziercurveitem.h"

NodeEditingWindow::NodeEditingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeEditingWindow)
{
    ui->setupUi(this);

    scene.setSceneRect(250,250,500,500);
    view=new GraphicsView(&scene);
    ui->verticalLayout->addWidget(view);


}

NodeEditingWindow::~NodeEditingWindow()
{
    delete ui;
}
