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

    // add color selector
    ColorSelector * x_selector = new ColorSelector();
    ui->verticalLayout_5->addWidget(x_selector);
    connect(x_selector, &ColorSelector::colorChanged, this, [this](QColor color){
        curColor = color;
    });

    // add canvas
    canvas = new Canvas(30, 30, curColor);
    ui->canvasLayout->addWidget(canvas);
    // &Canvas::setSize(int) is a slot to resize all the pixel blocks
    // connect(this, &MainWindow::sizeChanged, canvas, &Canvas::setSize);
    // delete canvas;

    // need a toolbar on the right
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
