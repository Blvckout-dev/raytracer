#include "MenuWidget.h"

MenuWidget::MenuWidget(QWidget* parent)
  : QFrame(parent)
{
    ui.setupUi(this);
}

MenuWidget::~MenuWidget() = default;