#ifndef MENU_H
#define MENU_H

#include <QFrame>

namespace Ui {
    class MenuWidget;
}

class MenuWidget : public QFrame {
    Q_OBJECT
private:
    Ui::MenuWidget* _ui;

public:
    explicit MenuWidget(QWidget* parent = nullptr);
    ~MenuWidget();
};

#endif