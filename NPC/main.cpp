// Project includes
#include "NPC.h"

// Standard includes
#include <string>
#include <iostream>

// LUA includes
extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

auto check_lua(lua_State *L, int r) -> bool
{
    if (r != LUA_OK)
    {
        std::cerr << "Error: " << lua_tostring(L, -1) << '\n';
        return false;
    }
    return true;
}

int lua_add_npc(lua_State *L)
{
    auto name = lua_tostring(L, 1);
    std::cout << "Adding NPC: " << name << '\n';
    NPCManager::GetInstance().AddNPC(name);
    return 0;
}

int lua_remove_npc(lua_State *L)
{
    auto name = lua_tostring(L, 1);
    std::cout << "Removing NPC: " << name << '\n';
    NPCManager::GetInstance().RemoveNPC(name);
    return 0;
}

int lua_set_health(lua_State *L)
{
    auto name = lua_tostring(L, 1);
    auto health = lua_tonumber(L, 2);
    std::cout << "Setting health of " << name << " to " << health << '\n';
    NPCManager::GetInstance().SetHealth(name, static_cast<int>(health));
    return 0;
}

void load_npc_health(lua_State *L, std::string const &npc)
{
    lua_getglobal(L, npc.c_str());
    if (lua_istable(L, -1))
    {
        lua_getfield(L, -1, "name");
        auto name = lua_tostring(L, -1);
        lua_getfield(L, -2, "health");
        auto health = lua_tonumber(L, -1);
        NPCManager::GetInstance().SetHealth(name, (int)health);
    }
}

int main()
{
    auto L = luaL_newstate();
    if (L == nullptr)
    {
        return 1;
    }

    luaL_openlibs(L);
    
    lua_register(L, "addNPC", lua_add_npc);
    lua_register(L, "removeNPC", lua_remove_npc);
    lua_register(L, "setHealth", lua_set_health);

    if (check_lua(L, luaL_dofile(L, "startup.lub")))
    {
        std::cout << "startup.lub loaded" << '\n';
    }

    if (check_lua(L, luaL_dofile(L, "main.lua")))
    {
        // Calling lua functions from the C++ side
        lua_getglobal(L, "add_npc");
        if (lua_isfunction(L, -1))
        {
            lua_pushstring(L, "Adam");
            if (not check_lua(L, lua_pcall(L, 1, 0, 0)))
            {
                std::cerr << "Error calling add_npc" << '\n';
            }
        }
        
        lua_getglobal(L, "remove_npc");
        if (lua_isfunction(L, -1))
        {
            lua_pushstring(L, "Adam");
            if (not check_lua(L, lua_pcall(L, 1, 0, 0)))
            {
                std::cerr << "Error calling remove_npc" << '\n';
            }
        }

        // Alternative way
        // load_npc_health(L, "npc1");
        // load_npc_health(L, "npc2");
        // load_npc_health(L, "npc3");
        // load_npc_health(L, "npc4");
    }
    
    NPCManager::GetInstance().Dump();
    lua_close(L);
}
