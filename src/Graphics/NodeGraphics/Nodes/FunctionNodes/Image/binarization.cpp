#include "binarization.h"

Binarization::Binarization(QPointF pos):Node(Node::FunctionNode, pos)
{
    NodeName="二值化";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));
    AddPort(new Port(2,"阈值输入",Port::Input,Port::Int,120));
    AddPort(new Port(1,"二值化图像",Port::Output,Port::Image,QImage()));

    NodeHeight=250;

}

void Binarization::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);
    // 检查图片是否有效，然后绘制它
    if (!Image.isNull()) {
        // 定义图片位置和大小
        QRectF imageRect(3, 160, 80, 80);
        // 绘制图片
        painter->drawImage(imageRect, Image);
    }
}


void Binarization::execute()
{
    QVariant imgval = GetPortValue(1, Port::Input);
    Image = imgval.value<QImage>();
    QImage ezh = Image.copy();
    int threshold = GetPortValue(2, Port::Input).toUInt();  // 二值化阈值

    if (!ezh.isNull()) {
        cv::Mat cvImage = ImageConversionUtil::QImageToCvMat(ezh);

        // 将图像转换为灰度图像
        cv::cvtColor(cvImage, cvImage, cv::COLOR_BGR2GRAY);

        // 使用阈值二值化
        cv::Mat binaryImage;
        cv::threshold(cvImage, binaryImage, threshold, 255, cv::THRESH_BINARY);

        // 将OpenCV的Mat转换回QImage
        QImage outimg = ImageConversionUtil::CvMatToQImage(binaryImage);

        SetPortValue(1, outimg, Port::Output);
    }

    Node::execute();
}

