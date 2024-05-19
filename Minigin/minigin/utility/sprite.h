#pragma once

// GLM includes
#include <glm/glm.hpp>

namespace mngn
{
    struct rect
    {
        int width  = 0;
        int height = 0;
        int left   = 0;
        int bottom = 0;
    };
    
    // Forward declarations
    class texture;

    class sprite final
    {
    public:
        sprite() = default;
        explicit sprite(mngn::texture *texture_ptr);  
        ~sprite() = default;
    
        sprite(const sprite &other)            = delete;
        sprite(sprite &&other)                 = delete;
        sprite &operator=(const sprite &other) = delete;
        sprite &operator=(sprite &&other)      = delete;

        void init();
        void init_grid_size();
        void init_clip_size();
        void init_src_rect();
        void init_dst_rect();
        void init_curr_rows_cols();
        void calculate_frame_time();
    
        void update(float elapsed_sec);
        void update_src_rect();
    
        void reset_curr_frame();
        void reset_iter_count();

        void set_rows(int rows);
        void set_cols(int cols);
        void set_sub_rows(int sub_rows);
        void set_sub_cols(int sub_cols);
        void set_left_offset_px(int left);
        void set_left_offset_cols(int left);
        void set_top_offset_px(int top);
        void set_top_offset_rows(int top);
        void set_collider_width(float collider_width);
        void set_collider_height(float collider_height);
        void set_collider_horizontal_offset(float collider_horizontal_offset);
        void set_collider_vertical_offset(float collider_vertical_offset);
        void set_frames_per_sec(float frames_per_sec);
        void set_scale(float scale);
        void set_clip_width(int clip_width);
        void set_clip_height(int clip_height);
        
        void set_position(const glm::ivec2 & pos);
        void set_current_frame(int frame);
        
        [[nodiscard]] auto src_rect() const -> rect;
        [[nodiscard]] auto dst_rect() const -> rect;
        [[nodiscard]] auto texture() const -> texture *;
        [[nodiscard]] auto texture_width() const -> int;
        [[nodiscard]] auto texture_height() const -> int;
        [[nodiscard]] auto collider_width() const -> float;
        [[nodiscard]] auto collider_height() const -> float;
        [[nodiscard]] auto collider_horizontal_offset() const -> float;
        [[nodiscard]] auto collider_vertical_offset() const -> float;
        [[nodiscard]] auto scaled_clip_width() const -> float;
        [[nodiscard]] auto scaled_clip_height() const -> float;
        [[nodiscard]] auto position() const -> glm::ivec2;
        [[nodiscard]] auto iter_count() const -> int;
        
        [[nodiscard]] auto is_last_frame() const -> bool;

    private:
        // SPRITE PROPERTIES
        mngn::texture *texture_ptr_     = nullptr;
        int     left_offset_px_   = 0;
        int     top_offset_px_    = 0;
        int     left_offset_cols_ = 0;
        int     top_offset_rows_  = 0;
        int     width_            = 0;
        int     height_           = 0;
        int     rows_             = 1;
        int     cols_             = 1;
        int     sub_rows_         = 0;
        int     sub_cols_         = 0;
        int     curr_rows_        = 0;
        int     curr_cols_        = 0;
        float   frames_per_sec_   = 0.0f;
        float   frame_time_       = 0.0f;
        float   scale_            = 1.0f;

        // SPRITE RELATED DATA MEMBERS
        float accu_time_                  = 0.0f;
        int   curr_frame_                 = 0;
        rect  src_rect_                   = {};
        rect  dst_rect_                   = {};
        int   clip_width_                 = 0;
        int   clip_height_                = 0;
        int   grid_width_                 = 0;
        int   grid_height_                = 0;
        float collider_width_             = 0.0f;
        float collider_height_            = 0.0f;
        float collider_horizontal_offset_ = 0.0f;
        float collider_vertical_offset_   = 0.0f;
        int   iter_count_                 = 0;
        bool  animated_                   = false;
    };
}
