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

    addStyles();

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

void MainWindow::addStyles(){
    QString stylesLineEdit="background-color: #f1f1f1";
    QString stylesLabel="background-color: #f1f1f1;";
    QString stylesButton="border-radius: 5px;"
                         "background-color: lightblue;"
                         "min-width: 90px;"
                         "width: 50%;"
                         "min-height: 20px;"
                         "border-style: outset;"
                         "border-width: 2px;"
                         "border-color: white;";
    QString stylesSelf="background-color: white";

    input->setStyleSheet(stylesLineEdit);
    output->setStyleSheet(stylesLabel);
    button->setStyleSheet(stylesButton);
    setStyleSheet(stylesSelf);
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

