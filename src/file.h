#ifndef FILE_H
#define FILE_H

#include "../inc/global_def.h"
#include "pixelblock.h"
#include "favoratecolor.h"

class xPixelxFile
{
private:
    QString path;
    bool saved;
    // root node of json
    QJsonObject rootObject;
    int img_width, img_height;
    QVector <QColor> temp_pixel_vector;
    QVector <QColor> temp_favorate_vector;

public:
    xPixelxFile();
    xPixelxFile(QString);
    ~xPixelxFile();

    bool isSaved() { return saved; };
    void setFile(QString fpath) { path = fpath; };
    void readFile();
    void saveFile(int, int, QVector <PixelBlock *>, QVector <FavoratePixelBlock *>);
    void clear() { path="";saved=false; };
    bool isEmpty();
    int width() { return img_width; };
    int height() { return img_height; };
    QVector <QColor> getImageVector() const { return temp_pixel_vector; };
    QVector <QColor> getFavorateVector() const { return temp_favorate_vector; };
};

#endif
