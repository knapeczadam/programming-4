#pragma once

// Project includes
#include "i_observer.h"

// Steam includes
#pragma warning (push)
#pragma warning (disable: 4996)
#include "steam_api.h"
#pragma warning (pop)

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

namespace dae
{
    struct Achievement_t
    {
        int m_eAchievementID;
        const char* m_pchAchievementID;
        char m_rgchName[128];
        char m_rgchDescription[256];
        bool m_bAchieved;
        int m_iIconImage;
    };

    class CSteamAchievements : public i_observer
    {
    private:
        int64 m_iAppID; // Our current AppID
        Achievement_t* m_pAchievements; // Achievements data
        int m_iNumAchievements; // The number of Achievements
        bool m_bInitialized; // Have we called Request stats and received the callback?

    public:
        CSteamAchievements(Achievement_t* Achievements, int NumAchievements);
        ~CSteamAchievements() = default;

        bool RequestStats();
        bool SetAchievement(const char* ID);
        void ResetAchievements();

        STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
        STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
        STEAM_CALLBACK(CSteamAchievements, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);

        void notify(const std::string& event, subject* subject) override;
    };

    // Defining our achievements
    enum EAchievements
    {
        ACH_WIN_ONE_GAME = 0,
        ACH_WIN_100_GAMES = 1,
        ACH_TRAVEL_FAR_ACCUM = 2,
        ACH_TRAVEL_FAR_SINGLE = 3,
    };

    // Achievement array which will hold data about the achievements and their state
    inline Achievement_t g_Achievements[] =
    {
        _ACH_ID(ACH_WIN_ONE_GAME, "Winner")
    };

    // Global access to Achievements object
    inline CSteamAchievements* g_steam_achievements = NULL;
}
