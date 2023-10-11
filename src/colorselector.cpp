#include "colorselector.h"

ColorCanvas::ColorCanvas(QWidget * parent)
    : QWidget(parent),
      x_hue(0),
      x_pos(QPoint(-1, -1))
{
    x_Label = new QLabel();
    x_Layout = new QVBoxLayout(this);
    x_Layout->addWidget(x_Label);
    x_Layout->setSpacing(0);
    x_Layout->setMargin(0);
}

ColorCanvas::~ColorCanvas()
{

}

void ColorCanvas::setColor(int hue)
{
    x_hue = hue;
    QColor tempColor = QColor::fromHsv(x_hue, (int)(255.0 * (double)x_pos.x() / (double)width()), (int)(255.0 * (double)x_pos.y() / (double)height()));
    emit sendColorChangedSignal(tempColor);
    update();
}

void ColorCanvas::setCyclePos(QColor color)
{
    int s = color.hsvSaturation();
    int v = color.value();
    x_pos = QPoint((int)(width() * (double)s / 255.0), (int)(height() * (double)v / 255.0));
    update();
}

void ColorCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(0, 0, width(), height());

    QLinearGradient linearGradientH(rect.topLeft(), rect.topRight());
    linearGradientH.setColorAt(0, Qt::white);
    QColor color;
    color.setHsv(x_hue, 255, 255);
    linearGradientH.setColorAt(1, color);
    painter.fillRect(rect, linearGradientH);

    QLinearGradient linearGradientV(rect.topLeft(), rect.bottomLeft());
    linearGradientV.setColorAt(1, QColor(0, 0, 0, 0));
    linearGradientV.setColorAt(0, QColor(0, 0, 0, 255));
    painter.fillRect(rect, linearGradientV);

    painter.setPen(QColor(Qt::white));
    painter.drawEllipse(x_pos, 5, 5);
}

void ColorCanvas::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        x_pos = QPoint(event->x(), event->y());
        update();
        // qDebug() << "Left button clicked at (" << event->x() << ", " << event->y() << ")";
        QColor tempColor = QColor::fromHsv(x_hue, (int)(255.0 * (double)event->x() / (double)width()), (int)(255.0 * (double)event->y() / (double)height()));
        emit sendColorChangedSignal(tempColor);
    }

    QWidget::mousePressEvent(event);
}

// ---------------------------------------------------------------------------

ColorHue::ColorHue(QWidget * parent)
    : QWidget(parent)
{
    x_slider = new QSlider();
    x_slider->setRange(0, 359);
    x_slider->setValue(359);
    x_slider->setStyleSheet("QSlider::groove:vertical {width: 15px; \
                            background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, \
                                stop:0 hsv(359,255,255), \
                                stop:0.17 hsv(299,255,255), \
                                stop:0.33 hsv(239,255,255), \
                                stop:0.5 hsv(179,255,255), \
                                stop:0.67 hsv(119,255,255), \
                                stop:0.83 hsv(59,255,255), \
                                stop:1 hsv(0,255,255));} \
                            QSlider::handle:vertical { \
                                background: white; \
                                height: 5px; \
                                margin:0px -2px; \
                                border: 1px solid grey; \
                                border-radius: 2px;} \
                            QSlider::add-page:vertical {background: transparent;} \
                            QSlider::sub-page:vertical {background: transparent;}");
    x_layout = new QVBoxLayout(this);
    x_layout->addWidget(x_slider);
    x_layout->setSpacing(0);
    x_layout->setContentsMargins(12, 0, 12, 0);

    connect(x_slider, &QSlider::valueChanged, this, [this]{
        emit x_HueChanged(x_slider->value());
    });
}

ColorHue::~ColorHue()
{
    delete x_layout;
    delete x_slider;
}

int ColorHue::value()
{
    return x_slider->value();
}

void ColorHue::setHue(int hue)
{
    x_slider->setValue(hue);
}

// ----------------------------------------------------------------------------

