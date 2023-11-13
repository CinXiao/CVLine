
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

private slots:
    void on_actioncreat_triggered();

    void on_actionsave_triggered();

private:
    Ui::MainWindow *ui;
    QDockWidget *outdock;//下方输出窗口
    QDockWidget *rightDock;
    QDockWidget *leftDock ;
    GraphicsView *view;//中间编辑视图窗口

};
#endif // MAINWINDOW_H
