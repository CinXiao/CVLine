#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <src/Model/DebugModel/cvlinedebug.h>

#include <QTreeWidgetItem>

#include <src/Model/FileModel/projectfile.h>

#include "src/Graphics/Menu/treemenu.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建左侧工具区
    QDockWidget *leftDock = new QDockWidget("节点",this);
    leftDock->setWidget(new TreeMenu());


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


void MainWindow::on_actionopen_triggered()
{
    // 创建文件对话框
    QFileDialog fileDialog;

    // 设置文件对话框的属性
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setViewMode(QFileDialog::Detail);

    // 打开文件对话框并获取用户选择的文件
    if (fileDialog.exec()) {
        // 获取所选文件的URL
        QList<QUrl> selectedUrls = fileDialog.selectedUrls();

        if (!selectedUrls.isEmpty()) {
            // 获取第一个选定的文件的URL
            QUrl selectedUrl = selectedUrls.first();

            MainWindow *w=new MainWindow();
            GraphicsView * view=ProjectFile::OpenProject(QUrl(selectedUrl.toString()));
            if(w->view!=nullptr)
            {
                delete w->view;
                w->view=nullptr;
            }
            w->view=view;
            view->setParent(w);
            w->setCentralWidget(view);
            w->show();
        }
    }



}

