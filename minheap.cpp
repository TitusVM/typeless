#include "minheap.h"
#include <iostream>

MinHeap::MinHeap()
{
    Node tmp = Node('0', INT_MAX);
    this->heap.emplace_back(tmp);
}

void MinHeap::rendreMinimier()
{
    if (!this->isEmpty())
    {
        int index = 1;
        bool estMinimier = false;

        while (index * 2 < this->heap.size() && !estMinimier)
        {
            const unsigned int premierIndex = index * 2;
            const unsigned int deuxiemeIndex = premierIndex + 1;
            unsigned int maxIndex = premierIndex;

            if (deuxiemeIndex > this->heap.size())
            {
                if (this->heap[deuxiemeIndex].prio < this->heap[premierIndex].prio)
                {
                    maxIndex = deuxiemeIndex;
                }
            }

            if (this->heap[maxIndex].prio < this->heap[index].prio)
            {
                this->echange(maxIndex, index);
            }
            else
            {
                estMinimier = true;
            }
        }
    }
}

void MinHeap::add(Node* node)
{
    this->add(node->label, node->prio);
}

void MinHeap::add(char s1, int prio)
{
    Node tmp = Node(s1, INT_MAX);
    this->heap.emplace_back(tmp);
    this->diminuerPrio(s1, this->heap.size() - 1, prio);
}

void MinHeap::diminuerPrio(char s1, int index, int nouvellePrio)
{
    if (nouvellePrio > this->heap[index].prio) {
        std::cout << "Erreur";
    }

    int indexExiste = this->existe(s1);

    switch (indexExiste)
    {
        case -1:
        {
            this->heap[index].prio = nouvellePrio;
            while (index > 1 && this->heap[index / 2].prio > this->heap[index].prio)
            {
                echange(index, index / 2);
                index /= 2;
            }
            break;
        }
        default:
        {
            this->heap[indexExiste].prio = nouvellePrio;
            this->heap.pop_back();
            this->rendreMinimier();
            break;
        }
    }
}

Node MinHeap::minimum()
{
    if (this->isEmpty()) {
        return this->heap[0];
    }
    Node min = Node(this->heap[1]);
    this->heap[1] = this->heap[this->heap.size() - 1];
    this->heap.pop_back();
    rendreMinimier();
    return min;
}

void MinHeap::echange(int i, int j)
{
    Node* tmp = new Node(this->heap[i]);
    this->heap[i] = this->heap[j];
    this->heap[j] = *tmp;
    delete tmp;
}

bool MinHeap::isEmpty()
{
    return this->heap.size() <= 1;
}

Node MinHeap::preleverTete()
{
    return this->minimum();
}

int MinHeap::existe(char s1)
{
    for (size_t i = 1; i < this->heap.size() - 1; i++)
    {
        if (this->heap[i].label - 65 == s1 - 65)
        {
            return (int)i;
        }
    }
    return -1;
}
