#pragma once
#include <vector>

struct Node
{
    Node(char label, int prio) // KISS pas besoin de parent
    {
        this->label = label;
        this->prio = prio;
    }

    char label;
    int prio;
};

class MinHeap
{
public:
    MinHeap();
    void rendreMinimier();
    void echange(int i, int j);
    void add(Node *node);
    void add(char label, int prio);
    Node preleverTete();
    Node minimum();
    bool isEmpty();
    inline int getSize() { return this->heap.size(); };

private:
    std::vector<Node> heap;
    void diminuerPrio(char s1, int index, int nouvellePrio);
    int existe(char s1);
};
