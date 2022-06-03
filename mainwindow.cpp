#include "mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    show();
}

void MainWindow::setupUI(){
    vLayout = new QVBoxLayout();
    hLayout = new QHBoxLayout();

    input = new QLineEdit();

    output = new QLabel("Resultat");
    button = new QPushButton("Chercher");

    connect(button, &QPushButton::clicked, this, &MainWindow::find);

    vLayout->addWidget(input);

    hLayout->addWidget(output);
    hLayout->addWidget(button);

    vLayout->addLayout(hLayout);

    setLayout(vLayout);
}

/**
 * @brief MainWindow::find
 */
void MainWindow::find(){
    //Call find func
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete button;
    delete input;
    delete output;
    delete hLayout;
    delete vLayout;
}

