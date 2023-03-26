#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <algorithm>

namespace Random {
    class WeightedPicker {
    public:
        WeightedPicker(int* initWeights, int num);
        ~WeightedPicker();

        int* weightSums;
        int numWeights;
        int totalWeight;

        int pick();
    };

    int RandomInit(unsigned int Seed);
    // Return [0, Range)
    int RandomInteger(int Range);
    // Returns [LB, UB]
    int RandomIntegerRange(int LowerBound, int UpperBound);

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

    template<class ItemClass>
    void shuffleArray(ItemClass array[], int size) {
        ItemClass temp;
        int pick;
        for (int i = size-1; i > 0; --i) {
            pick = RandomInteger(i);
            temp = array[i];
            array[i] = array[pick];
            array[pick] = temp;
            // std::swap(array[i], RandomInteger(i));
        }
    }
}

#endif // __RANDOM_H__