ColorHex::ColorHex(QWidget * parent)
    : QWidget(parent),
      lock(false)
{
    x_text_hex = new QLabel("Color:#");
    x_hex = new MyLineEdit(this);
    x_hex->setText("ffffff");

    x_validator = new QIntValidator(0, 255, this);

    x_text_r = new QLabel("Red:");
    x_red = new QLineEdit("255");
    x_red->setValidator(x_validator);
    x_text_g = new QLabel("Green:");
    x_green = new QLineEdit("255");
    x_green->setValidator(x_validator);
    x_text_b = new QLabel("Blue:");
    x_blue = new QLineEdit("255");
    x_blue->setValidator(x_validator);
    x_layout = new QHBoxLayout(this);

    x_layout->addWidget(x_text_hex);
    x_layout->addWidget(x_hex);
    x_layout->addWidget(x_text_r);
    x_layout->addWidget(x_red);
    x_layout->addWidget(x_text_g);
    x_layout->addWidget(x_green);
    x_layout->addWidget(x_text_b);
    x_layout->addWidget(x_blue);
    x_layout->setSpacing(7);
    x_layout->setMargin(0);

    connect(x_red, &QLineEdit::textChanged, this, &ColorHex::setRgb2Hex);
    connect(x_green, &QLineEdit::textChanged, this, &ColorHex::setRgb2Hex);
    connect(x_blue, &QLineEdit::textChanged, this, &ColorHex::setRgb2Hex);

    connect(x_hex, &MyLineEdit::sendEnterSignal, this, [this]{
        lock = true;
        // hex to rgb
        QString tempHex = x_hex->text();
        x_red->setText(hex2demical(tempHex.mid(0, 2)));
        x_green->setText(hex2demical(tempHex.mid(2, 2)));
        x_blue->setText(hex2demical(tempHex.mid(4, 2)));
        lock = false;
        // send signal

        changeColor();
    });
}

ColorHex::~ColorHex()
{
    delete x_layout;
    delete x_text_hex;
    delete x_hex;
    delete x_text_r;
    delete x_text_g;
    delete x_text_b;
    delete x_red;
    delete x_green;
    delete x_blue;
    delete x_validator;
}

void ColorHex::changeColor()
{
    QColor tempColor(x_red->text().toInt(), x_green->text().toInt(), x_blue->text().toInt());
    tempColor.toHsv();
    emit sendColorSignal(tempColor);
    emit sendHueSignal(tempColor.hsvHue());
    emit colorChanged(tempColor);
}

void ColorHex::setRgb2Hex()
{
    if (!lock)
    {
        x_hex->setText(demical2hex(x_red->text()) + demical2hex(x_green->text()) + demical2hex(x_blue->text()));
        changeColor();
    }
}

void ColorHex::setHex(QColor color)
{
    lock = true;
    x_red->setText(QString::number(color.red()));
    x_green->setText(QString::number(color.green()));
    x_blue->setText(QString::number(color.blue()));
    x_hex->setText(demical2hex(x_red->text()) + demical2hex(x_green->text()) + demical2hex(x_blue->text()));
    lock = false;
    emit colorChanged(QColor(x_red->text().toInt(), x_green->text().toInt(), x_blue->text().toInt()));
}

QString ColorHex::demical2hex(QString str)
{
    int decimal = str.toInt();
    QString hexString = QString("%1").arg(decimal, 2, 16, QChar('0'));
    return hexString;
}

QString ColorHex::hex2demical(QString str)
{
    bool ok;
    int decimalValue = str.toInt(&ok, 16);
    if (ok)
    {
        return QString::number(decimalValue);
    } else {
        return "Error";
    }
}

// ----------------------------------------------------------------------------

ColorSelector::ColorSelector(QWidget * parent)
    : QWidget(parent)
{
    x_canvas = new ColorCanvas();
    x_hue = new ColorHue();
    x_hex = new ColorHex();
    x_button = new QPushButton("save");
    x_button->setMinimumWidth(10);

    // set layout
    x_layout = new QGridLayout(this);
    x_layout->addWidget(x_canvas, 0, 0);
    x_layout->addWidget(x_hue, 0, 1);
    x_layout->addWidget(x_hex, 1, 0);
    x_layout->addWidget(x_button, 1, 1);
    x_layout->setColumnStretch(0, 99);
    x_layout->setColumnStretch(1, 1);

    // hue to canvas
    connect(x_hue, &ColorHue::x_HueChanged, x_canvas, &ColorCanvas::setColor);
    // canvas to hex
    connect(x_canvas, &ColorCanvas::sendColorChangedSignal, x_hex, &ColorHex::setHex);
    // hex to hue
    connect(x_hex, &ColorHex::sendHueSignal, x_hue, &ColorHue::setHue);
    // hex to canvas
    connect(x_hex, &ColorHex::sendColorSignal, x_canvas, &ColorCanvas::setCyclePos);
    // hex to selector
    connect(x_hex, &ColorHex::colorChanged, this, [this](QColor color) {
        emit colorChanged(color);
    });
    // button clicked
    connect(x_button, &QPushButton::clicked, this, [this]{
        emit clicked();
    });
}

ColorSelector::~ColorSelector()
{
    delete x_layout;
    delete x_canvas;
    delete x_hue;
    delete x_hex;
    delete x_button;
}
