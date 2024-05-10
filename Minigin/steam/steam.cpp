#include "steam.h"

// Project includes
#include "steam/achievement.h"

// Standard includes
#include <cassert>
#include <iostream>
#include <sstream>

// Steam includes
#pragma warning (push)
#pragma warning (disable: 4996)
#include "steam_api.h"
#pragma warning (pop)

namespace steam
{
    void init_steam()
    {
		if (not SteamAPI_Init())
		{
			std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << '\n';
			return;
		}
		std::cout << "Successfully initialized steam." << '\n';
		g_steam_achievements_ptr = new steam_achievements(g_achievements, 1);
    }

    void shutdown_steam()
    {
	    SteamAPI_Shutdown();
	    // Delete the SteamAchievements object
	    delete g_steam_achievements_ptr;
    }
}
