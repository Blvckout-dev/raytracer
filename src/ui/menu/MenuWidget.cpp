#include "MenuWidget.h"
#include "ui_MenuWidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QFrame(parent),
    _ui(new Ui::MenuWidget)
{
    _ui->setupUi(this);

    connect(_ui->exitButton, &QToolButton::clicked, qApp, &QCoreApplication::quit);
}

MenuWidget::~MenuWidget()
{
    delete _ui;
}