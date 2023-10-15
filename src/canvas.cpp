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
    for (int i=0;i<x_height;i++) {
        for (int j=0;j < x_width;j++) {
            x_vector[x_width*i+j] = new PixelBlock(curColor, graphicsview_mode, working_mode);
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

void Canvas::saveImage(QString name, double mult)
{
    /* not always the best way, should have a better method to save raw file */
    // save to history file
    QImage his_image(x_width, x_height, QImage::Format_RGB32);
    for (int i=0;i<x_height;i++) {
        for (int j=0;j < x_width;j++) {
            his_image.setPixel(j, i, x_vector[x_width*i+j]->color());
        }
    }
    his_image.save(QString(HISTORY_DIR) + "/" + name + ".jpg");

    // save to ouput file
    QImage out_image((int)(x_width * mult * PIXEL_SIZE), (int)(x_height * mult * PIXEL_SIZE), QImage::Format_RGB32);
    for (int i=0;i<x_height;i++) {
        for (int j=0;j < x_width;j++) {
            // render to entire color block
            for (int block_i=0+(int)(mult*PIXEL_SIZE)*i;block_i<(int)(mult*PIXEL_SIZE)*(i+1);block_i++) {
                for (int block_j=0+(int)(mult*PIXEL_SIZE)*j;block_j<(int)(mult*PIXEL_SIZE)*(j+1);block_j++) {
                    out_image.setPixel(block_j, block_i, x_vector[x_width*i+j]->color());
                }
            }
        }
    }
    out_image.save(QString(OUT_DIR) + "/" + name + ".jpg");
}

void Canvas::loadImage(QString path)
{

}
