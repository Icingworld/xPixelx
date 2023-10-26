#include "output.h"
#include "ui_output.h"

output::output(int _width, int _height, double & _mult, QString & _name, QWidget * parent) :
    QDialog(parent),
    ui(new Ui::output),
    width(_width),
    height(_height),
    mult(_mult),
    name(_name)
{
    ui->setupUi(this);

    ui->sizeLabel->setText(getSize());
}

output::~output()
{
    delete ui;
}

void output::on_buttonBox_accepted()
{
    name = ui->nameEdit->text();
}

void output::on_buttonBox_rejected()
{

}

void output::on_multCombo_currentIndexChanged(int index)
{
    mult = mult_vector[index];
    ui->sizeLabel->setText(getSize());
}

QString output::getSize()
{
    return QString::number(PIXEL_SIZE * width * mult) + ", " + QString::number(PIXEL_SIZE * height * mult);
}
