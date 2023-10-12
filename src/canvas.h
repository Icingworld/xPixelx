#ifndef CANVAS_H
#define CANVAS_H

#include "../inc/global_def.h"
#include "pixelblock.h"

/* Canvas class */
class Canvas : public QWidget
{
public:
    Canvas(int, int, QColor &, QWidget * parent = nullptr);
    virtual ~Canvas();

private:
    int x_width;
    int x_height;
    QColor & curColor;

public:
    QGridLayout * x_layout;
    QVector <PixelBlock *> x_vector;
    
public slots:
    void setSize(int);
};

#endif // CANVAS_H
