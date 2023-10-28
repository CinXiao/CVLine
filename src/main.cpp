#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QApplication>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<QFile>
#include<qstring.h>
#include<QLabel>
#include "Windows/nodeeditingwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    (new NodeEditingWindow())->show();


    /*
    cv::Mat mat;
    mat=cv::imread("C:/Users/Sun/Pictures/Image/Anno1800_Wallpaper_1920_1080_Success.jpg",cv::IMREAD_COLOR);
     cv::Mat out;
    cv::cvtColor(mat,out,cv::COLOR_BGR2GRAY);


    QLabel label;
    // 将 cv::Mat 转换为 QImage
    QImage img = QImage(out.data, out.cols, out.rows, out.step, QImage::Format_Grayscale8).rgbSwapped();

    // 将 QImage 显示在 QLabel 上
    label.setPixmap(QPixmap::fromImage(img));
    label.show();*/


    return a.exec();
}
