#ifndef IMAGEBLOCK_H
#define IMAGEBLOCK_H

#include "../inc/global_def.h"

class ImageBlock : public QLabel
{
private:
    int WIDTH;
    int HEIGHT;
    QString PATH;
public:
    ImageBlock(const QString &);
    ImageBlock(const int, const int, const QString &);
    virtual ~ImageBlock();

    void readImg();
};

#endif // IMAGEBLOCK_H
