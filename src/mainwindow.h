#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colorselector.h"
#include "imageblock.h"
#include "pixelblock.h"
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void makeDirs(const QString &s);

private:
    Ui::MainWindow *ui;
    QColor curColor;
};
#endif // MAINWINDOW_H
