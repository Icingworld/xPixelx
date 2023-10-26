#include "file.h"

xPixelxFile::xPixelxFile()
    : saved(false)
{

}

xPixelxFile::xPixelxFile(QString fpath)
    : path(fpath)
    , saved(false)
{

}

xPixelxFile::~xPixelxFile()
{

}

void xPixelxFile::readFile()
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString jsonString = in.readAll();
        // read json
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
        if (!jsonDocument.isNull()) {
            // get root
            rootObject = jsonDocument.object();
            img_width = rootObject["width"].toInt();
            img_height = rootObject["height"].toInt();
            int imgLength = rootObject["imgLength"].toInt();
            int favorateLength = rootObject["favorateLength"].toInt();

            // read img info
            for (int i=0;i<imgLength;i++) {
                QJsonObject colorObject = rootObject["PixelBlock"+QString::number(i)].toObject();
                temp_pixel_vector.push_back(QColor(
                    colorObject["red"].toInt(),
                    colorObject["green"].toInt(),
                    colorObject["blue"].toInt()
                ));
            }

            // read favorate color info
            for (int i=0;i<favorateLength;i++) {
                QJsonObject colorObject = rootObject["FavorateColor"+QString::number(i)].toObject();
                temp_favorate_vector.push_back(QColor(
                    colorObject["red"].toInt(),
                    colorObject["green"].toInt(),
                    colorObject["blue"].toInt()
                ));
            }
        } else {
            qDebug() << "invalid file!";
        }
        file.close();
    } else {
        qDebug() << "failed to open:" << file.errorString();
    }
}

void xPixelxFile::saveFile(int width, int height, QVector <PixelBlock *> img_vector, QVector <FavoratePixelBlock *> color_vector)
{
    qDebug() << "saving...";

    rootObject["width"] = width;
    rootObject["height"] = height;

    rootObject["imgLength"] = img_vector.length();
    rootObject["favorateLength"] = color_vector.length();

    // save img info
    for (int i=0;i<img_vector.length();i++) {
        QJsonObject colorObject;
        colorObject["red"] = qRed(img_vector[i]->color());
        colorObject["green"] = qGreen(img_vector[i]->color());
        colorObject["blue"] = qBlue(img_vector[i]->color());
        // add to parent node
        rootObject["PixelBlock"+QString::number(i)] = colorObject;
    }

    // save favorate color info
    for (int i=0;i<color_vector.length();i++) {
        QJsonObject colorObject;
        colorObject["red"] = qRed(color_vector[i]->color());
        colorObject["green"] = qGreen(color_vector[i]->color());
        colorObject["blue"] = qBlue(color_vector[i]->color());
        rootObject["FavorateColor"+QString::number(i)] = colorObject;
    }

    QJsonDocument jsonDoc(rootObject);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open json file.";
    }

    QTextStream out(&file);
    out << jsonDoc.toJson(QJsonDocument::Indented);

    file.close();
}

bool xPixelxFile::isEmpty()
{
    if (path == "")
    {
        return true;
    }
    return false;
}
