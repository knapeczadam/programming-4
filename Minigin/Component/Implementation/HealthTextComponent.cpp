#include "HealthTextComponent.h"

// Project includes
#include "HealthComponent.h"

// Standard includes
#include <sstream>

namespace dae
{
    void HealthTextComponent::Notify(const std::string& event, Subject* subject)
    {
        if (event == "HealthChanged")
        {
            const auto healthComp = static_cast<HealthComponent*>(subject);
            
            std::stringstream ss;
            ss << "# lives: " << healthComp->GetHealth();
            SetText(ss.str());
        }
    }
}
