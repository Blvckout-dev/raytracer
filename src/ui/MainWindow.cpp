#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "menu/MenuWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetImage(const QImage &image)
{
    // ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::showMenu()
{
    auto menu = new MenuWidget(this);
    ui->gridLayout->addWidget(menu, 0, 0);
}
