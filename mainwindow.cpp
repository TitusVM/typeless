#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui = new TypelessUI(this);
    createUI();
}

void MainWindow::createUI()
{
    setCentralWidget(this->ui);
}


MainWindow::~MainWindow()
{
}

