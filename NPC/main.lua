addNPC("Merchant")
removeNPC("Merchant")

-- Wrappers for NPC functions
function add_npc(name)
    -- Do something with name
    addNPC(name)
end

function remove_npc(name)
    -- Do something with name
    removeNPC(name)
end

setHealth("Tom", 10)
setHealth("Yosha", 20)
setHealth("KillBot2000", 30)
setHealth("Alex", 40)
setHealth("Alex", -10)

-- Alternative way
--npc1 = { name = "Tom",         health = 50 }
--npc2 = { name = "Yosha",       health = 60 }
--npc3 = { name = "KillBot2000", health = 70 }
--npc4 = { name = "Alex",        health = 80 }
