#pragma once

// Project includes
#include "minigin/component/text_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class score_text_component final : public mngn::text_component, public mngn::i_observer
    {
    public:
        score_text_component()           = default;
        ~score_text_component() override = default;

        score_text_component(score_text_component const &other)            = delete;
        score_text_component(score_text_component &&other)                 = delete;
        score_text_component &operator=(score_text_component const &other) = delete;
        score_text_component &operator=(score_text_component &&other)      = delete;

        void notify(std::string const &event, mngn::subject *subject_ptr) override;
    };
}
