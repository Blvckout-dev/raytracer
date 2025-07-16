#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _viewportWidget = new ViewportWidget(this);
    ui->gridLayout->addWidget(_viewportWidget, 0, 0);

    _menuWidget = new MenuWidget(this);
    _menuWidget->setVisible(false);
    ui->gridLayout->addWidget(_menuWidget, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        toggleMenu();
        event->accept();
    } else {
        QMainWindow::keyPressEvent(event); // Pass other keys to base class
    }
}

void MainWindow::setImage(const QImage &image)
{
    _viewportWidget->getRenderImage()->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::toggleMenu()
{
    _menuWidget->setVisible(!_menuWidget->isVisible());
}
