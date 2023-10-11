#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // check custom directories
    makeDirs(OUT_DIR);
    makeDirs(LOG_DIR);
    makeDirs(HISTORY_DIR);
    makeDirs(TEST_DIR);

    // add test image block
    ImageBlock * testImg = new ImageBlock("test/test.png");
    ui->testLayout->insertWidget(0, testImg);

    // add test pixel block
    PixelBlock * testPixel = new PixelBlock();
    // qDebug() << qRed(testPixel->color()) << qGreen(testPixel->color()) << qBlue(testPixel->color());
    ui->testLayout->insertWidget(0, testPixel);

    // add color selector
    ColorSelector * x_selector = new ColorSelector();
    ui->verticalLayout_5->addWidget(x_selector);

    // add canvas
    Canvas * canvas = new Canvas(40, 30);
    delete canvas;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeDirs(const QString & dirPath)
{
    QDir dir(dirPath);
    if (dir.exists()) {
        qDebug() << "Dir: " << dirPath << " already exists.";
    } else {
        if (dir.mkdir(".")) {
            qDebug() << "Dir: " << dirPath << " created successfully.";
        } else {
            qDebug() << "Dir: " << dirPath << " created failed.";
        }
    }
}
