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
    QColor currentColor() { return curColor; };
    void setCurColor(QColor color) { curColor = color; };

    void load() {
        curColor = globalColor;
        if (curColor == QColor(209, 209, 209))
        {
            clear();
        } else {
            draw();
        }
    }

    void draw() {
        curColor = globalColor;
        setFrameShape(QFrame::NoFrame);
        setStyleSheet(QString("background:rgb(%1,%2,%3);").arg(curColor.red()).arg(curColor.green()).arg(curColor.blue()));
    }

    void clear() {
        curColor = QColor(209, 209, 209);
        setFrameShape(QFrame::Box);
        setStyleSheet("background-color:rgb(209,209,209);border-width:1px;border-style:solid;border-color:rgb(255, 255, 255);");
    }

private:
    QColor & globalColor;
    QColor curColor;
    int & graphicsview_mode;
    int & working_mode;

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
