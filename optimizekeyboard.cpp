#include "optimizekeyboard.h"

#include <map>
#include <algorithm>

bool cmp(std::pair<char, uint64_t>& a, std::pair<char, uint64_t>& b)
{
    return a.second < b.second;
}

void sort(std::map<char, uint64_t> map)
{
    std::vector<std::pair<char, uint64_t>> pairVec;

    for(auto& it : map)
    {
        pairVec.push_back(it);
    }

    std::sort(pairVec.begin(), pairVec.end(), cmp);

    map.clear();

    for(auto& it : pairVec)
    {
        map.emplace(it);
    }
}

OptimizeKeyboard::OptimizeKeyboard()
{

}

/**
 * @brief OptimizeKeyboard::optimize should be able to optimize the keyboard layout to the specified usage pattern
 * @return
 */
std::vector<std::vector<int>>* OptimizeKeyboard::optimize(uint64_t * usage, int size)
{
    std::vector<std::vector<int>> *retKb = new std::vector<std::vector<int>>();
    std::vector<int> row1 = {0,0,0,0,0,0,0,0,0,0};
    std::vector<int> row2 = {0,0,0,0,0,0,0,0,0,0};
    std::vector<int> row3 = {0,0,0,0,0,0,0,0,0,0};

    /* Creating a sortable dictionnary */
    std::map<char, uint64_t> map;
    for(int i = 0; i < size; i++)
    {
        map.emplace((char)(i+65), usage[i]);
    }

    sort(map);

    /**
     * Now we need to find a way to place the letters in the correct order given the optimizedUsagePattern
     *
     */

    retKb->push_back(row3);
    retKb->push_back(row2);
    retKb->push_back(row1);

    return retKb;
}
