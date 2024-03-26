#include "HealthTextComponent.h"

// Project includes
#include "HealthComponent.h"

// Standard includes
#include <sstream>

namespace dae
{
    void health_text_component::notify(const std::string& event, subject* subject)
    {
        if (event == "HealthChanged")
        {
            const auto health_comp = static_cast<health_component*>(subject);
            
            std::stringstream ss;
            ss << "# lives: " << health_comp->get_health();
            set_text(ss.str());
        }
    }
}
