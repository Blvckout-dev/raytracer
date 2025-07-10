#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include "ui_menu.h"

class Menu : public QFrame {
    Q_OBJECT

public:
    explicit Menu(QWidget* parent = nullptr);
    ~Menu();
};

#endif