#pragma once

// Project includes
#include "Singleton.h"

// Standard includes
#include <vector>

namespace dae
{
    struct TransformDummy
    {
        float matrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    };

    struct GameObject3D
    {
        TransformDummy transform{};
        int ID{1};
    };

    struct GameObject3DAlt
    {
        TransformDummy* transform{};
        int ID{1};
    };
    
    class TrashTheCacheManager final : public dae::Singleton<TrashTheCacheManager>
    {
    public:
        void CalculateData();
        void CalculateDataAlt();
        
        std::vector<float>& GetData() { return m_Data; }
        std::vector<float>& GetDataAlt() { return m_DataAlt; }

    private:
        friend class dae::Singleton<TrashTheCacheManager>;
        TrashTheCacheManager() = default;
        
        std::vector<float> m_Data;
        std::vector<float> m_DataAlt;

        const int m_sample = 20'000'000;
    };
}
