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
            std::stringstream ss;
            ss << "# lives: " << static_cast<HealthComponent*>(subject)->GetHealth();
            SetText(ss.str());
        }
    }
}
