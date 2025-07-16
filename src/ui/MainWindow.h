#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewport/ViewportWidget.h"
#include "menu/MenuWidget.h"
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    ViewportWidget* _viewportWidget;
    MenuWidget* _menuWidget;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setImage(const QImage& image);
    void showMenu();
};

#endif // MAINWINDOW_H
