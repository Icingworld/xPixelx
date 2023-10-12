#ifndef PIXELBLOCK_H
#define PIXELBLOCK_H

#include "../inc/global_def.h"

class PixelBlock : public QLabel
{
    Q_OBJECT

public:
    PixelBlock(QColor & color, QWidget * parent = nullptr);
    virtual ~PixelBlock();

private:
    QColor & curColor;
    void setBackground() {
        setFrameShape(QFrame::NoFrame);
        setStyleSheet(QString("background:rgb(%1,%2,%3);").arg(curColor.red()).arg(curColor.green()).arg(curColor.blue()));
    }

protected:
    void mousePressEvent(QMouseEvent * event) override {
        if (event->button() == Qt::LeftButton) {
            setBackground();
        }
        QWidget::mousePressEvent(event);
    }

};

#endif // PIXELBLOCK_H
