#ifndef IMAGECONVERSIONUTIL_H
#define IMAGECONVERSIONUTIL_H
#include <QImage>
#include <opencv2/opencv.hpp>

class ImageConversionUtil
 {
public:
static cv::Mat QImageToCvMat(const QImage &image) {
    return cv::Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar *>(image.bits()), image.bytesPerLine()).clone();
}

static QImage CvMatToQImage(const cv::Mat &mat) {
    QImage::Format format;
    if (mat.type() == CV_8UC1) {
        format = QImage::Format_Grayscale8;
    } else if (mat.type() == CV_8UC3) {
        format = QImage::Format_RGB888;
    } else if (mat.type() == CV_8UC4) {
        format = QImage::Format_ARGB32;
    } else {
        format = QImage::Format_RGB888;
    }

    QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), format);
    return image.copy();
}
};

#endif // IMAGECONVERSIONUTIL_H
