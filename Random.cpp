#include "Random.h"

#include <random>
#include <iostream>

static std::mt19937 gen;

namespace Random {

    WeightedPicker::WeightedPicker(int* weights, int num) {
        numWeights = num;
        weightSums = new int[numWeights];
        totalWeight = 0;
        // std::cout << "weights: ";
        for (int i = 0; i < numWeights; i++) {
            totalWeight += weights[i];
            weightSums[i] = totalWeight;
            // std::cout << totalWeight << " ";
        }
        // std::cout << std::endl;
    }
    WeightedPicker::~WeightedPicker() {
        delete weightSums;
    }

    int WeightedPicker::pick() {
        int val = RandomInteger(totalWeight);
        int lower = 0;
        int upper = numWeights - 1;
        int mid;
        int dummy;
        // std::cout << "pick (" << val << "): ";
        while (val >= weightSums[lower]) {
            // std::cout << lower << " " << upper << " | ";
            // std::cin >> dummy;
            if (upper - lower == 1) {
                // std::cout << "-- 1 apart, must be " << upper << " -- ";
                lower = upper;
            } else {
                mid = (upper + lower) / 2;
                // std::cout << "[" << mid << "->" << weightSums[mid] << "]";
                if (val < weightSums[mid]) {
                    upper = mid;
                } else {
                    lower = mid;
                }
            }
        }
        return lower;
    }

    int RandomInit(unsigned int seed) {
        if (seed == 0) {
            std::random_device rd;
            seed = rd();
            gen.seed(seed); 
        }
        else {
            gen.seed(seed);
        }
        return seed;
    }

    int RandomInteger(int Range) {
        return RandomIntegerRange(0, Range - 1);
    }

    int RandomIntegerRange(int LowerBound, int UpperBound) {
        static std::uniform_int_distribution<int> dis;
        return dis(gen, std::uniform_int_distribution<int>::param_type{LowerBound, UpperBound});
    }

    void testPicker () {
        int weights[5] = {7, 7, 3, 2, 1};
        int results[5] = {0, 0, 0, 0, 0};
        WeightedPicker picker(weights, 5);
        for (int i = 0; i < 2000; i++) {
            // std::cout << picker.pick() << std::endl;
            results[picker.pick()]++;
        }
        std::cout << std::endl;
        for (int i = 0; i < 5; i++) {
            std::cout << i << " - " << results[i] << std::endl;
        }
    }

    void testRandomInteger () {
        int buckets[10];
        for (int i = 0; i < 10; i++) {
            buckets[i] = 0;
        }
        for (int i = 0; i < 1000; i++) {
            buckets[Random::RandomInteger(10)]++;
        }
        for (int i = 0; i < 10; i++) {
            std::cout << buckets[i] << "  ";
        }
        std::cout << std::endl;
    }
}
