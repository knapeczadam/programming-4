#include "trash_the_cache_manager.h"

// Standard includes
#include <algorithm>
#include <chrono>
#include <ranges>

namespace dae
{
    void trash_the_cache_manager::calculate_data()
    {
        std::vector<game_object_3d> buffer(sample_);
        int stepSize = 1;

        // vector for storing time
        std::vector<float> times;

        for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
        {
            std::vector<long long> tempTimes;
            for (int i = 0; i < 10; ++i)
            {
                // measure time - start
                auto start = std::chrono::high_resolution_clock::now();
                for (size_t j = 0; j < buffer.size(); j += stepSize)
                {
                    buffer[j].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();
                // store the time difference between start and end
                const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                tempTimes.push_back(total);
            }
            
            // 3 liners
            // min-max
            // delete min and max
            // average

            
            // sort temp times
            std::ranges::sort(tempTimes);
            // remove first and last element
            tempTimes.pop_back();
            tempTimes.erase(tempTimes.begin());
            // calculate average
            long long sum = 0;
            for (const auto tempTime : tempTimes)
            {
                sum += tempTime;
            }
            times.push_back(static_cast<float>(sum) / static_cast<float>(tempTimes.size()));
        }
        data_ = times;
    }

    void trash_the_cache_manager::calculate_data_alt()
    {
        std::vector<game_object_3d_alt> buffer(sample_);
        int stepSize = 1;

        // vector for storing time
        std::vector<float> times;

        for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
        {
            std::vector<long long> tempTimes;
            for (int i = 0; i < 10; ++i)
            {
                // measure time - start
                auto start = std::chrono::high_resolution_clock::now();
                for (size_t j = 0; j < buffer.size(); j += stepSize)
                {
                    buffer[j].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();
                // store the time difference between start and end
                const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                tempTimes.push_back(total);
            }
            // sort temp times
            std::ranges::sort(tempTimes);
            // remove first and last element
            tempTimes.pop_back();
            tempTimes.erase(tempTimes.begin());
            // calculate average
            long long sum = 0;
            for (const auto tempTime : tempTimes)
            {
                sum += tempTime;
            }
            times.push_back(static_cast<float>(sum) / static_cast<float>(tempTimes.size()));
        }
        data_alt_ = times;
    }
}
