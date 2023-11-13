#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QApplication>
#include<QFile>
#include<qstring.h>
#include<QLabel>
#include <QLCDNumber>


#include <opencv2/opencv.hpp>

#include <src/Model/FileModel/projectfile.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    (new MainWindow())->show();



    return a.exec();
}
