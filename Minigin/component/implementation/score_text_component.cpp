#include "score_text_component.h"

// Project includes
#include "score_component.h"

// Standard includes
#include <sstream>

namespace dae
{
    void score_text_component::notify(std::string const &event, subject *subject_ptr)
    {
        if (event == "ScoreChanged")
        {
            if (auto const score_comp = dynamic_cast<score_component*>(subject_ptr))
            {
                std::stringstream ss;
                ss << "Score: " << score_comp->get_score();
                set_text(ss.str());
            }
        }
    }
}
