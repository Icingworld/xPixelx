#include "canvas.h"

Canvas::Canvas(int width, int height, QColor & color, QWidget * parent)
    : QWidget(parent),
      x_width(width),
      x_height(height),
      curColor(color),
      x_vector(x_height * x_width)
{
    x_layout = new QGridLayout(this);
    for (int i=0;i < x_height;i++) {
        for (int j=0;j < x_width;j++) {
            // qDebug() << x_width*i+j;
            x_vector[x_width*i+j] = new PixelBlock(color);
            x_layout->addWidget(x_vector[x_width*i+j], i, j);
        }
    }
    x_layout->setSpacing(0);
    setLayout(x_layout);
}

Canvas::~Canvas()
{
    delete x_layout;
}

void Canvas::setSize(int length)
{
    qDebug() << "get length: " << length;
    for (int i=0;i < x_height;i++) {
        for (int j=0;j < x_width;j++) {
            x_vector[x_width*i+j]->resize(length, length);
        }
    }
    update();
}
