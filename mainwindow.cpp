#include "mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    vLayout = new QVBoxLayout();
    hLayout = new QHBoxLayout();

    input = new QLineEdit();

    output = new QLabel("Resultat");
    button = new QPushButton("Chercher");

    connect(input, &QLineEdit::textChanged, this, &MainWindow::updateText);
    connect(button, &QPushButton::clicked, this, &MainWindow::find);

    vLayout->addWidget(input);

    hLayout->addWidget(output);
    hLayout->addWidget(button);

    vLayout->addLayout(hLayout);

    setLayout(vLayout);

    show();
}

/**
 * @brief MainWindow::find
 */
void MainWindow::find(){
    //Call find func
}

/**
 * @brief MainWindow::updateText
 * @param text
 */
void MainWindow::updateText(const QString& text){
    // call the calculate function, and put the output in "output"
    output->setText(text);
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

