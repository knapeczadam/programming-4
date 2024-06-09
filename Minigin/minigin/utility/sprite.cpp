#include "sprite.h"

// Project includes
#include "minigin/utility/texture.h"

namespace mngn
{
    sprite::sprite(mngn::texture* texture_ptr)
        : texture_ptr_{texture_ptr}
        , width_{texture_ptr_->width()}
        , height_{texture_ptr_->height()}
    {
    }

    void sprite::init()
    {
        calculate_frame_time();
        init_curr_rows_cols();
        init_grid_size();
        init_clip_size();
        init_src_rect();
        init_dst_rect();
    }

    void sprite::init_grid_size()
    {
        grid_width_  = width_ / cols_;
        grid_height_ = height_ / rows_;
    }

    void sprite::init_clip_size()
    {
        clip_width_  = clip_width_ == 0 ? grid_width_ : clip_width_;
        clip_height_ = clip_height_  == 0 ? grid_height_ : clip_height_;
    }

    void sprite::init_src_rect()
    {
        src_rect_.width  = clip_width_;
        src_rect_.height = clip_height_;
        update_src_rect();
    }

    void sprite::init_dst_rect()
    {
        dst_rect_.width  = static_cast<int>(src_rect_.width * scale_);
        dst_rect_.height = static_cast<int>(src_rect_.height * scale_);
    }

    void sprite::init_curr_rows_cols()
    {
        curr_rows_ = sub_rows_ == 0 ? rows_ : sub_rows_;
        curr_cols_ = sub_cols_ == 0 ? cols_ : sub_cols_;
    }

    void sprite::calculate_frame_time()
    {
        if (frames_per_sec_ != 0.0f)
        {
            frame_time_ = 1.0f / frames_per_sec_;
            animated_ = true;
        }
    }

    void sprite::update(float elapsed_sec)
    {
        if (animated_)
        {
            accu_time_ += elapsed_sec;
            if (accu_time_ > frame_time_)
            {
                ++curr_frame_ %= (curr_rows_ * curr_cols_);
                if (curr_frame_ == 0)
                {
                    ++iter_count_;
                }
                accu_time_ -= frame_time_;
                update_src_rect();
            }
        }
    }

    void sprite::update_src_rect()
    {
        src_rect_.left   = left_offset_px_ + left_offset_cols_ * grid_width_  + curr_frame_  % curr_cols_  * clip_width_;
        src_rect_.bottom = top_offset_px_  + top_offset_rows_  * grid_height_ + (curr_frame_ / curr_cols_) * clip_height_;
    }

    void sprite::reset_curr_frame()
    {
        curr_frame_ = 0;
    }

    void sprite::reset_iter_count()
    {
        iter_count_ = 0;
    }

    //---------------------------------------------------------------------------------
    
    void sprite::set_rows(int rows)
    {
        rows_ = rows;
    }

    void sprite::set_cols(int cols)
    {
        cols_ = cols;
    }

    void sprite::set_sub_rows(int sub_rows)
    {
        sub_rows_ = sub_rows;
    }

    void sprite::set_sub_cols(int sub_cols)
    {
        sub_cols_ = sub_cols;
    }
    
    void sprite::set_left_offset_px(int left)
    {
        left_offset_px_ = left;
    }
    
    void sprite::set_left_offset_cols(int left)
    {
        left_offset_cols_ = left;
    }
    
    void sprite::set_top_offset_px(int top)
    {
        top_offset_px_ = top;
    }

    void sprite::set_top_offset_rows(int top)
    {
        top_offset_rows_ = top;
    }

    void sprite::set_collider_width(float collider_width)
    {
        collider_width_ = collider_width;
    }

    void sprite::set_collider_height(float collider_height)
    {
        collider_height_ = collider_height;
    }

    void sprite::set_collider_offset_x(float collider_offset_x)
    {
        collider_offset_x_ = collider_offset_x;
    }

    void sprite::set_collider_offset_y(float collider_offset_y)
    {
        collider_offset_y_ = collider_offset_y;
    }

    void sprite::set_frames_per_sec(float frames_per_sec)
    {
        frames_per_sec_ = frames_per_sec;
    }

    void sprite::set_scale(float scale)
    {
        scale_ = scale;
    }

    void sprite::set_clip_width(int clip_width)
    {
        clip_width_ = clip_width;
    }

    void sprite::set_clip_height(int clip_height)
    {
        clip_height_ = clip_height;
    }
    void sprite::set_position(const glm::ivec2 &pos)
    {
        dst_rect_.left = pos.x;
        dst_rect_.bottom = pos.y;
    }

    void sprite::set_current_frame(int frame)
    {
        curr_frame_ = frame;
        update_src_rect();
    }

    //---------------------------------------------------------------------------------

    auto sprite::src_rect() const -> rect
    {
        return src_rect_;
    }

    auto sprite::dst_rect() const -> rect
    {
        return dst_rect_;
    }

    auto sprite::texture() const -> mngn::texture *
    {
        return texture_ptr_;
    }
    
    auto sprite::texture_width() const -> int
    {
        return width_;
    }

    auto sprite::texture_height() const -> int
    {
        return height_;
    }

    auto sprite::collider_width() const -> float
    {
        if (collider_width_ == 0.0f)
        {
            return static_cast<float>(clip_width_) * scale_;
        }
        return collider_width_ * scale_;
    }

    auto sprite::collider_height() const -> float
    {
        if (collider_height_ == 0.0f)
        {
            return static_cast<float>(clip_height_) * scale_;
        }
        return collider_height_ * scale_;
    }

    auto sprite::collider_offset_x() const -> float
    {
        return collider_offset_x_ * scale_;
    }

    auto sprite::collider_offset_y() const -> float
    {
        return collider_offset_y_ * scale_;
    }

    auto sprite::scaled_clip_width() const -> float
    {
        return static_cast<float>(clip_width_) * scale_;
    }

    auto sprite::scaled_clip_height() const -> float
    {
        return static_cast<float>(clip_height_) * scale_;
    }

    auto sprite::position() const -> glm::ivec2
    {
        glm::ivec2 pos;
        pos.x = dst_rect_.left;
        pos.y = dst_rect_.bottom;
        return pos;
    }

    auto sprite::iter_count() const -> int
    {
        return iter_count_;
    }

    auto sprite::is_last_frame() const -> bool
    {
        return curr_frame_ == curr_rows_ * curr_cols_ - 1;
    }

    auto sprite::animated() const -> bool
    {
        return animated_;
    }
}
