#include "pixelblock.h"

PixelBlock::PixelBlock(QColor & color, QWidget * parent)
    : QLabel(parent),
      curColor(color)
{
    setFrameShape(QFrame::Box);
    setStyleSheet("background-color:rgb(209,209,209);border-width:1px;border-style:solid;border-color:rgb(255, 255, 255);");
}

PixelBlock::~PixelBlock()
{

}
