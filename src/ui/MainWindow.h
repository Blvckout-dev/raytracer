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
    Ui::MainWindow* _ui;

    ViewportWidget* _viewportWidget;
    MenuWidget* _menuWidget;

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setImage(const QImage& image);
    void toggleMenu();
};

#endif // MAINWINDOW_H
