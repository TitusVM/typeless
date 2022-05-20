#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Graph
{
private:
    int size;
    int** matrix;
    bool* tabVisited;
    bool* tabRencontred;

    void parseFile(std::string* filePath);
    void init(int nb);
    int visiterLeSommet(char s1);
    void visitePriorite(char s1);

public:
    Graph(int nb);
    Graph(std::string* filePath);
    ~Graph();
    void afficherGraphe();
    void ajouterArc(char s1, char s2, int pond = 1);
    void ajouterArcOriente(char s1, char s2, int pond = 1);
    int  degree(char s);
    bool estConnexe();
    bool estFortementConnexe();
    void visited(char s1);
    void destroy();

    void parcoursProfRecursif(char s1);
    void parcoursProfIteratif(char s1);
    void parcoursLargIteratif(char s1);

    int parcoursARPM(char s1);
    void parcoursACPC(char s1);

    void VSPR(char s1);
    void VSPNR(char s1);
    void VSLNR(char s1);

    void parcoursProfIteratifSupEgal3(char s1); //Exercice 3
    void VSPNRSupEgal3(char s1);

    int poidsTotal();
    int degreeMax();

    inline int getSize() { return this->size; };

};
