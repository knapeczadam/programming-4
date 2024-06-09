#include "cube_component.h"

// Project includes
#include "component/character/position_component.h"
#include "component/player/score_counter_component.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    cube_component::cube_component(cube_component_config_info const &config_info)
        : row_idx_{config_info.row_idx}
        , col_idx_{config_info.col_idx}
        , score_count_{static_cast<int>(config_info.colors.size()) - 1}
        , revertible_{config_info.revertible}
        , colors_{config_info.colors}
        , animated_sprite_ptr_{config_info.animated_sprite_ptr}
    {
    }

    void cube_component::start()
    {
        owner()->component<mngn::sprite_component>()->set_sprite(colors_[current_color_]);
    }

    void cube_component::on_enable()
    {
        owner()->component<mngn::sprite_component>()->set_sprite(colors_[current_color_]);
    }

    void cube_component::on_disable()
    {
        current_color_ = 0;
        score_count_   = static_cast<int>(colors_.size()) - 1;
        disable_animation();
    }

    void cube_component::notify(std::string const &event, mngn::subject *subject_ptr)
    {
        if (event == "update_cube")
        {
            auto const position_comp_ptr = dynamic_cast<position_component*>(subject_ptr);
            if (position_comp_ptr->row() == row_idx_ and position_comp_ptr->col() == col_idx_)
            {
                if (position_comp_ptr->owner()->has_tag("player"))
                {
                    // only two colors
                    if (revertible_) // only two colors
                    {
                        current_color_ = (current_color_ + 1) % static_cast<int>(colors_.size());
                    }
                    // two or three colors
                    else if (current_color_ < static_cast<int>(colors_.size()) - 1)
                    {
                        ++current_color_;
                    }
                    if (score_count_ > 0)
                    {
                        --score_count_;
                        if (not position_comp_ptr->owner()->has_tag("ai"))
                        {
                            if (colors_.size() == 3)
                            {
                                if (score_count_ == 1)
                                {
                                    position_comp_ptr->owner()->component<score_counter_component>()->add_score(score_1_);
                                }
                                else if (score_count_ == 0)
                                {
                                    position_comp_ptr->owner()->component<score_counter_component>()->add_score(score_2_);
                                }
                            }
                            else if (colors_.size() == 2)
                            {
                                position_comp_ptr->owner()->component<score_counter_component>()->add_score(score_2_);
                            }
                        }
                    }
                }
                else if (position_comp_ptr->owner()->has_tag("friend"))
                {
                    if (current_color_ > 0)
                    {
                        --current_color_;
                    }
                }
                owner()->component<mngn::sprite_component>()->set_sprite(colors_[current_color_]);
                
                notify_observers("color_changed");
            }
        }
    }

    auto cube_component::has_final_color() const -> bool
    {
        return current_color_ == static_cast<int>(colors_.size()) - 1;
    }

    void cube_component::enable_animation()
    {
        owner()->component<mngn::sprite_component>()->set_sprite(animated_sprite_ptr_);
        owner()->component<mngn::sprite_component>()->set_animated(true);
    }

    void cube_component::disable_animation()
    {
        owner()->component<mngn::sprite_component>()->set_sprite(colors_[current_color_]);
        owner()->component<mngn::sprite_component>()->set_animated(false);
    }
}
