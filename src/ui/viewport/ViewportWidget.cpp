#include "ViewportWidget.h"
#include "ui_ViewportWidget.h"

ViewportWidget::ViewportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewportWidget)
{
    ui->setupUi(this);

    _renderImage = ui->imageLabel;
}

QLabel* ViewportWidget::getRenderImage() const
{
    return _renderImage;
}