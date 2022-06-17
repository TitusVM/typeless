#include "graph.h"
#include "tools.h"
#include "minheap.h"
#include <stack>
#include <list>

#include <QDebug>

Graph::Graph(int nb)
{
    init(nb);
}

Graph::Graph(std::string* filePath)
{
    this->parseFile(filePath);
}

void Graph::afficherGraphe()
{
    std::cout << "\t";
    for (char i = 65; i < this->size + 65; i++)
    {
        std::cout << i << "\t";
    }
    std::cout << "\n";
    for (size_t i = 0; i < this->size; i++)
    {
        std::cout << char(i + 65) << "\t";
        for (size_t j = 0; j < this->size; j++)
        {
            std::cout << this->matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void Graph::ajouterArc(char s1, char s2, double pond)
{
    int index1 = s1 - 65;
    int index2 = s2 - 65;

    this->matrix[index1][index2] = pond;
    this->matrix[index2][index1] = pond;
}

void Graph::ajouterArcOriente(char s1, char s2, double pond)
{
    int index1 = s1 - 65;
    int index2 = s2 - 65;

    this->matrix[index1][index2] = pond;
}

double Graph::getPonderation(char s1, char s2)
{
    int index1 = s1 - 65;
    int index2 = s2 - 65;
    return this->matrix[index1][index2];
}

int Graph::degree(char s)
{
    int index = s - 65;
    int degre = 0;
    for (size_t i = 0; i < this->size; i++)
    {
        degre += int(this->matrix[index][i] != 0);
    }
    return degre;
}

bool Graph::estConnexe()
{
    for (size_t i = 0; i < this->size; i++)
    {
        if (!this->tabVisited[i])
            return false;
    }
    return true;
}

bool Graph::estFortementConnexe()
{
    int A = 0; // nombre d'arretes est la somme des degres /2
    for (size_t i = 0; i < this->size; i++)
    {
        A += degree(char(i + 65));
    }
    return A/static_cast<double>(2) > (this->size * log(this->size));
}

void Graph::visited(char s1)
{
    if (this->tabVisited[(int)s1 - 65] == false)
    {
        this->tabVisited[(int)s1 - 65] = true;
        std::cout << s1;
        for (size_t i = 0; i < this->size; i++)
        {
            if (this->matrix[(int)s1 - 65][i] != 0)
            {
                visited((char)(i+65));
            }
        }
    }
}

void Graph::destroy()
{
    for (size_t i = 0; i < this->size; i++)
    {
        for (size_t j = 0; j < this->size; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
    delete[] this->tabRencontred;
    delete[] this->tabVisited;
    delete[] this->matrix;
}

// startregion PARCOURS

void Graph::parcoursProfRecursif(char s1)
{
    // Reset values on tabVisited
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabVisited[i] = false;
    }

    int start = s1 - 65;
    int end = this->size;
    bool secondPassFlag = false;
    for (size_t i = start; i <= end; i++)
    {
        if (i != end)
        {
            this->VSPR(i + 65);
        }
        else if (!secondPassFlag)
        {
            int tmp = i;
            i = -1;
            end = tmp - 1;
            secondPassFlag = true;
        }
    }
}

void Graph::parcoursProfIteratif(char s1)
{
    // Reset values on tabVisited
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabVisited[i] = false;
    }
    // Reset values on tabRencontred
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabRencontred[i] = false;
    }

    int start = s1 - 65;
    int end = this->size;
    bool secondPassFlag = false;
    for (size_t i = start; i <= end; i++)
    {
        if (i != end)
        {
            this->VSPNR(i + 65);
        }
        else if (!secondPassFlag)
        {
            int tmp = i;
            i = -1;
            end = tmp - 1;
            secondPassFlag = true;
        }
    }
}

void Graph::parcoursLargIteratif(char s1)
{
    // Reset values on tabVisited
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabVisited[i] = false;
    }
    // Reset values on tabRencontred
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabRencontred[i] = false;
    }

    int start = s1 - 65;
    int end = this->size;
    bool secondPassFlag = false;
    for (size_t i = start; i <= end; i++)
    {
        if (i != end)
        {
            this->VSLNR(i + 65);
        }
        else if (!secondPassFlag)
        {
            int tmp = i;
            i = -1;
            end = tmp - 1;
            secondPassFlag = true;
        }
    }
}

void Graph::VSPR(char s1)
{
    int sommet = s1 - 65;
    if (!this->tabVisited[sommet]) {
        this->tabVisited[sommet] = true;
        std::cout << (char)(sommet + 65) << "->";
        for (size_t i = 0; i < this->size; i++)
        {
            if (this->matrix[sommet][i] != 0)
            {
                VSPR(i + 65);
            }
        }
    }
}

