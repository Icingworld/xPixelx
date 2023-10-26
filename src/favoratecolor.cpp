#include "favoratecolor.h"

FavoratePixelBlock::FavoratePixelBlock(QColor color, int _index, bool _mode, QWidget * parent)
    : QLabel(parent)
    , curColor(color)
    , index(_index)
    , mode(_mode)
{
    setMinimumSize(FAVORATECOLOR_SIZE, FAVORATECOLOR_SIZE);
    setMaximumSize(FAVORATECOLOR_SIZE, FAVORATECOLOR_SIZE);
    setFrameShape(QFrame::Box);
    if (mode)
        setStyleSheet(QString("background-color:rgb(%1,%2,%3);border-width:1px;border-style:solid;border-color:rgb(255, 255, 255);").arg(color.red()).arg(color.green()).arg(color.blue()));
}

FavoratePixelBlock::~FavoratePixelBlock()
{

}

FavorateSelector::FavorateSelector(QWidget * parent)
    : QWidget(parent)
{
    x_layout = new QGridLayout(this);
    x_layout->setSpacing(0);
}

FavorateSelector::~FavorateSelector()
{

}

void FavorateSelector::modifyVector()
{
    int length = x_vector.length();
    int i_max = length / FAVORATECOLOR_MAX + 1;
    int j_max = length % FAVORATECOLOR_MAX;

    for (int i=0;i<i_max;i++) {
        for (int j=0;j<FAVORATECOLOR_MAX;j++) {
            if (j < j_max)
            {
                x_layout->addWidget(x_vector[FAVORATECOLOR_MAX*i+j], i, j);
            } else {
                FavoratePixelBlock * newColor = new FavoratePixelBlock(QColor(0,0,0), 0, false);
                x_layout->addWidget(newColor, i, j);
            }
        }
    }
}

void FavorateSelector::addColor(QColor color)
{
    for (int i=0;i<x_vector.length();i++) {
        if (color == x_vector[i]->curColor)
            return;
    }
    FavoratePixelBlock * newColor = new FavoratePixelBlock(color, x_vector.length(), true);
    x_vector.push_back(newColor);
    connect(newColor, &FavoratePixelBlock::colorSelected, this, [this](QColor color) {
        emit colorSelected(color);
    });
    modifyVector();
}

void FavorateSelector::load(QVector <QColor> saved_vector)
{
    x_vector.clear();
    for (int i=0;i<saved_vector.length();i++) {
        FavoratePixelBlock * newColor = new FavoratePixelBlock(saved_vector[i], i, true);
        x_vector.push_back(newColor);
        connect(newColor, &FavoratePixelBlock::colorSelected, this, [this](QColor color) {
            emit colorSelected(color);
        });
    }
    modifyVector();
}
