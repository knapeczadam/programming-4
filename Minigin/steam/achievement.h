#pragma once

// Project includes
#include "minigin/core/i_observer.h"

// Steam includes
#pragma warning (push)
#pragma warning (disable: 4996)
#include "steam_api.h"
#pragma warning (pop)

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

namespace steam
{
    struct achievement_t
    {
        int achievement_id;
        char const *achievement_name;
        char name[128];
        char description[256];
        bool achieved;
        int icon_image;
    };

    class steam_achievements final : public mngn::i_observer
    {
    public:
        steam_achievements(achievement_t *achievements_ptr, int num_achievements);
        ~steam_achievements() override = default;

        auto request_stats() -> bool;
        auto set_achievement(char const *id) -> bool;
        void reset_achievements();

        STEAM_CALLBACK(steam_achievements, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
        STEAM_CALLBACK(steam_achievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
        STEAM_CALLBACK(steam_achievements, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);

        void notify(std::string const &event, mngn::subject *subject_ptr) override;
        
    private:
        int64          app_id_;           // Our current AppID
        achievement_t *achievements_ptr_; // Achievements data
        int            num_achievements_; // The number of Achievements
        bool           initialized_;      // Have we walled Request stats and received the callback?

    };

    // Defining our achievements
    enum achievements
    {
        win_one_game      = 0,
        win_100_games     = 1,
        travel_far_accum  = 2,
        travel_far_single = 3,
    };

    // Achievement array which will hold data about the achievements and their state
    inline achievement_t g_achievements[] =
    {
        _ACH_ID(win_one_game, "Winner")
    };

    // Global access to Achievements object
    inline steam_achievements *g_steam_achievements_ptr = nullptr;
}
