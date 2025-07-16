#include "ViewportWidget.h"
#include "ui_ViewportWidget.h"

ViewportWidget::ViewportWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ViewportWidget)
{
    _ui->setupUi(this);

    _renderImage = _ui->imageLabel;
}

QLabel* ViewportWidget::getRenderImage() const
{
    return _renderImage;
}