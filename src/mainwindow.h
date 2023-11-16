
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QToolBar>
#include <QDockWidget>
#include "src/Graphics/graphicsview.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    QUrl ProjectUrl;     //项目位置
    GraphicsView *view;  //中间编辑视图窗口
private slots:
    void on_actioncreat_triggered();

    void on_actionsave_triggered();

    void on_actionopen_triggered();



private:
    Ui::MainWindow *ui;
    QDockWidget *outdock;//下方输出窗口
    QDockWidget *rightDock;
    QDockWidget *leftDock ;

};
#endif // MAINWINDOW_H
