#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "graph.h"
#include <QVector>

#define NB_ROWS 3
#define NB_COLUMNS 10


class Keyboard
{
public:
    Keyboard(int **matrix) {};
    virtual double getDistance(QChar one, QChar two) = 0;
    virtual double getDistance(int firstAscii, int secondAscii) = 0;
    virtual double getLength(QString word) = 0;

protected:
    Graph *graph;
    int **matrix;


};

#endif // KEYBOARD_H
