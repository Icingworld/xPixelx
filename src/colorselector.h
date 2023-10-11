#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include "../inc/global_def.h"

// color canvas
class ColorCanvas : public QWidget
{
    Q_OBJECT

public:
    ColorCanvas(QWidget * parent = nullptr);
    virtual ~ColorCanvas();

private:
    QVBoxLayout * x_Layout;
    QLabel * x_Label;
    int x_hue;
    QPoint x_pos;

protected:
    void mousePressEvent(QMouseEvent * event) override;
    void paintEvent(QPaintEvent *) override;

public slots:
    void setColor(int);
    void setCyclePos(QColor);

signals:
    void sendColorChangedSignal(QColor);
};


// Hue value selector
class ColorHue : public QWidget
{
    Q_OBJECT

public:
    ColorHue(QWidget * parent = nullptr);
    virtual ~ColorHue();

    // color value
    int value();

private:
    QSlider * x_slider;
    QVBoxLayout * x_layout;

signals:
    // change canvas color
    void x_HueChanged(int);

public slots:
    void setHue(int);
};

class MyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    MyLineEdit(QWidget * parent = nullptr) : QLineEdit(parent) {}

signals:
    void sendEnterSignal();

protected:
    void keyPressEvent(QKeyEvent * event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            // handle enter event
            emit sendEnterSignal();
            event->accept();
        } else {
            QLineEdit::keyPressEvent(event);
        }
    }
};

// color in hex
class ColorHex : public QWidget
{
    Q_OBJECT

public:
    ColorHex(QWidget * parent = nullptr);
    ~ColorHex();

private:
    QLabel * x_text_hex;
    MyLineEdit * x_hex;
    QLabel * x_text_r;
    QLineEdit * x_red;
    QLabel * x_text_g;
    QLineEdit * x_green;
    QLabel * x_text_b;
    QLineEdit * x_blue;
    QHBoxLayout * x_layout;
    QIntValidator * x_validator;
    bool lock;

    void changeColor();
    QString demical2hex(QString);
    QString hex2demical(QString);

signals:
    void sendHueSignal(int);
    void sendColorSignal(QColor);
    void colorChanged(QColor);

private slots:
    void setRgb2Hex();

public slots:
    void setHex(QColor);
};


// Selector
class ColorSelector : public QWidget
{
    Q_OBJECT

public:
    ColorSelector(QWidget * parent = nullptr);
    virtual ~ColorSelector();

private:
    ColorCanvas * x_canvas;
    ColorHue * x_hue;
    ColorHex * x_hex;
    QPushButton * x_button;
    QGridLayout * x_layout;

    QColor curColor;

signals:
    void colorChanged(QColor);
    void clicked();
};

#endif // COLORSELECTOR_H
