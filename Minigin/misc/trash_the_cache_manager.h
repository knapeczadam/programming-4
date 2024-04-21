#pragma once

// Project includes
#include "utility/singleton.h"

// Standard includes
#include <vector>

namespace dae
{
    struct transform_dummy
    {
        float matrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    };

    struct game_object_3d
    {
        transform_dummy transform{};
        int id = 1;
    };

    struct game_object_3d_alt
    {
        transform_dummy *transform_ptr = nullptr;
        int id = 1;
    };
    
    class trash_the_cache_manager final : public singleton<trash_the_cache_manager>
    {
    public:
        void calculate_data();
        void calculate_data_alt();

        auto get_data() -> std::vector<float> & { return data_; }
        auto get_data_alt() -> std::vector<float> & { return data_alt_; }

    private:
        friend class singleton<trash_the_cache_manager>;
        trash_the_cache_manager() = default;
        
        std::vector<float> data_;
        std::vector<float> data_alt_;

        const int sample_ = 20'000'000;
    };
}
