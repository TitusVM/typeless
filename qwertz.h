#ifndef QWERTZ_H
#define QWERTZ_H
#include "keyboard.h"


class QWERTZ : public Keyboard
{
public:
    QWERTZ(int **matrix);
    double getDistance(QChar one, QChar two);
    double getDistance(int firstAscii, int secondAscii);
    double getLength(QString word);

private:
    Graph *graph;
    int **matrix;

};

#endif // QWERTZ_H
