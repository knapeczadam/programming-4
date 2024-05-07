#include "achievement.h"

// Windows includes
#include <windows.h>

namespace steam
{
    steam_achievements::steam_achievements(achievement_t *achievements_ptr, int num_achievements):
        app_id_{0},
        initialized_{false},
        m_CallbackUserStatsReceived{this, &steam_achievements::OnUserStatsReceived},
        m_CallbackUserStatsStored{this, &steam_achievements::OnUserStatsStored},
        m_CallbackAchievementStored{this, &steam_achievements::OnAchievementStored}
    {
        app_id_ = SteamUtils()->GetAppID();
        achievements_ptr_ = achievements_ptr;
        num_achievements_ = num_achievements;
        request_stats();
    }

    auto steam_achievements::request_stats() -> bool
    {
        // Is Steam loaded? If not we can't get stats.
        if (NULL == SteamUserStats() or NULL == SteamUser())
        {
            return false;
        }
        // Is the user logged on?  If not we can't get stats.
        if (not SteamUser()->BLoggedOn())
        {
            return false;
        }
        // Request user stats.
        return SteamUserStats()->RequestCurrentStats();
    }

    auto steam_achievements::set_achievement(char const *id) -> bool
    {
        // Have we received a call back from Steam yet?
        if (initialized_)
        {
            SteamUserStats()->SetAchievement(id);
            return SteamUserStats()->StoreStats();
        }
        // If not then we can't set achievements yet
        return false;
    }

    void steam_achievements::reset_achievements()
    {
        if (SteamUserStats()->ResetAllStats(true))
        {
            OutputDebugString("Successfully reset all stats and achievements\n");
        }
        else
        {
            OutputDebugString("Failed to reset stats and achievements\n");
        }
    }

    void steam_achievements::OnUserStatsReceived(UserStatsReceived_t *callback_ptr)
    {
        // we may get callbacks for other games' stats arriving, ignore them
#pragma warning(disable: 4389)
        if (app_id_ == callback_ptr->m_nGameID)
#pragma warning(default: 4389)
        {
            if (k_EResultOK == callback_ptr->m_eResult)
            {
                OutputDebugString("Received stats and achievements from Steam\n");
                initialized_ = true;

                // load achievements
                for (int i_ach = 0; i_ach < num_achievements_; ++i_ach)
                {
                    achievement_t &ach = achievements_ptr_[i_ach];

                    SteamUserStats()->GetAchievement(ach.achievement_name, &ach.achieved);
                    _snprintf_s(ach.name, sizeof(ach.name), "%s", SteamUserStats()->GetAchievementDisplayAttribute(ach.achievement_name, "name"));
                    _snprintf_s(ach.description, sizeof(ach.description), "%s", SteamUserStats()->GetAchievementDisplayAttribute(ach.achievement_name, "desc"));
                }
            }
            else
            {
                char buffer[128];
                _snprintf_s(buffer, 128, "RequestStats - failed, %d\n", callback_ptr->m_eResult);
                OutputDebugString(buffer);
            }
        }
    }

    void steam_achievements::OnUserStatsStored(UserStatsStored_t *callback_ptr)
    {
        // we may get callbacks for other games' stats arriving, ignore them
#pragma warning(disable: 4389)
        if (app_id_ == callback_ptr->m_nGameID)
#pragma warning(default: 4389)
        {
            if (k_EResultOK == callback_ptr->m_eResult)
            {
                OutputDebugString("Stored stats for Steam\n");
            }
            else
            {
                char buffer[128];
                _snprintf_s(buffer, 128, "StatsStored - failed, %d\n", callback_ptr->m_eResult);
                OutputDebugString(buffer);
            }
        }
    }

    void steam_achievements::OnAchievementStored(UserAchievementStored_t *callback_ptr)
    {
        // we may get callbacks for other games' stats arriving, ignore them
#pragma warning(disable: 4389)
        if (app_id_ == callback_ptr->m_nGameID)
#pragma warning(default: 4389)
        {
            OutputDebugString("Stored Achievement for Steam\n");
        }
    }

    void steam_achievements::notify(std::string const &event, [[maybe_unused]] mngn::subject *subject_ptr)
    {
        if (event == "AchievementUnlocked")
            set_achievement("ACH_WIN_ONE_GAME");
    }
}
