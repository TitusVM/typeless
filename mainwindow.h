#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "typelessui.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TypelessUI *ui;

    void createUI();


};
#endif // MAINWINDOW_H
