#include "health_text_component.h"

// Project includes
#include "health_component.h"

// Standard includes
#include <sstream>

namespace qbert
{
    void health_text_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "health_changed")
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
