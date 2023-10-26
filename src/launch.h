#ifndef LAUNCH_H
#define LAUNCH_H

#include "../inc/global_def.h"
#include "mainwindow.h"

namespace Ui {
class launch;
}

class launch : public QDialog
{
    Q_OBJECT

public:
    explicit launch(QWidget *parent = nullptr);
    ~launch();

private slots:
    void on_newButton_clicked();
    void on_buttonBox_accepted();
    void on_listView_clicked(const QModelIndex &);

private:
    Ui::launch *ui;
    int mode;
    int width, height;
    QString path, title_;
    QStandardItemModel model;
    QVector <QString> title;
};

#endif // LAUNCH_H
