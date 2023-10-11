#include "imageblock.h"

ImageBlock::ImageBlock(const QString & path)
{
    PATH = path;
    readImg();
}

ImageBlock::ImageBlock(const int width, const int height, const QString & path)
{
    WIDTH = width;
    HEIGHT = height;
    PATH = path;
    readImg();
}

ImageBlock::~ImageBlock()
{

}

void ImageBlock::readImg()
{
    QPixmap pixmap(PATH);
    this->setPixmap(pixmap);
    this->setFixedSize(pixmap.size());
}
