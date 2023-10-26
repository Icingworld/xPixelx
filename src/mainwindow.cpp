#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int _mode, int _width, int _height, QString _path, QString _title, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mode(_mode)
    , curWidth(_width)
    , curHeight(_height)
    , path(_path)
    , GraphicsViewMode(QGraphicsView::NoDrag)
    , WorkingMode(Draw)

{
    ui->setupUi(this);
    // set title
    setWindowIcon(QIcon("://assets/icon/logo.png"));
    setWindowTitle("xPixelx - " + _title);

    // check custom directories
    makeDirs(OUT_DIR);
    makeDirs(LOG_DIR);
    makeDirs(HISTORY_DIR);
    makeDirs(TEST_DIR);

    // init File system
    file = new xPixelxFile(path);

    // add color selector
    ColorSelector * colorSelector = new ColorSelector();
    ui->verticalLayout_5->addWidget(colorSelector);
    connect(colorSelector, &ColorSelector::colorChanged, this, [this](QColor color){
        curColor = color;
    });

    // add FavorateColor Widget
    favoratecolor = new FavorateSelector(this);
    ui->verticalLayout_11->addWidget(favoratecolor);

    connect(colorSelector, &ColorSelector::clicked, favoratecolor, &FavorateSelector::addColor);
    connect(favoratecolor, &FavorateSelector::colorSelected, this, [this](QColor color) {
        curColor = color;
        // set color of colorSelector or not
    });

    // add GraphicsView and canvas
    canvas = new Canvas(curWidth, curHeight, curColor, GraphicsViewMode, WorkingMode);
    scene = new QGraphicsScene(this);
    graphicsView = new MyGraphicsView(scene, this);
    scene->addWidget(canvas);
    graphicsView->setRenderHint(QPainter::Antialiasing, true);
    graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    ui->canvasLayout->addWidget(graphicsView);
    canvas->setCursor(Qt::CrossCursor);

    // set MenuBar
    QMenu * menu1 = new QMenu("file", this);
    QMenu * menu2 = new QMenu("about", this);
    QMenu * menu3 = new QMenu("help", this);

    ui->menubar->addSeparator();
    ui->menubar->addMenu(menu1);
    ui->menubar->addMenu(menu2);
    ui->menubar->addMenu(menu3);

    QAction * saveAct = new QAction("save", this);
    menu1->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, [this] {
        file->saveFile(curWidth, curHeight, canvas->x_vector, favoratecolor->x_vector);
    });

    // load history project
    if (mode == HistoryProject)
    {
        file->readFile();
        canvas->loadImage(file->getImageVector());
        curColor = colorSelector->color();
        favoratecolor->load(file->getFavorateVector());
    }
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
    // if (WorkingMode == Clear)
    // {
    //     WorkingMode = Draw;
    // } else {
    //     WorkingMode = Clear;
    // }
    WorkingMode = Clear;
}

void MainWindow::on_save_clicked()
{
    double mult = 1.0;
    QString name;
    output * out = new output(curWidth, curHeight, mult, name, this);
    int result = out->exec();
    if (result == QDialog::Accepted)
        canvas->outputImage(name , mult);
    delete out;
}
