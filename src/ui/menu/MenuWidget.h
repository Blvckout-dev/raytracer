#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include "ui_MenuWidget.h"

class MenuWidget : public QFrame {
    Q_OBJECT

public:
    explicit MenuWidget(QWidget* parent = nullptr);
    ~MenuWidget();

private:
    Ui::Frame ui;
};

#endif