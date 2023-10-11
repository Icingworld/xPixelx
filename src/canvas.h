#ifndef CANVAS_H
#define CANVAS_H

#include "../inc/global_def.h"
#include "pixelblock.h"

/* Canvas class */
class Canvas : public QWidget
{
public:
    Canvas(int, int, QWidget * parent = nullptr);
    virtual ~Canvas();

private:
    int x_width;
    int x_height;

public:
    QGridLayout * x_layout;
    QVector <PixelBlock *> x_vector;


};

#endif // CANVAS_H
