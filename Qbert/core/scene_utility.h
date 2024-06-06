#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <string>
#include <vector>

// Forward declarations
namespace mngn
{
    class collider_component;
    class scene;
    class game_object;
    class sprite_component;
    class sprite_ui_component;
}

namespace qbert
{
    // Forward declarations
    class jump_component;
    class spawn_component;
    class fall_component;
    class flicker_component;
    class player_collider_component;
    class game_state_component;
    
    class scene_utility final : public mngn::singleton<scene_utility> 
    {
    public:
        ~scene_utility() override = default;

        scene_utility(scene_utility const &other)            = delete;
        scene_utility(scene_utility &&other)                 = delete;
        scene_utility &operator=(scene_utility const &other) = delete;
        scene_utility &operator=(scene_utility &&other)      = delete;

        void freeze_all();
        void unfreeze_all();
        void freeze_animation();
        void unfreeze_animation();
        void freeze_npcs();
        void unfreeze_npcs();

        void hide_all();
        void show_all();
        void hide_npcs();
        void show_npcs();

        void trigger_root();
        void trigger_npcs();

        [[nodiscard]] auto current_scene() const -> mngn::scene *;
        [[nodiscard]] auto current_root() const -> mngn::game_object *;
        [[nodiscard]] auto scene_id() const -> std::string;

        [[nodiscard]] auto game_state() const -> game_state_component *;

    private:
        friend class mngn::singleton<scene_utility>;
        scene_utility() = default;

    private:
        struct current_scene
        {
            mngn::scene                             *scene_ptr;
            mngn::game_object                       *root_ptr;
            std::vector<jump_component*>            jump_comp_ptrs;
            std::vector<spawn_component*>           spawn_comp_ptrs;
            std::vector<fall_component*>            fall_comp_ptrs;
            std::vector<flicker_component*>         flicker_comp_ptrs;
            std::vector<mngn::sprite_component*>    sprite_comp_ptrs;
            std::vector<mngn::sprite_ui_component*> sprite_ui_comp_ptrs;
            std::vector<player_collider_component*> player_collider_comp_ptrs;
            std::vector<mngn::collider_component*>  collider_comp_ptrs;
        } current_scene_{};
    };
}