void Graph::VSPNR(char s1)
{
    int sommet = s1 - 65;
    std::stack<int> *pileSommets = new std::stack<int>;
    if (!this->tabVisited[sommet])
    {
        this->tabRencontred[sommet] = true;
        pileSommets->push(sommet);
        while (!pileSommets->empty())
        {
            int sommetCourant = (int)pileSommets->top();
            pileSommets->pop();

            this->tabVisited[sommetCourant] = true;
            std::cout << (char)(sommetCourant + 65) << "->";
            /* TRAITEMENT */
            for (size_t i = 0; i < this->size; i++)
            {
                if (this->matrix[sommetCourant][i] != 0 && !this->tabVisited[i] && !this->tabRencontred[i])
                {
                    this->tabRencontred[i] = true;
                    pileSommets->push(i);
                }
            }
        }
    }
}

void Graph::VSLNR(char s1)
{
    int sommet = s1 - 65;
    std::list<int> *queueSommets = new std::list<int>();
    if (!this->tabVisited[sommet])
    {
        this->tabRencontred[sommet] = true;
        queueSommets->push_back(sommet);
        /* TRAITEMENT */
        while (!queueSommets->empty())
        {
            int sommetCourant = queueSommets->front();
            queueSommets->pop_front();
            this->tabVisited[sommetCourant] = true;
            std::cout << (char)(sommetCourant + 65) << "->";
            /* TRAITEMENT */
            for (size_t i = 0; i < this->size; i++)
            {
                if (this->matrix[sommetCourant][i] != 0 && !this->tabVisited[i] && !this->tabRencontred[i])
                {
                    this->tabRencontred[i] = true;
                    queueSommets->push_back(i);
                }
            }
        }
    }
}


int Graph::parcoursARPM(char s1)
{
    // Reset values on tabVisited
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabVisited[i] = false;
    }
    // Reset values on tabRencontred
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabRencontred[i] = false;
    }

    int start = s1 - 65;
    int end = this->size;
    bool secondPassFlag = false;
    int poids = 0;
    for (size_t i = start; i <= end; i++)
    {
        if (i != end)
        {
            poids += this->visiterLeSommet(i + 65);
            std::cout << "  ";
        }
        else if (!secondPassFlag)
        {
            int tmp = i;
            i = -1;
            end = tmp - 1;
            secondPassFlag = true;
        }
    }
    return poids;
}

int Graph::visiterLeSommet(char s1)
{
    MinHeap* queuePrio = new MinHeap();
    Node* node = new Node(s1, 1);
    int sommet = s1 - 65;
    int returnValue = 0;
    if (!this->tabVisited[sommet])
    {
        queuePrio->add(node);
    }
    while (!queuePrio->isEmpty())
    {
        Node* nodeCourant = new Node(queuePrio->preleverTete());
        int sommetCourant = nodeCourant->label - 65;
        int prioCourant = nodeCourant->prio;
        delete nodeCourant;

        this->tabVisited[sommetCourant] = true;
        returnValue += prioCourant;
        /* TRAITEMENT */
        std::cout << (char)(sommetCourant + 65) << "->";
        for (size_t i = 0; i < this->size; i++)
        {
            if (this->matrix[sommetCourant][i] != 0 && !this->tabVisited[i] && !this->tabRencontred[i])
            {
                int prioI = this->matrix[sommetCourant][i];
                this->tabRencontred[i] = true;
                Node* nodeI = new Node(i + 65, prioI);
                queuePrio->add(nodeI);
            }
        }
    }
    return returnValue;
}

void Graph::parcoursACPC(char s1)
{
    // Reset values on tabVisited
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabVisited[i] = false;
    }
    // Reset values on tabRencontred
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabRencontred[i] = false;
    }
    this->visitePriorite(s1);
}

void Graph::visitePriorite(char s1)
{
    int sommetCourant = s1 - 65;
    MinHeap* queuePrio = new MinHeap();
    if (!this->tabVisited[sommetCourant])
    {
        Node* nodeCourant = new Node(s1, 0);
        queuePrio->add(nodeCourant);
        while (!queuePrio->isEmpty())
        {
            Node* nodeCourant = new Node(queuePrio->preleverTete());
            int sommetCourant = nodeCourant->label - 65;
            int prioCourant = nodeCourant->prio;
            /* TRAITEMENT */
            qDebug() << (char)(sommetCourant + 65) << prioCourant << "; ";
            this->tabVisited[sommetCourant] = true;
            for (size_t i = 0; i < this->size; i++)
            {
                if (this->matrix[sommetCourant][i] != 0 && !this->tabVisited[i])
                {
                    int prioI = prioCourant + this->matrix[sommetCourant][i];
                    this->tabRencontred[i] = true;
                    Node* nodeI = new Node(i + 65, prioI);
                    queuePrio->add(nodeI);
                }
            }
        }
    }
}

