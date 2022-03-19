#pragma once
#include <chrono>
#include <stdint.h>

namespace m1{
    class Timer{

        public:

        Timer():
            startTime{std::chrono::high_resolution_clock::now()}
        {
        }

        void Restart(){
            startTime = std::chrono::high_resolution_clock::now();
        }

        uint64_t ElapsedNano(){
            return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::ratio<1,1000000000>>>(std::chrono::high_resolution_clock::now() - startTime).count();
        }

        uint64_t ElapsedMicro(){
            return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::ratio<1,1000000>>>(std::chrono::high_resolution_clock::now() - startTime).count();
        };

        uint64_t ElapsedMilli(){
            return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::ratio<1,1000>>>(std::chrono::high_resolution_clock::now() - startTime).count();
        }

        uint64_t ElapsedSec(){
            return std::chrono::duration_cast<std::chrono::duration<uint64_t, std::ratio<1,1>>>(std::chrono::high_resolution_clock::now() - startTime).count();
        }

        private:

        std::chrono::high_resolution_clock::time_point startTime;

    };
}