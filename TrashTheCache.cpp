#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

struct Transform
{
    float matrix[16] = { 1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1 };
};

struct GameObject3D
{
    Transform transform{};
    int ID{1};
};

struct GameObject3DAlt
{
    Transform* transform{};
    int ID{1};
};

int main() {
    constexpr int count = 20'000'000;

    // --- Exercise 1 ---
    // std::vector<int> buffer(count, 1);

    // --- Exercise 2 ---
    // std::vector<GameObject3D> buffer(count);
    std::vector<GameObject3D> buffer(count);
    int stepSize = 1;

    // vector for storing time
    std::vector<double> times;

    for (stepSize = 1; stepSize <= 1024; stepSize *= 2) {
        std::vector<long long> tempTimes;
        for (int i = 0; i < 10; ++i) {

            // measure time - start
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t j = 0; j < buffer.size(); j += stepSize) {
                // --- Exercise 1 ---
                // buffer[j] *= 2;

                // --- Exercise 2 ---
                buffer[j].ID *= 2;
            }
            auto end = std::chrono::high_resolution_clock::now();
            // measure time - end

            const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            tempTimes.push_back(total);
        }
        const auto [min, max] = std::ranges::minmax_element(tempTimes);
        const auto sum = std::accumulate(tempTimes.begin(), tempTimes.end(), 0LL) - *min - *max;
        times.push_back(static_cast<double>(sum) / (static_cast<int>(tempTimes.size()) - 2));
    }
    
    // std::ranges::for_each(times, [](const double time) { std::cout << time << '\n'; });
    std::ranges::copy(times, std::ostream_iterator<double>(std::cout, "\n"));
}