// endregion

Graph::~Graph()
{
    this->destroy();
}

void Graph::parseFile(std::string* filePath)
{
    using namespace std;
    filebuf fBFile;

    if (fBFile.open(*filePath, ios::in))
    {
        istream iSFile(&fBFile);
        bool firstLine = true;
        while (iSFile)
        {
            char in[256];
            iSFile.getline(in, 256);

            if (firstLine)
            {
                init(stoi(in));
                firstLine = false;
            }
            else
            {
                string line = in;
                if (!line.empty())
                {
                    vector<string> args = Tools::splitLines(line, " ");
                    char sommet1 = args.at(0).at(0); // On assume que les strings ne font pas plus de 1 char
                    char sommet2 = args.at(1).at(0);
                    int ponderation;
                    if (args.size() == 3)
                    {
                        ponderation = args.at(2).at(0) - '0';
                    }
                    else
                    {
                        ponderation = 1;
                    }
                    this->ajouterArcOriente(sommet1, sommet2, ponderation);
                }
            }
        }
    }
    else
    {
        cout << "[ERROR] The path « " << *filePath << " » is incorrect !" << endl;
        exit(-1);
    }
}

void Graph::init(int nb)
{
    this->size = nb;
    this->tabVisited = new bool[nb];
    this->tabRencontred = new bool[nb];
    this->matrix = new double* [this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabVisited[i] = false;
        this->tabRencontred[i] = false;
        this->matrix[i] = new double[this->size];
        for (size_t j = 0; j < this->size; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

int Graph::poidsTotal()
{
    int poidsTotal = 0;
    for (size_t i = 0; i < this->size / 2; i++)
    {
        for (size_t j = 0; j < this->size; j++)
        {
            poidsTotal += this->matrix[i][j];
        }
    }
    return poidsTotal;
}

int Graph::degreeMax()
{
    int degree = 0;
    std::vector<int> allDegrees;
    for (size_t i = 0; i < this->size / 2; i++)
    {
        for (size_t j = 0; j < this->size; j++)
        {
            if (this->matrix[i][j] != 0)
            {
                degree++;
            }
        }
        allDegrees.push_back(degree);
        degree = 0;
    }
    int degreeMax = 0;
    for (size_t i = 0; i < allDegrees.size(); i++)
    {
        if (allDegrees[i] > degreeMax)
        {
            degreeMax = allDegrees[i];
        }
    }
    return degreeMax;
}

void Graph::parcoursProfIteratifSupEgal3(char s1)
{
    // Reset values on tabVisited
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabVisited[i] = false;
    }
    // Reset values on tabRencontred
    for (size_t i = 0; i < this->size; i++)
    {
        this->tabRencontred[i] = false;
    }

    int start = s1 - 65;
    int end = this->size;
    bool secondPassFlag = false;
    for (size_t i = start; i <= end; i++)
    {
        if (i != end)
        {
            this->VSPNRSupEgal3(i + 65);
        }
        else if (!secondPassFlag)
        {
            int tmp = i;
            i = -1;
            end = tmp - 1;
            secondPassFlag = true;
        }
    }
}

void Graph::VSPNRSupEgal3(char s1)
{
    int sommet = s1 - 65;
    std::stack<int>* pileSommets = new std::stack<int>;
    if (!this->tabVisited[sommet])
    {
        this->tabRencontred[sommet] = true;
        pileSommets->push(sommet);
        while (!pileSommets->empty())
        {
            int sommetCourant = (int)pileSommets->top();
            pileSommets->pop();
            if (this->degree((char)(sommetCourant + 65)) >= 3)
            {
                std::cout << (char)(sommetCourant + 65) << "->";
            }
            this->tabVisited[sommetCourant] = true;
            /* TRAITEMENT */
            for (size_t i = 0; i < this->size; i++)
            {
                if (this->matrix[sommetCourant][i] != 0 && !this->tabVisited[i] && !this->tabRencontred[i])
                {
                    this->tabRencontred[i] = true;
                    pileSommets->push(i);
                }
            }
        }
    }
}
