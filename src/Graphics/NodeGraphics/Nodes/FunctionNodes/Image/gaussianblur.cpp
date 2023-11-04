#include "gaussianblur.h"


GaussianBlur::GaussianBlur(QPointF pos):Node(Node::FunctionNode, pos)
{

    NodeName="高斯模糊";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));
    AddPort(new Port(2,"内核大小",Port::Input,Port::Int,5));
    AddPort(new Port(3,"标准差",Port::Input,Port::Int,1));

    AddPort(new Port(1,"图像输出",Port::Output,Port::Image,QImage()));

    NodeHeight=300;

}

void GaussianBlur::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);
    // 检查图片是否有效，然后绘制它
    if (!Image.isNull()) {
        // 定义图片位置和大小
        QRectF imageRect(3, 200, 90, 90);
        // 绘制图片
        painter->drawImage(imageRect, Image);
    }
}


void GaussianBlur::execute()
{
    QVariant imgval = GetPortValue(1, Port::Input);
    Image = imgval.value<QImage>();

    if (!Image.isNull())
    {
        // 转换QImage为OpenCV的Mat
        cv::Mat cvImage = ImageConversionUtil::QImageToCvMat(Image);
        // 获取用户输入的内核大小和标准差
        int kernel_size = GetPortValue(2, Port::Input).toInt();
        double custom_sigma = GetPortValue(3, Port::Input).toDouble();

        // 检查内核大小和标准差是否在有效范围内
        if (kernel_size <= 0 || custom_sigma <= 0) {
            // 无效的参数值，可以显示错误消息或使用默认值
            kernel_size = 5;  // 默认内核大小
            custom_sigma = 1.0;  // 默认标准差
        }
        if(kernel_size%2==0)
        {
            kernel_size+=1;
        }

        // 使用高斯滤波
        cv::Mat blurredImage;
        cv::GaussianBlur(cvImage, blurredImage, cv::Size(kernel_size, kernel_size), custom_sigma, custom_sigma);

        // 将OpenCV的Mat转换回QImage
        QImage outimg = ImageConversionUtil::CvMatToQImage(blurredImage);

        SetPortValue(1, outimg, Port::Output);
    }
}


