#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _viewportWidget = new ViewportWidget(this);
    _ui->gridLayout->addWidget(_viewportWidget, 0, 0);

    _menuWidget = new MenuWidget(this);
    _ui->gridLayout->addWidget(_menuWidget, 0, 0);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        _menuWidget->toggleMenu();
        event->accept();
    } else {
        QMainWindow::keyPressEvent(event); // Pass other keys to base class
    }
}

void MainWindow::setImage(const QImage &image)
{
    _viewportWidget->getRenderImage()->setPixmap(QPixmap::fromImage(image));
}
