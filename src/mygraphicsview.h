#ifndef MYGRAPHICVSIEW_H
#define MYGRAPHICVSIEW_H

#include "../inc/global_def.h"

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QGraphicsScene * scene, QWidget *parent = nullptr) : QGraphicsView(scene, parent) {}

protected:
    void wheelEvent(QWheelEvent *event) override
    {
        int wheelValue = event->angleDelta().y();
        double ratio = (double)wheelValue / (double)1200 + 1;
        scale(ratio, ratio);
    }
};


#endif