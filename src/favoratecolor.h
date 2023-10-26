#ifndef FAVORATECOLOR_H
#define FAVORATECOLOR_H

#include "../inc/global_def.h"

class FavoratePixelBlock : public QLabel
{
    Q_OBJECT

public:
    QColor curColor;
    int index;
    bool mode;

    QRgb color() { return curColor.rgb(); };

public:
    FavoratePixelBlock(QColor, int, bool, QWidget * parent = nullptr);
    virtual ~FavoratePixelBlock();

protected:
    void mousePressEvent(QMouseEvent * event) override
    {
        if (event->button() == Qt::LeftButton) {
            emit colorSelected(curColor);
        }
        QWidget::mousePressEvent(event);
    }

signals:
    void colorSelected(QColor);
};


class FavorateSelector : public QWidget
{
    Q_OBJECT

private:
    void modifyVector();

public:
    QGridLayout * x_layout;
    QVector <FavoratePixelBlock *> x_vector;

public:
    FavorateSelector(QWidget * parent = nullptr);
    virtual ~FavorateSelector();

    void delColor(int);
    void load(QVector <QColor>);


signals:
    void colorSelected(QColor);

public slots:
    void addColor(QColor);
};

#endif
