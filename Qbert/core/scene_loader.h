#pragma once

// Project includes
#include "core/factory.h"
#include "minigin/utility/singleton.h"

// Forward declarations
namespace mngn
{
    class game_object;
    class scene;
}

namespace qbert
{
    // Forward declarations
    class level_manager_component;
    
    class scene_loader final : public mngn::singleton<scene_loader>
    {
        struct scene_info
        {
            mngn::scene                         *scene_ptr;
            mngn::game_object                   *root_ptr;
            level_manager_component             *level_manager_comp_ptr;
            factory::ui::score_display_info     score_display_info;
            factory::ui::health_display_info    health_display_info;
            factory::ui::level_display_info     level_display_info;
            factory::ui::round_display_info     round_display_info;
            factory::level::level_info          level_info;
            factory::character::player_info     player_info;
            factory::character::red_ball_info   red_ball_info;
            factory::character::coily_info      coily_info;
            factory::character::ugg_info        ugg_info;
            factory::character::wrong_way_info  wrong_way_info;
            factory::character::green_ball_info green_ball_info;
            factory::character::slick_info      slick_info;
            factory::character::sam_info        sam_info;
        };
        
    public:
        ~scene_loader() override = default;

        scene_loader(scene_loader const& other)            = delete;
        scene_loader(scene_loader &&other)                 = delete;
        scene_loader &operator=(scene_loader const &other) = delete;
        scene_loader &operator=(scene_loader &&other)      = delete;

        void load_scenes();

    private:
        void load_debug_scene();
        void load_game_state_scene();
        void load_menu_scene();
        void load_loading_scene();
        void load_solo_scene();
        void load_duo_scene();
        void load_versus_scene();
        void load_game_over_scene();
        void load_scoreboard_scene();

        void create_score_display(scene_info &scene_info);
        void create_health_display(scene_info &scene_info);
        void create_level_display(scene_info &scene_info);
        void create_round_display(scene_info &scene_info);
        void create_level(scene_info &scene_info);
        void create_player_1(scene_info &scene_info);
        void create_player_2(scene_info &scene_info);
        void create_red_ball(scene_info &scene_info);
        void create_coily(scene_info &scene_info);
        void create_ugg(scene_info &scene_info);
        void create_wrong_way(scene_info &scene_info);
        void create_green_ball(scene_info &scene_info);
        void create_slick(scene_info &scene_info);
        void create_sam(scene_info &scene_info);
        void create_ui(scene_info &scene_info);
        void create_scoreboard();
        
        void bind_player_observers(scene_info &scene_info);

    private:
        friend class singleton<scene_loader>;
        scene_loader() = default;
    };
}