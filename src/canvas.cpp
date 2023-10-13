#include "canvas.h"

Canvas::Canvas(int width, int height, QColor & color, int & graphicsmode, int & workingmode, QWidget * parent)
    : QWidget(parent),
      x_width(width),
      x_height(height),
      curColor(color),
      graphicsview_mode(graphicsmode),
      working_mode(workingmode),
      x_vector(x_height * x_width)
{
    x_layout = new QGridLayout(this);
    for (int i=0;i < x_height;i++) {
        for (int j=0;j < x_width;j++) {
            x_vector[x_width*i+j] = new PixelBlock(color, graphicsview_mode, working_mode);
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
