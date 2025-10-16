#include <algorithm>
#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <ranges>
#include <thread>
#include <vector>

// Sequential
int in_seq{0}, total_seq{0};
// Atomic
std::atomic<int> in_atomic_1{0}, total_atomic_1{0};
std::atomic<int> in_atomic_2{0}, total_atomic_2{0};
// Mutex
int in_mutex_1{0}, total_mutex_1{0};
int in_mutex_2{0}, total_mutex_2{0};
std::mutex mtx;

struct vector2f
{
    float x, y;
};

vector2f get_random_point()
{
    thread_local std::random_device rd;
    thread_local std::default_random_engine eng(rd());
    thread_local std::uniform_real_distribution<float> distr(-1, 1);
    return {distr(eng), distr(eng)};
}

void count_points_atomic_1(int number_of_points);
void count_points_atomic_2(int start, int end);

void count_points_mutex_1(int number_of_points);
void count_points_mutex_2(int start, int end);

int count_points_future_1(int num_of_points);
int count_points_future_2(int start, int end);

void count_points(int number)
{
    total_seq += number;
    for (int i{}; i < number; ++i)
    {
        const auto point{get_random_point()};
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in_seq;
        }
    }
}

void count_points_atomic_1(int number_of_points)
{
    int in = 0;
    for (int i = 0; i < number_of_points; ++i)
    {
        const auto point = get_random_point();
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in;
        }
    }
    in_atomic_1 += in;
    total_atomic_1 += number_of_points;
}

void count_points_atomic_2(int start, int end)
{
    int in = 0;
    for (int i = start; i < end; ++i)
    {
        const auto point = get_random_point();
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in;
        }
    }
    in_atomic_2 += in;
    total_atomic_2 += end - start;
}

void count_points_mutex_1(int number_of_points)
{
    int in = 0;
    for (int i = 0; i < number_of_points; ++i)
    {
        const auto point = get_random_point();
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in;
        }
    }
    std::lock_guard lock(mtx);
    in_mutex_1 += in;
    total_mutex_1 += number_of_points;
}

void count_points_mutex_2(int start, int end)
{
    int in = 0;
    for (int i = start; i < end; ++i)
    {
        const auto point = get_random_point();
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in;
        }
    }
    std::lock_guard lock(mtx);
    in_mutex_2 += in;
    total_mutex_2 += end - start;
}

int count_points_future_1(int num_of_points)
{
    int in = 0;
    for (int i = 0; i < num_of_points; ++i)
    {
        const auto point = get_random_point();
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in;
        }
    }
    return in;
}

int count_points_future_2(int start, int end)
{
    int in = 0;
    for (int i = start; i < end; ++i)
    {
        const auto point = get_random_point();
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in;
        }
    }
    return in;
}

