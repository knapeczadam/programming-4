#include <algorithm>
#include <atomic>
#include <chrono>
#include <execution>
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
std::atomic<int> in_atomic{0}, total_atomic{0};
// Mutex
int in_mutex{0}, total_mutex{0};
std::mutex mtx;

struct vector2f
{
    float x, y;
};

template <typename Func>
void measure_func(std::string const &name, Func f)
{
    std::cout << " --- Measuring " << name << " ---\n";
    std::vector<long long> measured_times;
    for (int i = 0; i < 10; ++i)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        f();
        auto end_time = std::chrono::high_resolution_clock::now();
        measured_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    }
    auto [min1, max1] = std::ranges::minmax_element(measured_times);
    auto const average = (std::accumulate(measured_times.begin(), measured_times.end(), 0LL) - (*min1 + *max1)) / (measured_times.size() - 2);
    std::cout << "Average time:\t" << average << "ms\n";
}

void print_pi(int in, int total)
{
    std::cout << "Pi accuracy:\t" << 1.f * in / total * 4 << "\n\n";
}

void print_pi(std::vector<float> const &pi_values)
{
    std::cout << "Pi accuracy:\t" << 1.f * std::accumulate(pi_values.begin(), pi_values.end(), 0.0f) / pi_values.size() <<"\n\n";
}

vector2f get_random_point()
{
    thread_local std::random_device rd;
    thread_local std::default_random_engine eng(rd());
    thread_local std::uniform_real_distribution<float> distr(-1, 1);
    return {distr(eng), distr(eng)};
}

void count_points(int num_of_points)
{
    total_seq += num_of_points;
    for (int i{}; i < num_of_points; ++i)
    {
        const auto point{get_random_point()};
        if (point.x * point.x + point.y * point.y < 1.f)
        {
            ++in_seq;
        }
    }
}

void count_points_atomic(int number_of_points)
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
    in_atomic += in;
    total_atomic += number_of_points;
}

void count_points_mutex(int number_of_points)
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
    in_mutex += in;
    total_mutex += number_of_points;
}

void count_points_future_promise(int num_of_points, std::promise<int> promise)
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
    promise.set_value(in);
}

int count_points_future_async(int num_of_points)
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

int main()
{
    // const int num_threads = std::thread::hardware_concurrency();
    constexpr int num_threads = 10;
    constexpr int total_points = 100'000'000;
    const int points_per_thread = total_points / num_threads;

    std::cout << "# Number of threads:\t" << num_threads << '\n';
    std::cout << "# Samples:\t\t" << total_points << "\n\n";

    //--------------------------------------------------------------------------------
    // Original
    //--------------------------------------------------------------------------------
    measure_func("original", []() { count_points(total_points); });
    print_pi(in_seq, total_seq);
    
    //--------------------------------------------------------------------------------
    // Atomic
    //--------------------------------------------------------------------------------
    {
        measure_func("atomic", [&]()
        {
            std::vector<std::jthread> threads(num_threads);
            for (int j = 0; j < num_threads; ++j)
            {
                threads.emplace_back(count_points_atomic, points_per_thread);
            }
        });
        print_pi(in_atomic, total_atomic);
    }
    
    //--------------------------------------------------------------------------------
    // Mutex
    //--------------------------------------------------------------------------------
    {
        measure_func("mutex", [&]()
        {
            std::vector<std::jthread> threads(num_threads);
            for (int j = 0; j < num_threads; ++j)
            {
                threads.emplace_back(count_points_mutex, points_per_thread);
            }
        });
        print_pi(in_mutex, total_mutex);
    }

    //--------------------------------------------------------------------------------
    // Future
    //--------------------------------------------------------------------------------
    {
        std::vector<float> pi_values;
        measure_func("future with promise", [&]()
        {
            std::vector<std::jthread> threads;
            std::vector<std::future<int>> futures;
            for (int i = 0; i < num_threads; ++i)
            {
                std::promise<int> promise;
                futures.emplace_back(promise.get_future());
                threads.emplace_back(count_points_future_promise, points_per_thread, std::move(promise));
            }
            int total_in_circle = 0;
            for (auto &future : futures)
            {
                total_in_circle += future.get();
            }
            pi_values.push_back(1.f * total_in_circle / total_points * 4);
            
        });
        print_pi(pi_values);
    }
    {
        std::vector<float> pi_values;
        measure_func("future with async", [&]()
        {
            std::vector<std::future<int>> futures;
            for (int i = 0; i < num_threads; ++i)
            {
                futures.push_back(std::async(std::launch::async, count_points_future_async, points_per_thread));
            }
            int total_in_circle = 0;
            for (auto &future : futures)
            {
                total_in_circle += future.get();
            }
            pi_values.push_back(1.f * total_in_circle / total_points * 4);
        });
        print_pi(pi_values);
    }
    
    //--------------------------------------------------------------------------------
    // STL
    //--------------------------------------------------------------------------------
    {
        std::vector<float> pi_values;
        measure_func("STL with sequenced policy", [&]()
        {
            std::vector<int> total_in_circles(num_threads);
            std::for_each(std::execution::seq, total_in_circles.begin(), total_in_circles.end(), [points_per_thread](int &sum)
            {
                sum = count_points_future_async(points_per_thread);
            });
            pi_values.push_back(1.f * std::accumulate(total_in_circles.begin(), total_in_circles.end(), 0) / total_points * 4);
        });
        print_pi(pi_values);
    }
    {
        std::vector<float> pi_values;
        measure_func("STL with parallel policy", [&]()
        {
            std::vector<int> total_in_circles(num_threads);
            std::for_each(std::execution::par, total_in_circles.begin(), total_in_circles.end(), [points_per_thread](int &sum)
            {
                sum = count_points_future_async(points_per_thread);
            });
            pi_values.push_back(1.f * std::accumulate(total_in_circles.begin(), total_in_circles.end(), 0) / total_points * 4);
        });
        print_pi(pi_values);
    }
    {
        std::vector<float> pi_values;
        measure_func("STL with parallel-unsequenced policy", [&]()
        {
            std::vector<int> total_in_circles(num_threads);
            std::for_each(std::execution::par_unseq, total_in_circles.begin(), total_in_circles.end(), [points_per_thread](int &sum)
            {
                sum = count_points_future_async(points_per_thread);
            });
            pi_values.push_back(1.f * std::accumulate(total_in_circles.begin(), total_in_circles.end(), 0) / total_points * 4);
        });
        print_pi(pi_values);
    }
    {
        std::vector<float> pi_values;
        measure_func("STL with unsequenced policy", [&]()
        {
            std::vector<int> total_in_circles(num_threads);
            std::for_each(std::execution::unseq, total_in_circles.begin(), total_in_circles.end(), [points_per_thread](int &sum)
            {
                sum = count_points_future_async(points_per_thread);
            });
            pi_values.push_back(1.f * std::accumulate(total_in_circles.begin(), total_in_circles.end(), 0) / total_points * 4);
        });
        print_pi(pi_values);
    }
}
