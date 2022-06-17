#ifndef OPTIMIZEKEYBOARD_H
#define OPTIMIZEKEYBOARD_H

#include <vector>
#include <cstdint>

/**
 * @brief The OptimizeKeyboard class is a singleton that allows the optimization of a keyboard of a given usage pattern
 * ASYNC, don't call in threads.
 */
class OptimizeKeyboard // SINGLETON
{

public:
    static OptimizeKeyboard *getInstance()
    {
        if(instance == nullptr) instance = new OptimizeKeyboard();
        return instance;
    }
    std::vector<std::vector<int>>* optimize(uint64_t*, int);

// PRIVATE CONSTRUCTOR
private:
    OptimizeKeyboard();

// PRIVATE ATTRIBUTES
private:
    // SINGLETON
    static OptimizeKeyboard *instance;
    // TOOLS
    const std::vector<std::vector<int>> optimizedUsagePattern =
    {
        {4,3,2,1,1,-1,-1,-2,-3,-4},
        {4,3,2,1,1,-1,-1,-2,-3, 0},
        {0,3,2,1,1,-1,-1,-2, 0, 0}
    };
};

#endif // OPTIMIZEKEYBOARD_H
