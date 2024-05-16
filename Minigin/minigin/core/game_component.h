#pragma once

// Standard includes
#include <string>

namespace mngn
{
    // Forward declarations
    class game_object;

    enum class component_family
    {
        audio,
        collision,
        custom,
        physics,
        rendering,
        ui,
        test
    };
    
    class game_component
    {
        friend class game_object;
        
    public:
        game_component()          = default;
        virtual ~game_component() = default;

        game_component(game_component const &other)            = delete;
        game_component(game_component &&other)                 = delete;
        game_component &operator=(game_component const &other) = delete;
        game_component &operator=(game_component &&other)      = delete;

        virtual void awake()  { }
        virtual void start()  { }
        virtual void update() { }

        [[nodiscard]] virtual auto family() const -> component_family = 0;
        [[nodiscard]] auto owner() const -> game_object * { return owner_ptr_; }
        void set_enabled(bool enabled);
        [[nodiscard]] auto enabled() const -> bool { return enabled_; }
        
    private:
        void set_owner(game_object *owner_ptr);

    private:
        game_object *owner_ptr_ = nullptr;
        bool enabled_ = true;
        bool start_dirty_ = true;
    };
}
