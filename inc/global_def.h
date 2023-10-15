#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H

#include <QPixmap>
#include <QDir>
#include <QString>
#include <QVector>
#include <QColor>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QCursor>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QIntValidator>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QImage>

/* custom directory */
#define     OUT_DIR         "out"
#define     LOG_DIR         "log"
#define     HISTORY_DIR     "history"
#define     TEST_DIR        "test"

/* customs param */
#define     IMG_WIDHT       120
#define     IMG_HEIGHT      90
#define     PIXEL_SIZE      40

/* custom struct */
enum _WorkingMode_ {
    Draw,
    Clear
};

#endif // GLOBAL_H
