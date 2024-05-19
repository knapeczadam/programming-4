#pragma once

// Project includes
#include "minigin/utility/singleton.h"

namespace qbert
{
    class qbert_scene_manager final : public mngn::singleton<qbert_scene_manager>
    {
    public:
        ~qbert_scene_manager() override = default;

        qbert_scene_manager(qbert_scene_manager const& other)            = delete;
        qbert_scene_manager(qbert_scene_manager &&other)                 = delete;
        qbert_scene_manager &operator=(qbert_scene_manager const &other) = delete;
        qbert_scene_manager &operator=(qbert_scene_manager &&other)      = delete;

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
        
    private:
        friend class singleton<qbert_scene_manager>;
        qbert_scene_manager() = default;
    };
}