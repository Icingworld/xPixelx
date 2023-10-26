#include "launch.h"
#include "ui_launch.h"

launch::launch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::launch),
    mode(NewProject),
    path("")
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://assets/icon/logo.png"));
    setWindowTitle("启动");
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->stackedWidget->setCurrentIndex(1);

    QString fileExtension = "xPixelx";
    QDir directory(HISTORY_DIR);
    QStringList files = directory.entryList(QStringList() << "*" + fileExtension, QDir::Files);
    for (const QString &name : files) {
        QStandardItem * item = new QStandardItem(name.left(name.size() - 8));
        model.appendRow(item);
        title.push_back(name.left(name.size() - 8));
    }
    ui->listView->setModel(&model);
}

launch::~launch()
{
    delete ui;
}

void launch::on_newButton_clicked()
{
    mode = NewProject;
    ui->stackedWidget->setCurrentIndex(1);
}

void launch::on_buttonBox_accepted()
{
    QString raw = ui->nameEdit->text();
    int i = 1;
    while (title.contains(ui->nameEdit->text()))
    {
        ui->nameEdit->setText(raw + "-" + QString::number(i));
    }
    // launch mainwindow
    if (mode == NewProject)
    {
        width = ui->widthEdit->text().toInt();
        height = ui->heightEdit->text().toInt();
        path = QString(HISTORY_DIR) + "/" + ui->nameEdit->text() + ".xPixelx";
        title_ = ui->nameEdit->text();
    }
    MainWindow * w = new MainWindow(mode, width, height, path, title_, this);
    w->show();
}

void launch::on_listView_clicked(const QModelIndex &index)
{
    mode = HistoryProject;
    ui->stackedWidget->setCurrentIndex(0);

    QStandardItem * clickedItem = model.itemFromIndex(index);
    title_ = clickedItem->text();
    path = QString(HISTORY_DIR) + "/" + clickedItem->text() + ".xPixelx";

    // read info
    xPixelxFile * file = new xPixelxFile(path);
    file->readFile();
    width = file->width();
    height = file->height();

    ui->widthLabel->setText(QString::number(width));
    ui->heightLabel->setText(QString::number(height));

    QImage shotcut(width*PIXEL_SHOTCUT_SIZE, height*PIXEL_SHOTCUT_SIZE, QImage::Format_RGB32);
    QVector <QColor> tempImage = file->getImageVector();
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            for (int block_i=0+(int)(PIXEL_SHOTCUT_SIZE)*i;block_i<(int)(PIXEL_SHOTCUT_SIZE)*(i+1);block_i++) {
                for (int block_j=0+(int)(PIXEL_SHOTCUT_SIZE)*j;block_j<(int)(PIXEL_SHOTCUT_SIZE)*(j+1);block_j++) {
                    shotcut.setPixel(block_j, block_i, tempImage[width*i+j].rgb());
                }
            }
        }
    }
    QPixmap pixmap = QPixmap::fromImage(shotcut);
    ui->shotcutLabel->setPixmap(pixmap);
}

