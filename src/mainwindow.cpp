#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , GraphicsViewMode(QGraphicsView::NoDrag)
    , WorkingMode(Draw)

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

    // add GraphicsView and 30 * 30 canvas
    canvas = new Canvas(400, 300, curColor, GraphicsViewMode, WorkingMode);
    scene = new QGraphicsScene(this);
    graphicsView = new MyGraphicsView(scene, this);
    scene->addWidget(canvas);
    graphicsView->setRenderHint(QPainter::Antialiasing, true);
    graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    ui->canvasLayout->addWidget(graphicsView);
    canvas->setCursor(Qt::CrossCursor);

    // TODO
    /*
     * 1. Hue点击跳转事件
     * 2. Canvas初始化自动缩放至合适大小
     * 3.
     */
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

void MainWindow::on_handtool_clicked()
{
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    GraphicsViewMode = QGraphicsView::ScrollHandDrag;

}

void MainWindow::on_pointer_clicked()
{
    graphicsView->setDragMode(QGraphicsView::NoDrag);
    GraphicsViewMode = QGraphicsView::NoDrag;
    WorkingMode = Draw;
    canvas->setCursor(Qt::CrossCursor);
}

void MainWindow::on_zoomin_clicked()
{
    graphicsView->scale(1.2, 1.2);
}

void MainWindow::on_zoomout_clicked()
{
    graphicsView->scale(0.8, 0.8);
}


void MainWindow::on_clear_clicked()
{
    canvas->setCursor(Qt::CrossCursor);
    if (WorkingMode == Clear)
    {
        WorkingMode = Draw;
    } else {
        WorkingMode = Clear;
    }
}


void MainWindow::on_save_clicked()
{
    canvas->saveImage("test");
}

