#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewport/Viewport.h"
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

    Viewport* _viewport;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetImage(const QImage& image);
    void showMenu();
};

#endif // MAINWINDOW_H
