#include "qwertz.h"

QWERTZ::QWERTZ(int** matrix) : Keyboard(nullptr)
{
    this->graph = new Graph(26);
    this->matrix = matrix;
}

/**
 * @brief QWERTZ::getDistance uses the keyboards letter matrix to estimate a symbolic physical distance between two characters
 * @param one From character
 * @param two To character
 * @return double Distance between the two given characters
 */

double QWERTZ::getDistance(int firstAscii, int secondAscii)
{
    if(firstAscii == secondAscii) return 0;
    double ponderation = this->graph->getPonderation((char)firstAscii, (char)secondAscii);
    if(ponderation != 0) return ponderation;

    double dist = 0;
    int firstIndex[2] = {-1, -1};
    int secondIndex[2] = {-1, -1};
    for(size_t i = 0; i < NB_ROWS; i++)
    {
        for(size_t j = 0; j < NB_COLUMNS; j++)
        {
            if (this->matrix[i][j] == firstAscii)
            {
                firstIndex[0] = i + 1;
                firstIndex[1] = j + 1;
                break;
            }
        }
        if(firstIndex[0] != -1) break;
    }

    for(size_t i = 0; i < NB_ROWS; i++)
    {
        for(size_t j = 0; j < NB_COLUMNS; j++)
        {
            if (this->matrix[i][j] == secondAscii)
            {
                secondIndex[0] = i + 1;
                secondIndex[1] = j + 1;
                break;
            }
        }
        if(secondIndex[0] != -1) break;
    }

    dist = sqrt(pow(firstIndex[0] - secondIndex[0],2) + pow(firstIndex[1] - secondIndex[1],2));
    this->graph->ajouterArc(firstAscii, secondAscii, dist);

    return dist;
}

double QWERTZ::getDistance(QChar one, QChar two)
{
    int firstAscii = one.toUpper().toLatin1();
    int secondAscii = two.toUpper().toLatin1();

    return getDistance(firstAscii, secondAscii);

}


double QWERTZ::getLength(QString word)
{
    double length = 0;

    for (size_t i = 0; i < word.length() - 1; i++)
    {
        length += this->getDistance(word[i], word[i+1]);
    }

    return length;
}
