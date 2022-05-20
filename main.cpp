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

    qDebug() << "T - I" << qwert->getDistance(84, 73);
    qDebug() << "I - M" << qwert->getDistance(73, 77);
    qDebug() << "T - U" << qwert->getDistance(84, 85);
    qDebug() << "U - S" << qwert->getDistance(85, 83);

    qDebug() << "TIM should be ~5" << qwert->getLength(QString("TIM"));
    qDebug() << "TITUS should be ~16.3" << qwert->getLength(QString("TITUS"));

}
