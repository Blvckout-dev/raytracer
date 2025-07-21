#include "ViewportWidget.h"
#include "ui_ViewportWidget.h"

ViewportWidget::ViewportWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ViewportWidget)
{
    _ui->setupUi(this);

    _renderImage = _ui->imageLabel;
}

ViewportWidget::~ViewportWidget()
{
    delete _ui;
}

QLabel* ViewportWidget::getRenderImage() const
{
    return _renderImage;
}