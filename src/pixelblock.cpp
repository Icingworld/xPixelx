#include "pixelblock.h"

PixelBlock::PixelBlock(QColor & color, int & graphicsmode, int & workingmode, QWidget * parent)
    : QLabel(parent),
      globalColor(color),
      curColor(209, 209, 209),
      graphicsview_mode(graphicsmode),
      working_mode(workingmode)
{
    // set fixed size
    setMinimumSize(PIXEL_SIZE, PIXEL_SIZE);
    setMaximumSize(PIXEL_SIZE, PIXEL_SIZE);
    setFrameShape(QFrame::Box);
    setStyleSheet("background-color:rgb(209,209,209);border-width:1px;border-style:solid;border-color:rgb(255, 255, 255);");
}

PixelBlock::~PixelBlock()
{

}
