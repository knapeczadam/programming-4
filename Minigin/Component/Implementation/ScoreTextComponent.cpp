#include "ScoreTextComponent.h"

// Project includes
#include "ScoreComponent.h"

// Standard includes
#include <sstream>

namespace dae
{
    void ScoreTextComponent::Notify(const std::string& event, Subject* subject)
    {
        if (event == "ScoreChanged")
        {
            std::stringstream ss;
            ss << "Score: " << static_cast<ScoreComponent*>(subject)->GetScore();
            SetText(ss.str());
        }
    }
}
