#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <algorithm>

namespace Random {
    int RandomInit(unsigned int Seed);
    // Return [0, Range)
    int RandomInteger(int Range);
    // Returns [LB, UB]
    int RandomIntegerRange(int LowerBound, int UpperBound);
    // Advance the RNG state, by "throwing away" some numbers
    void discard(unsigned long z);

    template<class C>
    void Shuffle(C& c)
    {
        auto first = c.begin();
        auto last = c.end();
        auto n = last - first;
        for (auto i = n-1; i > 0; --i) {
            std::swap(first[i], first[RandomIntegerRange(0, static_cast<int>(i))]);
        }
    }
}

#endif // __RANDOM_H__
