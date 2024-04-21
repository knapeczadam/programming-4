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
        int step_size = 1;

        // vector for storing time
        std::vector<float> times;

        for (step_size = 1; step_size <= 1024; step_size *= 2)
        {
            std::vector<long long> temp_times;
            for (int i = 0; i < 10; ++i)
            {
                // measure time - start
                auto start = std::chrono::high_resolution_clock::now();
                for (size_t j = 0; j < buffer.size(); j += step_size)
                {
                    buffer[j].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();
                // store the time difference between start and end
                auto const total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                temp_times.push_back(total);
            }
            
            // 3 liners
            // min-max
            // delete min and max
            // average

            
            // sort temp times
            std::ranges::sort(temp_times);
            // remove first and last element
            temp_times.pop_back();
            temp_times.erase(temp_times.begin());
            // calculate average
            long long sum = 0;
            for (auto const temp_time : temp_times)
            {
                sum += temp_time;
            }
            times.push_back(static_cast<float>(sum) / static_cast<float>(temp_times.size()));
        }
        data_ = times;
    }

    void trash_the_cache_manager::calculate_data_alt()
    {
        std::vector<game_object_3d_alt> buffer(sample_);
        int step_size = 1;

        // vector for storing time
        std::vector<float> times;

        for (step_size = 1; step_size <= 1024; step_size *= 2)
        {
            std::vector<long long> temp_times;
            for (int i = 0; i < 10; ++i)
            {
                // measure time - start
                auto start = std::chrono::high_resolution_clock::now();
                for (size_t j = 0; j < buffer.size(); j += step_size)
                {
                    buffer[j].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();
                // store the time difference between start and end
                auto const total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                temp_times.push_back(total);
            }
            // sort temp times
            std::ranges::sort(temp_times);
            // remove first and last element
            temp_times.pop_back();
            temp_times.erase(temp_times.begin());
            // calculate average
            long long sum = 0;
            for (auto const temp_time : temp_times)
            {
                sum += temp_time;
            }
            times.push_back(static_cast<float>(sum) / static_cast<float>(temp_times.size()));
        }
        data_alt_ = times;
    }
}
