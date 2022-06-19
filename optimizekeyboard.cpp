#include "optimizekeyboard.h"

#include <vector>
#include <algorithm>


bool cmp(std::pair<char, uint64_t>& a, std::pair<char, uint64_t>& b)
{
    return a.second < b.second;
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

    /* Previous steps create a map in alphabetic order, so it needs to be sorted first */
    std::vector<std::pair<uint64_t, char>> *vec = new std::vector<std::pair<uint64_t, char>>();
    for (int i = 0; i < size + 4; i++ )
    {
        std::pair<uint64_t, char> pair;
        // Dirty hack because we have 30 keys and only 26 letters...
        if(i > 25)
        {
            pair = std::make_pair(0, 0);
        }
        else
        {
            pair = std::make_pair(usage[i], (char)(i+65));
        }
        vec->emplace_back(pair);
    }

    std::sort(vec->begin(), vec->end(), [](auto const& lhs, auto const& rhs) { return rhs < lhs; });

    std::vector<int> letters;
    for (int i = 0; i < size + 4; i++)
    {
        std::pair<uint64_t, char> pair = vec[0][i];
        letters.emplace_back(pair.second);
    }

    /**
     * Now we need to find a way to place the letters in the correct order given the optimizedUsagePattern
     */

    int colIndex = (row2.size() / 2) - 1; // Center column
    int usageIndex = 0; // Index in usage map

    for (int i = 0; i < row2.size() / 2; i++ )
    {

        switch (i)
        {
        case 0:
            {
                row2.at(colIndex + i) = letters[usageIndex++];
                row1.at(colIndex + i) = letters[usageIndex++];
                row3.at(colIndex + i) = letters[usageIndex++];
                break;
            }
        default:
            {
                row2.at(colIndex + i) = letters[usageIndex++];
                row1.at(colIndex + i) = letters[usageIndex++];
                row3.at(colIndex + i) = letters[usageIndex++];
                if( usageIndex < 30) // Still hacking because less letters than keys on keyboard...
                {
                    row2.at(colIndex - i) = letters[usageIndex++];
                    row1.at(colIndex - i) = letters[usageIndex++];
                    row3.at(colIndex - i) = letters[usageIndex++];
                }
                break;
            }
        }
    }

    retKb->emplace_back(row1);
    retKb->emplace_back(row2);
    retKb->emplace_back(row3);

    return retKb;
}
