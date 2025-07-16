#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _viewport = new Viewport(this);
    ui->gridLayout->addWidget(_viewport, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage(const QImage &image)
{
    _viewport->getRenderImage()->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::showMenu()
{
    auto menu = new MenuWidget(this);
    ui->gridLayout->addWidget(menu, 0, 0);
}
