#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建左侧工具区
    QDockWidget *leftDock = new QDockWidget("节点",this);
    // 创建右侧工具区
    QDockWidget *rightDock = new QDockWidget("信息",this);

    // 创建下方的输出区
    outdock = new QDockWidget("输出",this);
    outdock->setWidget(new OutWidget());
    //中间编辑器选修卡
    CentralTab=new  QTabWidget();
    CentralTab->setTabsClosable(true);

    setCentralWidget(CentralTab);
    addDockWidget(Qt::BottomDockWidgetArea, outdock);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actioncreat_triggered(bool checked)
{
    CentralTab->addTab(new GraphicsView(),"蓝图");
}

