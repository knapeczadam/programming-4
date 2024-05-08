#pragma once

namespace qbert
{
    enum class resource
    {
        e_qbert_fall,
        e_qbert_jump,
        
        s_01_credit
    };
    void init_resources();
    auto to_int(resource id) -> int;
}
