#include "mainwindow.h"
#include "qwertz.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
    int matrix[3][10] =
    {
        {*"Q", *"W", *"E", *"R", *"T", *"Z", *"U", *"I", *"O", *"P"},
        {0, *"A", *"D", *"F", *"G", *"H", *"J", *"K", *"L", 0},
        {0, *"Y", *"X", *"C", *"V", *"B", *"N", *"M", 0, 0 }
    };

    int *matrix_rows[3] = {matrix[0], matrix[1], matrix[2]};

    QWERTZ *qwert = new QWERTZ(matrix_rows);

    qDebug() << "A - D" << qwert->getDistance(65, 68);
    qDebug() << "T - M" << qwert->getDistance(84, 77);
    qDebug() << "J - Y" << qwert->getDistance(74, 89);
    qDebug() << "V - Y" << qwert->getDistance(86, 89);

}
