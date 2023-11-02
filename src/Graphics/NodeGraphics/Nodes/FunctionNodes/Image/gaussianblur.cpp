#include "gaussianblur.h"


GaussianBlur::GaussianBlur(QPointF pos):Node(Node::FunctionNode, pos)
{

    NodeName="高斯模糊";
    //添加控制端口
    AddPort(new Port(0,"",Port::InStream,Port::Stream));
    AddPort(new Port(0,"",Port::OutStream,Port::Stream));

    //数据端口
    AddPort(new Port(1,"图像输入",Port::Input,Port::Image,QImage()));
    AddPort(new Port(2,"模糊半径",Port::Input,Port::Int,2));
    AddPort(new Port(1,"图像输出",Port::Output,Port::Image,QImage()));

    NodeHeight=250;

}

void GaussianBlur::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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


void GaussianBlur::execute()
{
    QVariant imgval = GetPortValue(1, Port::Input);
    Image = imgval.value<QImage>();

     int radius = GetPortValue(2, Port::Input).toUInt();
    if (!Image.isNull())
    {
        QImage outimg=Image.copy();
        int diameter = 2 * radius + 1;
        int size = diameter * diameter;
        // 创建高斯核
        QVector<float> kernel(size, 0.0);
        float sigma = radius / 3.0;
        float twoSigmaSquare = 2.0 * sigma * sigma;
        float constant = 1.0 / (qSqrt(2.0 * M_PI) * sigma);

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int index = (i + radius) * diameter + (j + radius);
                kernel[index] = constant * qExp(-(i * i + j * j) / twoSigmaSquare);
            }
        }
        // 归一化高斯核
        float sum = 0.0;
        for (int i = 0; i < size; i++) {
            sum += kernel[i];
        }
        for (int i = 0; i < size; i++) {
            kernel[i] /= sum;
        }

        // 创建用于填充边缘的颜色，这里使用黑色
        QColor edgeColor(0, 0, 0, 0);

        // 复制输入图像，用于边界填充
        QImage paddedImage = Image.copy();
        paddedImage = paddedImage.convertToFormat(Image.format());

        // 边界填充
        for (int x = 0; x < radius; x++) {
            for (int y = 0; y < Image.height(); y++) {
                paddedImage.setPixel(x, y, edgeColor.rgb());
                paddedImage.setPixel(Image.width() - x - 1, y, edgeColor.rgb());
            }
        }

        for (int y = 0; y < radius; y++) {
            for (int x = 0; x < Image.width(); x++) {
                paddedImage.setPixel(x, y, edgeColor.rgb());
                paddedImage.setPixel(x, Image.height() - y - 1, edgeColor.rgb());
            }
        }

        uint w,h;
        h=outimg.height() - radius;
        w=outimg.width() - radius;
        // 应用高斯滤镜
        for (int x = radius; x <w ; x++) {
            for (int y = radius; y < h; y++) {
                float red = 0.0, green = 0.0, blue = 0.0, alpha = 0.0;

                for (int i = -radius; i <= radius; i++) {
                    int index;
                    for (int j = -radius; j <= radius; j++) {
                        index = (i + radius) * diameter + (j + radius);
                        QRgb pixel = paddedImage.pixel(x + i, y + j);
                        red += qRed(pixel) * kernel[index];
                        green += qGreen(pixel) * kernel[index];
                        blue += qBlue(pixel) * kernel[index];
                        alpha += qAlpha(pixel) * kernel[index];
                    }
                }

                QRgb newPixel = qRgba(static_cast<int>(red), static_cast<int>(green), static_cast<int>(blue), static_cast<int>(alpha));
                outimg.setPixel(x, y, newPixel);
            }
        }

        SetPortValue(1, outimg, Port::Output);
    }
    Node::execute();
}

