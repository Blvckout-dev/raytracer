#include "MainWindow.h"
#include "ui_MainWindow.h"

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

void MainWindow::setImage(const QImage &image)
{
    _viewportWidget->getRenderImage()->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::showMenu()
{
    auto menu = new MenuWidget(this);
    ui->gridLayout->addWidget(menu, 0, 0);
}
