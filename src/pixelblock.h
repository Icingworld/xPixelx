#ifndef PIXELBLOCK_H
#define PIXELBLOCK_H

#include "../inc/global_def.h"

class PixelBlock : public QLabel
{
    Q_OBJECT

public:
    PixelBlock(QColor &, int &, int &, QWidget * parent = nullptr);
    virtual ~PixelBlock();

    QRgb color() { return curColor.rgb(); };

private:
    QColor & globalColor;
    QColor curColor;
    int & graphicsview_mode;
    int & working_mode;
    
    void draw() {
        setFrameShape(QFrame::NoFrame);
        setStyleSheet(QString("background:rgb(%1,%2,%3);").arg(globalColor.red()).arg(globalColor.green()).arg(globalColor.blue()));
        curColor = globalColor;
    }

    void clear() {
        setFrameShape(QFrame::Box);
        setStyleSheet("background-color:rgb(209,209,209);border-width:1px;border-style:solid;border-color:rgb(255, 255, 255);");
    }

protected:
    void mousePressEvent(QMouseEvent * event) override {
        if (event->button() == Qt::LeftButton) {
            if (graphicsview_mode == QGraphicsView::NoDrag)
            {
                if (working_mode == Draw)
                {
                    draw();
                } else if (working_mode == Clear) {
                    clear();
                }
            }
        }
        QWidget::mousePressEvent(event);
    }

};

#endif // PIXELBLOCK_H
