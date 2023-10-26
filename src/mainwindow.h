#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colorselector.h"
#include "pixelblock.h"
#include "canvas.h"
#include "mygraphicsview.h"
#include "favoratecolor.h"
#include "file.h"
#include "output.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int, int, int, QString, QString, QWidget *parent = nullptr);
    ~MainWindow();

    void makeDirs(const QString &s);

private slots:
    void on_handtool_clicked();
    void on_pointer_clicked();
    void on_zoomin_clicked();
    void on_zoomout_clicked();
    void on_clear_clicked();
    void on_save_clicked();

private:
    Ui::MainWindow *ui;
    int mode;
    int curWidth, curHeight;
    QString path;
    int GraphicsViewMode;
    int WorkingMode;

    QColor curColor;
    MyGraphicsView *graphicsView;
    QGraphicsScene *scene;
    Canvas * canvas;
    FavorateSelector * favoratecolor;
    xPixelxFile * file;

};
#endif // MAINWINDOW_H
