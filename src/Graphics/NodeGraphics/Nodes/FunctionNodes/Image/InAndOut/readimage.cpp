#include "readimage.h"

ReadImage::ReadImage(QPointF pos):Node(Node::FunctionNode, pos)
{

    NodeName="依次输出目录图像";
    //数据端口
    AddPort(new Port(0,"图像输出",Port::Output,Port::Image,QImage()));


}

void ReadImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Node::paint(painter,option,widget);

    painter->drawText(QRectF(3,60,200,40),"当前图片数量:"+QString::number(ImageList.count()));

}

void ReadImage::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString directoryPath =
        QFileDialog::getExistingDirectory(nullptr, "选择文件夹", QDir::homePath(), QFileDialog::ShowDirsOnly);
    if (!directoryPath.isEmpty()) {
    QDir dir(directoryPath);

    QStringList nameFilters;
    nameFilters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp"; // 可以根据你的需要添加其他图片格式

    dir.setNameFilters(nameFilters);
    QStringList imageFiles = dir.entryList(QDir::Files);

   ImageList.clear();

    foreach (const QString &fileName, imageFiles) {
        QString filePath = dir.filePath(fileName);
        QImage image(filePath);
        if (!image.isNull()) {
            ImageList.append(image);
        }
    }

    }

}

void ReadImage::execute()
{

    if(ImageList.count()!=0)
    {
    CurrentImage=*ImageList.begin();
    ImageList.pop_front();
    }


    QVariant val(CurrentImage);
    SetPortValue(0,val,Port::Output);
   Node::execute();
}
