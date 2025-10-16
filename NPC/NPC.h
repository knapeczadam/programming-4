#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class NPC
{
    std::string m_name;
    int m_health;

public:
    explicit NPC(std::string name) : m_name(std::move(name)), m_health{0}
    {
    }

    [[nodiscard]] auto get_name() const -> std::string const & { return m_name; }
    [[nodiscard]] auto get_health() const -> uint32_t { return m_health; }

    void set_health(int health)
    {
        if (health < 0)
        {
            std::cout << "Health cannot be negative" << '\n';
            return;
        }
        m_health = health;
    }
};

class NPCManager
{
    std::vector<NPC> m_npcs;

public:
    static NPCManager &GetInstance()
    {
        static NPCManager instance{};
        return instance;
    }

    void AddNPC(const std::string &&name)
    {
        m_npcs.emplace_back(NPC(name));
    }

    void RemoveNPC(const std::string &name)
    {
        m_npcs.erase(std::ranges::remove_if(m_npcs, [name](NPC &npc) { return npc.get_name() == name; }).begin(), m_npcs.end());
    }

    void SetHealth(const std::string &name, int health)
    {
        auto npc = std::ranges::find_if(m_npcs, [name](const NPC &npc) { return npc.get_name() == name; });
        if (npc != m_npcs.end())
        {
            npc->set_health(health);
        }
    }

    void Dump() const
    {
        std::cout << "Available NPC's:" << '\n';
        for (const auto &npc : m_npcs)
            std::cout << "NPC " << npc.get_name() << " has " << npc.get_health() << " health" << '\n';
        std::cout << "NPC count:" << m_npcs.size() << '\n';
    }
};