int main()
{
    std::vector<long long> measured_times;

    // const int numThreads = std::thread::hardware_concurrency();
    constexpr int num_threads = 10;
    constexpr int total_points = 100'000'000;
    constexpr int points_per_thread = total_points / num_threads;

    //--------------------------------------------------------------------------------
    // Sequential
    //--------------------------------------------------------------------------------
    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        count_points(total_points);
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min1, max1] = std::ranges::minmax_element(measured_times);
    auto average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min1 + *max1)) / (measured_times.size() - 2);
    std::cout << "Average time (sequence): " << average << "ms\n";
    std::cout << "Pi accuracy: " << 1.f * in_seq / total_seq * 4 << "\n";
    std::cout << "In: " << in_seq << " Total: " << total_seq << "\n\n";

    measured_times.clear();

    //--------------------------------------------------------------------------------
    // Atomic
    //--------------------------------------------------------------------------------
    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        {
            std::vector<std::jthread> threads(10);
            for (int j = 0; j < num_threads; ++j)
            {
                threads.emplace_back(count_points_atomic_1, points_per_thread);
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min2, max2] = std::ranges::minmax_element(measured_times);
    average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min2 + *max2)) / (measured_times.size() - 2);
    std::cout << "Average time (atomic) - number_of_points: " << average << "ms\n";
    std::cout << "Pi accuracy: " << 1.f * in_atomic_1 / total_atomic_1 * 4 << "\n";
    std::cout << "In: " << in_atomic_1 << " Total: " << total_atomic_1 << "\n\n";

    measured_times.clear();

    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        {
            std::vector<std::jthread> threads(10);
            for (int j = 0; j < num_threads; ++j)
            {
                int start = j * points_per_thread;
                int end = (j == num_threads - 1) ? total_points : (j + 1) * points_per_thread;
                threads.emplace_back(count_points_atomic_2, start, end);
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min3, max3] = std::ranges::minmax_element(measured_times);
    average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min3 + *max3)) / (measured_times.size() - 2);
    std::cout << "Average time (atomic) - start, end: " << average << "ms\n";
    std::cout << "Pi accuracy: " << 1.f * in_atomic_2 / total_atomic_2 * 4 << "\n";
    std::cout << "In: " << in_atomic_2 << " Total: " << total_atomic_2 << "\n\n";

    measured_times.clear();

    //--------------------------------------------------------------------------------
    // Mutex
    //--------------------------------------------------------------------------------
    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        {
            std::vector<std::jthread> threads(10);
            for (int j = 0; j < num_threads; ++j)
            {
                threads.emplace_back(count_points_mutex_1, points_per_thread);
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min4, max4] = std::ranges::minmax_element(measured_times);
    average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min4 + *max4)) / (measured_times.size() - 2);
    std::cout << "Average time (mutex) - number_of_points: " << average << "ms\n";
    std::cout << "Pi accuracy: " << 1.f * in_mutex_1 / total_mutex_1 * 4 << "\n";
    std::cout << "In: " << in_mutex_1 << " Total: " << total_mutex_1 << "\n\n";

    measured_times.clear();

    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        {
            std::vector<std::jthread> threads(10);
            for (int j = 0; j < num_threads; ++j)
            {
                int start = j * points_per_thread;
                int end = (j == num_threads - 1) ? total_points : (j + 1) * points_per_thread;
                threads.emplace_back(count_points_mutex_2, start, end);
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min5, max5] = std::ranges::minmax_element(measured_times);
    average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min5 + *max5)) / (measured_times.size() - 2);
    std::cout << "Average time (mutex) - start, end: " << average << "ms\n";
    std::cout << "Pi accuracy: " << 1.f * in_mutex_2 / total_mutex_2 * 4 << "\n";
    std::cout << "In: " << in_mutex_2 << " Total: " << total_mutex_2 << "\n\n";

    measured_times.clear();

    //--------------------------------------------------------------------------------
    // Future
    //--------------------------------------------------------------------------------
    std::vector<float> pi_values;
    int totalInCircle = 0;
    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        {
            std::vector<std::future<int>> futures;
            for (int j = 0; j < num_threads; ++j)
            {
                futures.push_back(std::async(std::launch::async, count_points_future_1, points_per_thread));
            }
            for (auto &future : futures)
            {
                totalInCircle += future.get();
            }
            pi_values.push_back(1.f * totalInCircle / total_points * 4);
            if (i != 9)
                totalInCircle = 0;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min6, max6] = std::ranges::minmax_element(measured_times);
    average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min6 + *max6)) / (measured_times.size() - 2);
    std::cout << "Average time (future) - int: " << average << "ms\n";
    std::cout << "Pi accuracy: " << 1.f * std::accumulate(pi_values.begin(), pi_values.end(), 0.f) / pi_values.size() << "\n";
    std::cout << "In: " << totalInCircle << " Total: " << total_points << "\n\n";

    measured_times.clear();
    pi_values.clear();
    totalInCircle = 0;

    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        {
            std::vector<std::future<int>> futures;
            for (int j = 0; j < num_threads; ++j)
            {
                int start = j * points_per_thread;
                int end = (j == num_threads - 1) ? total_points : (j + 1) * points_per_thread;
                futures.push_back(std::async(std::launch::async, count_points_future_2, start, end));
            }
            for (auto &future : futures)
            {
                totalInCircle += future.get();
            }
            pi_values.push_back(1.f * totalInCircle / total_points * 4);
            if (i != 9)
                totalInCircle = 0;
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min7, max7] = std::ranges::minmax_element(measured_times);
    average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min7 + *max7)) / (measured_times.size() - 2);
    std::cout << "Average time (future) - start, end: " << average << "ms\n";
    std::cout << "Pi accuracy: " << 1.f * std::accumulate(pi_values.begin(), pi_values.end(), 0.f) / pi_values.size() << "\n";
    std::cout << "In: " << totalInCircle << " Total: " << total_points << "\n";
}