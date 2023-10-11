#ifndef PIXELBLOCK_H
#define PIXELBLOCK_H

#include "../inc/global_def.h"

class PixelBlock : public QLabel
{
    Q_OBJECT

public:
    PixelBlock(QWidget * parent = nullptr);
    virtual ~PixelBlock();
};

#endif // PIXELBLOCK_H
