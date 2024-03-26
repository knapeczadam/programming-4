#pragma once

namespace dae
{
    // Forward declarations
    class game_object;

    enum class component_family
    {
        audio,
        custom,
        physics,
        rendering,
        ui,
        test
    };
    
    class base_component
    {
        friend class game_object;
        
    public:
        base_component() = default;
        virtual ~base_component() = default;

        base_component(const base_component& other)            = delete;
        base_component(base_component&& other)                 = delete;
        base_component& operator=(const base_component& other) = delete;
        base_component& operator=(base_component&& other)      = delete;

        virtual void update() { }

        [[nodiscard]] virtual auto get_family() const -> component_family = 0;

        [[nodiscard]] auto get_owner() const -> game_object* { return owner_ptr_; }
        
    private:
        void set_owner(game_object* owner_ptr);
        
    private:
        game_object* owner_ptr_ = nullptr;
    };
}
