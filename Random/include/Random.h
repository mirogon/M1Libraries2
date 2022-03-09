#pragma once
#include <cstdlib>
#include <random>

namespace m1{
    class Random{
        public:

        Random(){
            mt.seed(rd());
        }

        uint32_t RandomNumber(long minInclusive, long maxInclusive){
            std::uniform_int_distribution<uint32_t> distribution(minInclusive, maxInclusive);
            return distribution(mt);
        }

        private:
        std::random_device rd;
        std::mt19937 mt;

    };
}
