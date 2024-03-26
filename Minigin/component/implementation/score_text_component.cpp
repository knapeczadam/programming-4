#include "score_text_component.h"

// Project includes
#include "score_component.h"

// Standard includes
#include <sstream>

namespace dae
{
    void score_text_component::notify(const std::string& event, subject* subject)
    {
        if (event == "ScoreChanged")
        {
            std::stringstream ss;
            ss << "Score: " << static_cast<score_component*>(subject)->get_score();
            set_text(ss.str());
        }
    }
}
