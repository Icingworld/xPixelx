#include "pixelblock.h"

PixelBlock::PixelBlock(QColor & color, int & graphicsmode, int & workingmode, QWidget * parent)
    : QLabel(parent),
      curColor(color),
      graphicsview_mode(graphicsmode),
      working_mode(workingmode)
{
    // set fixed size
    setMinimumSize(40, 40);
    setMaximumSize(40, 40);
    setFrameShape(QFrame::Box);
    setStyleSheet("background-color:rgb(209,209,209);border-width:1px;border-style:solid;border-color:rgb(255, 255, 255);");
}

PixelBlock::~PixelBlock()
{

}
