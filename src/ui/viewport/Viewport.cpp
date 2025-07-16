#include "Viewport.h"
#include "ui_Viewport.h"

Viewport::Viewport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Viewport)
{
    ui->setupUi(this);

    _renderImage = ui->imageLabel;
}

QLabel* Viewport::getRenderImage() const
{
    return _renderImage;
}