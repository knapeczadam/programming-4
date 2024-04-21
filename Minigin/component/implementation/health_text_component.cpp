#include "health_text_component.h"

// Project includes
#include "health_component.h"

// Standard includes
#include <sstream>

namespace dae
{
    void health_text_component::notify(std::string const &event, subject *subject_ptr)
    {
        if (event == "HealthChanged")
        {
            if (auto const health_comp = dynamic_cast<health_component*>(subject_ptr))
            {
                std::stringstream ss;
                ss << "# lives: " << health_comp->get_health();
                set_text(ss.str());
            }
        }
    }
}
