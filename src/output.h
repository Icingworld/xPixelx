#ifndef OUTPUT_H
#define OUTPUT_H

#include <QDialog>
#include "../inc/global_def.h"

namespace Ui {
class output;
}

class output : public QDialog
{
    Q_OBJECT

public:
    explicit output(int, int, double &, QString &, QWidget *parent = nullptr);
    ~output();

private:
    Ui::output *ui;
    int width, height;
    double & mult;
    QString & name;
    QVector <double> mult_vector{1.0,0.1,0.2,0.25,0.5,0.75,0.8,0.9};
    QString getSize();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_multCombo_currentIndexChanged(int);
};

#endif // OUTPUT_H
