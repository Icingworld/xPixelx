#ifndef CANVAS_H
#define CANVAS_H

#include "../inc/global_def.h"
#include "pixelblock.h"

/* Canvas class */
class Canvas : public QWidget
{
public:
    Canvas(int, int, QColor &, int &, int &, QWidget * parent = nullptr);
    virtual ~Canvas();

    void outputImage(QString, double = 1.0);
    QImage shotcutImage();
    void loadImage(QVector <QColor>);
    void reSize(int, int);

private:
    int x_width;
    int x_height;
    QColor & curColor;
    int & graphicsview_mode;
    int & working_mode;

public:
    QGridLayout * x_layout;
    QVector <PixelBlock *> x_vector;

};

#endif // CANVAS_H
