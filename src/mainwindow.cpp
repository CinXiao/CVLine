#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <src/Model/DebugModel/cvlinedebug.h>

#include <QTreeWidgetItem>

#include <src/Model/FileModel/projectfile.h>




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

     // 禁用关闭按钮
    leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    outdock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QTextEdit *debug=new QTextEdit();
    debug->setReadOnly(true);
    outdock->setWidget(debug);

    view=new GraphicsView();

    view->setParent(this);
    setCentralWidget(view);
    addDockWidget(Qt::BottomDockWidgetArea, outdock);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
    addDockWidget(Qt::RightDockWidgetArea, rightDock);


    //绑定输出
    connect(CVLineDebug::getInstance(),&CVLineDebug::Debug,this,[debug](QString str){
    debug->append(str);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actioncreat_triggered()
{
    (new MainWindow())->show();
}


void MainWindow::on_actionsave_triggered()
{

    ProjectFile::SaveProjct(view,QUrl(""));
}

