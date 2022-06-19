#include "mainwindow.h"
#include "optimizekeyboard.h"
#include <QApplication>

OptimizeKeyboard *OptimizeKeyboard::instance = 0; // ??? Tim said to do that...

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
