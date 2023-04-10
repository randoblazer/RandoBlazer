#include "ItemPool.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;

// Static references
Item ItemPool::allItems[MAX_POOL_SIZE];
int ItemPool::allItemsCount;
ItemIndex ItemPool::itemIdMap[256];
ItemIndex ItemPool::npcIdMap[NPC_ID_MAX];

void logItem (const Item& item) {
    if (item.isNPC) {
        cout << "NPC " << (int)item.npcId << " ";
    } else {
        cout << "Item " << (int)item.itemId << " ";
    }
    cout << item.name << " ";
    if (item.isEquipment) {
        cout << "(Equipment) ";
    }
    if (item.isProgression) {
        cout << "(Progression) ";
    }
    if (item.isRequired) {
        cout << "(Required) ";
    }
    if (item.isUnique) {
        cout << "(Unique) ";
    }
    if (item.isConsumable) {
        cout << "(Consumable) ";
    }
    if (item.isExperience) {
        cout << "(" << item.ExpAmount << " Experience) ";
    }
    cout << endl;
}

ItemPool::ItemPool() {
    clear();
}
ItemPool::~ItemPool() {}

void ItemPool::logAllItems () {
    cout << allItemsCount << " items" << endl;
    for (int i = 0; i < allItemsCount; i++) {
        logItem(allItems[i]);
    }
}
void ItemPool::logList () {
    cout << "print item pool" << endl;
}

void ItemPool::populateItem (ItemIndex index, Item *flags, ItemId id, const char* name) {
    // cout << "populate item " << (int)index << " with " << name << endl;
    Item *dst = &allItems[(int)index];
    memcpy(dst, flags, sizeof(Item));
    dst->itemId = id;
    strcpy(dst->name, name);
    itemIdMap[(int)id] = index;
}
void ItemPool::populateNpc (ItemIndex index, Item *flags, NpcId id, const char* name) {
    // cout << "populate npc " << (int)index << " with " << name << endl;
    Item *dst = &allItems[(int)index];
    memcpy(dst, flags, sizeof(Item));
    dst->npcId = id;
    strcpy(dst->name, name);
    npcIdMap[(int)id] = index;
}

void resetFlags (Item &flags) {
    flags.isNPC = false;
    flags.isProgression = false;
    flags.isRequired = false;
    flags.isEquipment = false;
    flags.isUnique = false;
    flags.isConsumable = false;
    flags.isExperience = false;
}

void ItemPool::populate () {
    Item flags;
    allItemsCount = 0;

    resetFlags(flags);
    populateItem(ItemIndex::NOTHING, &flags, ItemId::NOTHING, "Nothing");

    resetFlags(flags);
    flags.isEquipment = true;
    flags.isUnique = true;
    populateItem(ItemIndex::SWORD_OF_LIFE, &flags, ItemId::SWORD_OF_LIFE, "Sword of Life");
    populateItem(ItemIndex::PSYCHO_SWORD, &flags, ItemId::PSYCHO_SWORD, "Psycho Sword");
    populateItem(ItemIndex::CRITICAL_SWORD, &flags, ItemId::CRITICAL_SWORD, "Critical Sword");
    populateItem(ItemIndex::RECOVERY_SWORD, &flags, ItemId::RECOVERY_SWORD, "Recovery Sword");
    populateItem(ItemIndex::IRON_ARMOR, &flags, ItemId::IRON_ARMOR, "Iron Armor");
    populateItem(ItemIndex::ICE_ARMOR, &flags, ItemId::ICE_ARMOR, "Ice Armor");
    populateItem(ItemIndex::MAGIC_ARMOR, &flags, ItemId::MAGIC_ARMOR, "Magic Armor");
    populateItem(ItemIndex::MYSTIC_ARMOR, &flags, ItemId::MYSTIC_ARMOR, "Mystic Armor");
    populateItem(ItemIndex::LIGHT_ARMOR, &flags, ItemId::LIGHT_ARMOR, "Light Armor");
    populateItem(ItemIndex::ELEMENTAL_MAIL, &flags, ItemId::ELEMENTAL_MAIL, "Elemental Mail");
    populateItem(ItemIndex::FLAME_BALL, &flags, ItemId::FLAME_BALL, "Flame Ball");
    populateItem(ItemIndex::LIGHT_ARROW, &flags, ItemId::LIGHT_ARROW, "Light Arrow");
    populateItem(ItemIndex::MAGIC_FLARE, &flags, ItemId::MAGIC_FLARE, "Magic Flare");
    populateItem(ItemIndex::ROTATOR, &flags, ItemId::ROTATOR, "Rotator");
    populateItem(ItemIndex::SPARK_BOMB, &flags, ItemId::SPARK_BOMB, "Spark Bomb");
    populateItem(ItemIndex::FLAME_PILLAR, &flags, ItemId::FLAME_PILLAR, "Flame Pillar");
    populateItem(ItemIndex::TORNADO, &flags, ItemId::TORNADO, "Tornado");
    populateItem(ItemIndex::POWER_BRACELET, &flags, ItemId::POWER_BRACELET, "Power Bracelet");
    populateItem(ItemIndex::SHIELD_BRACELET, &flags, ItemId::SHIELD_BRACELET, "Shield Bracelet");
    populateItem(ItemIndex::SUPER_BRACELET, &flags, ItemId::SUPER_BRACELET, "Super Bracelet");

    flags.isProgression = true;
    populateItem(ItemIndex::LUCKY_BLADE, &flags, ItemId::LUCKY_BLADE, "Lucky Blade");
    populateItem(ItemIndex::ZANTETSU_SWORD, &flags, ItemId::ZANTETSU_SWORD, "Zantetsu Sword");
    populateItem(ItemIndex::SPIRIT_SWORD, &flags, ItemId::SPIRIT_SWORD, "Spirit Sword");
    populateItem(ItemIndex::BUBBLE_ARMOR, &flags, ItemId::BUBBLE_ARMOR, "Bubble Armor");

    flags.isRequired = true;
    populateItem(ItemIndex::SOUL_BLADE, &flags, ItemId::SOUL_BLADE, "Soul Blade");
    populateItem(ItemIndex::SOUL_ARMOR, &flags, ItemId::SOUL_ARMOR, "Soul Armor");
    populateItem(ItemIndex::PHOENIX, &flags, ItemId::PHOENIX, "Phoenix");

    resetFlags(flags);
    flags.isUnique = true;
    flags.isProgression = true;
    populateItem(ItemIndex::HARP_STRING, &flags, ItemId::HARP_STRING, "Harp String");
    populateItem(ItemIndex::PASS, &flags, ItemId::PASS, "Pass");
    populateItem(ItemIndex::DREAM_ROD, &flags, ItemId::DREAM_ROD, "Dream Rod");
    populateItem(ItemIndex::LEOS_BRUSH, &flags, ItemId::LEOS_BRUSH, "Leo`s Brush");
    populateItem(ItemIndex::GREENWOOD_LEAF, &flags, ItemId::GREENWOOD_LEAF, "Greenwood Leaf");
    populateItem(ItemIndex::MOLES_RIBBON, &flags, ItemId::MOLES_RIBBON, "Mole`s Ribbon");
    populateItem(ItemIndex::BIG_PEARL, &flags, ItemId::BIG_PEARL, "Big Pearl");
    populateItem(ItemIndex::MUSHROOM_SHOES, &flags, ItemId::MUSHROOM_SHOES, "Mushroom Shoes");
    populateItem(ItemIndex::MOBILE_KEY, &flags, ItemId::MOBILE_KEY, "Mobile Key");
    populateItem(ItemIndex::THUNDER_RING, &flags, ItemId::THUNDER_RING, "Thunder Ring");
    populateItem(ItemIndex::DELICIOUS_SEEDS, &flags, ItemId::DELICIOUS_SEEDS, "Delicious Seeds");
    populateItem(ItemIndex::ACTINIDIA_LEAF, &flags, ItemId::ACTINIDIA_LEAF, "Actinidia Leaf");
    populateItem(ItemIndex::DOOR_KEY, &flags, ItemId::DOOR_KEY, "Door Key");
    populateItem(ItemIndex::PLATINUM_CARD, &flags, ItemId::PLATINUM_CARD, "Platinum Card");
    populateItem(ItemIndex::VIP_CARD, &flags, ItemId::VIP_CARD, "VIP Card");
    populateItem(ItemIndex::EMBLEM_A, &flags, ItemId::EMBLEM_A, "Emblem A");
    populateItem(ItemIndex::EMBLEM_B, &flags, ItemId::EMBLEM_B, "Emblem B");
    populateItem(ItemIndex::EMBLEM_C, &flags, ItemId::EMBLEM_C, "Emblem C");
    populateItem(ItemIndex::EMBLEM_D, &flags, ItemId::EMBLEM_D, "Emblem D");
    populateItem(ItemIndex::EMBLEM_E, &flags, ItemId::EMBLEM_E, "Emblem E");
    populateItem(ItemIndex::EMBLEM_F, &flags, ItemId::EMBLEM_F, "Emblem F");
    populateItem(ItemIndex::EMBLEM_G, &flags, ItemId::EMBLEM_G, "Emblem G");
    populateItem(ItemIndex::EMBLEM_H, &flags, ItemId::EMBLEM_H, "Emblem H");

    flags.isRequired = true;
    populateItem(ItemIndex::RED_HOT_MIRROR, &flags, ItemId::RED_HOT_MIRROR, "Red Hot Mirror");
    populateItem(ItemIndex::RED_HOT_BALL, &flags, ItemId::RED_HOT_BALL, "Red Hot Ball");
    populateItem(ItemIndex::RED_HOT_STICK, &flags, ItemId::RED_HOT_STICK, "Red Hot Stick");
    populateItem(ItemIndex::BROWN_STONE, &flags, ItemId::BROWN_STONE, "Brown Stone");
    populateItem(ItemIndex::GREEN_STONE, &flags, ItemId::GREEN_STONE, "Green Stone");
    populateItem(ItemIndex::BLUE_STONE, &flags, ItemId::BLUE_STONE, "Blue Stone");
    populateItem(ItemIndex::SILVER_STONE, &flags, ItemId::SILVER_STONE, "Silver Stone");
    populateItem(ItemIndex::PURPLE_STONE, &flags, ItemId::PURPLE_STONE, "Purple Stone");
    populateItem(ItemIndex::BLACK_STONE, &flags, ItemId::BLACK_STONE, "Black Stone");

    resetFlags(flags);
    flags.isUnique = true;
    populateItem(ItemIndex::GOATS_FOOD, &flags, ItemId::GOATS_FOOD, "Goat`s food");
    populateItem(ItemIndex::MERMAIDS_TEARS, &flags, ItemId::MERMAIDS_TEARS, "Mermaid Tears");
    populateItem(ItemIndex::MAGIC_BELL, &flags, ItemId::MAGIC_BELL, "Magic Bell");

    flags.isUnique = false;
    flags.isConsumable = true;
    populateItem(ItemIndex::MEDICAL_HERB, &flags, ItemId::MEDICAL_HERB, "Medical Herb");
    populateItem(ItemIndex::STRANGE_BOTTLE, &flags, ItemId::STRANGE_BOTTLE, "Strange Bottle");

    flags.isExperience = true;
    flags.ExpAmount = 1;
    populateItem(ItemIndex::GEMS_EXP_1, &flags, ItemId::GEMS_EXP, "1 Gem or Exp");
    flags.ExpAmount = 12;
    populateItem(ItemIndex::GEMS_EXP_12, &flags, ItemId::GEMS_EXP, "12 Gems or Exp");
    flags.ExpAmount = 30;
    populateItem(ItemIndex::GEMS_EXP_30, &flags, ItemId::GEMS_EXP, "30 Gems or Exp");
    flags.ExpAmount = 40;
    populateItem(ItemIndex::GEMS_EXP_40, &flags, ItemId::GEMS_EXP, "40 Gems or Exp");
    flags.ExpAmount = 50;
    populateItem(ItemIndex::GEMS_EXP_50, &flags, ItemId::GEMS_EXP, "50 Gems or Exp");
    flags.ExpAmount = 60;
    populateItem(ItemIndex::GEMS_EXP_60, &flags, ItemId::GEMS_EXP, "60 Gems or Exp");
    flags.ExpAmount = 80;
    populateItem(ItemIndex::GEMS_EXP_80, &flags, ItemId::GEMS_EXP, "80 Gems or Exp");
    flags.ExpAmount = 100;
    populateItem(ItemIndex::GEMS_EXP_100, &flags, ItemId::GEMS_EXP, "100 Gems or Exp");
    flags.ExpAmount = 150;
    populateItem(ItemIndex::GEMS_EXP_150, &flags, ItemId::GEMS_EXP, "150 Gems or Exp");
    flags.ExpAmount = 180;
    populateItem(ItemIndex::GEMS_EXP_180, &flags, ItemId::GEMS_EXP, "180 Gems or Exp");
    flags.ExpAmount = 200;
    populateItem(ItemIndex::GEMS_EXP_200, &flags, ItemId::GEMS_EXP, "200 Gems or Exp");
    flags.ExpAmount = 250;
    populateItem(ItemIndex::GEMS_EXP_250, &flags, ItemId::GEMS_EXP, "250 Gems or Exp");
    flags.ExpAmount = 300;
    populateItem(ItemIndex::GEMS_EXP_300, &flags, ItemId::GEMS_EXP, "300 Gems or Exp");
    flags.ExpAmount = 400;
    populateItem(ItemIndex::GEMS_EXP_400, &flags, ItemId::GEMS_EXP, "400 Gems or Exp");

    resetFlags(flags);
    Item npc;
    Item progNpc;
    Item reqNpc;
    resetFlags(npc);
    resetFlags(progNpc);
    resetFlags(reqNpc);
    npc.isNPC = true;
    progNpc.isNPC = true;
    progNpc.isProgression = true;
    reqNpc.isNPC = true;
    reqNpc.isProgression = true;
    reqNpc.isRequired = true;

    populateNpc(ItemIndex::NPC_OLD_WOMAN, &reqNpc, NpcId::NPC_OLD_WOMAN, "Old Woman (Chief's House)");
    populateNpc(ItemIndex::NPC_TOOL_SHOP_OWNER, &progNpc, NpcId::NPC_TOOL_SHOP_OWNER, "Tool Shop Owner");
    populateNpc(ItemIndex::NPC_TULIP, &npc, NpcId::NPC_TULIP, "Tulip");
    populateNpc(ItemIndex::NPC_TULIP2, &npc, NpcId::NPC_TULIP2, "Tulip 2");
    populateNpc(ItemIndex::NPC_TULIP3, &npc, NpcId::NPC_TULIP3, "Tulip 3");
    populateNpc(ItemIndex::NPC_TULIP4, &npc, NpcId::NPC_TULIP4, "Tulip 4");
    populateNpc(ItemIndex::NPC_TULIP_PASS, &progNpc, NpcId::NPC_TULIP_PASS, "Pass Tulip");
    populateNpc(ItemIndex::NPC_IVY, &progNpc, NpcId::NPC_IVY, "Ivy to southeast valley");
    populateNpc(ItemIndex::NPC_IVY2, &npc, NpcId::NPC_IVY2, "Ivy 2");
    populateNpc(ItemIndex::NPC_IVY_CHEST_ROOM, &progNpc, NpcId::NPC_IVY_CHEST_ROOM, "Hype Cave Ivy");
    populateNpc(ItemIndex::NPC_IVY_EMBLEM_A, &progNpc, NpcId::NPC_IVY_EMBLEM_A, "Emblem A Ivy");
    populateNpc(ItemIndex::NPC_IVY_RECOVERY_SWORD, &progNpc, NpcId::NPC_IVY_RECOVERY_SWORD, "Recovery Sword Ivy");
    populateNpc(ItemIndex::NPC_BRIDGE_GUARD, &progNpc, NpcId::NPC_BRIDGE_GUARD, "Bridge Guard");
    populateNpc(ItemIndex::NPC_WATER_MILL, &progNpc, NpcId::NPC_WATER_MILL, "Watermill Keeper");
    populateNpc(ItemIndex::NPC_GOAT_HERB, &progNpc, NpcId::NPC_GOAT_HERB, "Fence Goat");
    populateNpc(ItemIndex::NPC_GOAT, &npc, NpcId::NPC_GOAT, "Goat");
    populateNpc(ItemIndex::NPC_GOAT2, &npc, NpcId::NPC_GOAT2, "Goat 2");
    populateNpc(ItemIndex::NPC_LONELY_GOAT, &npc, NpcId::NPC_LONELY_GOAT, "Lonely Goat");
    populateNpc(ItemIndex::NPC_LISA, &progNpc, NpcId::NPC_LISA, "Lisa");
    populateNpc(ItemIndex::NPC_ARCHITECT, &progNpc, NpcId::NPC_ARCHITECT, "Architect (Stairs to Leo's House)");
    populateNpc(ItemIndex::NPC_OLD_MAN, &npc, NpcId::NPC_OLD_MAN, "Old Man");
    populateNpc(ItemIndex::NPC_OLD_MAN2, &npc, NpcId::NPC_OLD_MAN2, "Old Man 2");
    populateNpc(ItemIndex::NPC_TEDDY, &progNpc, NpcId::NPC_TEDDY, "Teddy");
    populateNpc(ItemIndex::NPC_LEOS_HOUSE, &progNpc, NpcId::NPC_LEOS_HOUSE, "Leo's House");
    populateNpc(ItemIndex::NPC_BOY_CABIN, &npc, NpcId::NPC_BOY_CABIN, "Hideout Boy");
    populateNpc(ItemIndex::NPC_BOY_CAVE, &progNpc, NpcId::NPC_BOY_CAVE, "Pass check Boy");
    populateNpc(ItemIndex::NPC_VILLAGE_CHIEF, &reqNpc, NpcId::NPC_VILLAGE_CHIEF, "Village Chief");

    populateNpc(ItemIndex::NPC_BIRD_RED_HOT_MIRROR, &progNpc, NpcId::NPC_BIRD_RED_HOT_MIRROR, "Red Hot Bird");
    populateNpc(ItemIndex::NPC_BIRD, &npc, NpcId::NPC_BIRD, "Bird");
    populateNpc(ItemIndex::NPC_BIRD2, &npc, NpcId::NPC_BIRD2, "Bird 2");
    populateNpc(ItemIndex::NPC_BIRD3, &npc, NpcId::NPC_BIRD3, "Bird 3");
    populateNpc(ItemIndex::NPC_BIRD_GREENWOOD_LEAF, &progNpc, NpcId::NPC_BIRD_GREENWOOD_LEAF, "Tiki (Turbo's Gravestone)");
    populateNpc(ItemIndex::NPC_DOG, &npc, NpcId::NPC_DOG, "Dog");
    populateNpc(ItemIndex::NPC_DOG2, &npc, NpcId::NPC_DOG2, "Dog 2");
    populateNpc(ItemIndex::NPC_DOG3, &progNpc, NpcId::NPC_DOG3, "Woodstin Trio Dog");
    populateNpc(ItemIndex::NPC_DOG4, &npc, NpcId::NPC_DOG4, "Dog 4");
    populateNpc(ItemIndex::NPC_DOG5, &npc, NpcId::NPC_DOG5, "Dog 5");
    populateNpc(ItemIndex::NPC_SQUIRREL, &npc, NpcId::NPC_SQUIRREL, "Squirrel");
    populateNpc(ItemIndex::NPC_SQUIRREL2, &npc, NpcId::NPC_SQUIRREL2, "Squirrel 2");
    populateNpc(ItemIndex::NPC_SQUIRREL3, &progNpc, NpcId::NPC_SQUIRREL3, "Woodstin Trio Squirrel");
    populateNpc(ItemIndex::NPC_SQUIRREL_EMBLEM_C, &progNpc, NpcId::NPC_SQUIRREL_EMBLEM_C, "Emblem C Squirrel");
    populateNpc(ItemIndex::NPC_SQUIRREL_ICE_ARMOR, &progNpc, NpcId::NPC_SQUIRREL_ICE_ARMOR, "Ice Armor Stump Squirrel");
    populateNpc(ItemIndex::NPC_SQUIRREL_PSYCHO_SWORD, &progNpc, NpcId::NPC_SQUIRREL_PSYCHO_SWORD, "Nut trade Squirrel");
    populateNpc(ItemIndex::NPC_CROCODILE, &progNpc, NpcId::NPC_CROCODILE, "Crocodile (to graveyard)");
    populateNpc(ItemIndex::NPC_CROCODILE2, &progNpc, NpcId::NPC_CROCODILE2, "Crocodile 2 (to graveyard)");
    populateNpc(ItemIndex::NPC_CROCODILE3, &progNpc, NpcId::NPC_CROCODILE3, "Crocodile 3 (to deer)");
    populateNpc(ItemIndex::NPC_MOLE, &progNpc, NpcId::NPC_MOLE, "Mole (hole to Ice Armor Stump)");
    populateNpc(ItemIndex::NPC_MOLE2, &npc, NpcId::NPC_MOLE2, "Mole 2");
    populateNpc(ItemIndex::NPC_MOLE3, &progNpc, NpcId::NPC_MOLE3, "Mole 3 (Monmo's hole)");
    populateNpc(ItemIndex::NPC_MOLE_SHIELD_BRACELET, &progNpc, NpcId::NPC_MOLE_SHIELD_BRACELET, "Shield Bracelet Mole");
    populateNpc(ItemIndex::NPC_MOLE_SOUL_OF_LIGHT, &progNpc, NpcId::NPC_MOLE_SOUL_OF_LIGHT, "Mole (Greenwood Leaf Hole)");
    populateNpc(ItemIndex::NPC_MONMO, &progNpc, NpcId::NPC_MONMO, "Monmo the Mole");
    populateNpc(ItemIndex::NPC_DEER, &progNpc, NpcId::NPC_DEER, "Woodstin Trio Deer");
    populateNpc(ItemIndex::NPC_DEER_MAGIC_BELL, &progNpc, NpcId::NPC_DEER_MAGIC_BELL, "Magic Bell Deer");
    populateNpc(ItemIndex::NPC_GREENWOODS_GUARDIAN, &reqNpc, NpcId::NPC_GREENWOODS_GUARDIAN, "Greenwoods Guardian");

    populateNpc(ItemIndex::NPC_DOLPHIN, &npc, NpcId::NPC_DOLPHIN, "Dolphin");
    populateNpc(ItemIndex::NPC_DOLPHIN_NORTHEAST, &progNpc, NpcId::NPC_DOLPHIN_NORTHEAST, "Northeast platform Dolphin");
    populateNpc(ItemIndex::NPC_DOLPHIN_PEARL, &progNpc, NpcId::NPC_DOLPHIN_PEARL, "Pearl Dolphin");
    populateNpc(ItemIndex::NPC_DOLPHIN_SAVES_LUE, &progNpc, NpcId::NPC_DOLPHIN_SAVES_LUE, "Dolphin who saves Lue");
    populateNpc(ItemIndex::NPC_DOLPHIN_SECRET_CAVE, &progNpc, NpcId::NPC_DOLPHIN_SECRET_CAVE, "Secret Cave Dolphin");
    populateNpc(ItemIndex::NPC_LUE, &progNpc, NpcId::NPC_LUE, "Lue");
    populateNpc(ItemIndex::NPC_MERMAID_NORTHEAST, &progNpc, NpcId::NPC_MERMAID_NORTHEAST, "NW Medical Herb Mermaid");
    populateNpc(ItemIndex::NPC_MERMAID2, &npc, NpcId::NPC_MERMAID2, "Mermaid 2");
    populateNpc(ItemIndex::NPC_MERMAID3, &npc, NpcId::NPC_MERMAID3, "Mermaid 3");
    populateNpc(ItemIndex::NPC_MERMAID_DANCE_LEADER, &progNpc, NpcId::NPC_MERMAID_DANCE_LEADER, "Dance platform Mermaid");
    populateNpc(ItemIndex::NPC_MERMAID5, &npc, NpcId::NPC_MERMAID5, "Mermaid 5");
    populateNpc(ItemIndex::NPC_MERMAID6, &npc, NpcId::NPC_MERMAID6, "Mermaid 6");
    populateNpc(ItemIndex::NPC_MERMAID7, &npc, NpcId::NPC_MERMAID7, "Mermaid 7");
    populateNpc(ItemIndex::NPC_MERMAID8, &npc, NpcId::NPC_MERMAID8, "Mermaid 8");
    populateNpc(ItemIndex::NPC_MERMAID9, &npc, NpcId::NPC_MERMAID9, "Mermaid 9");
    populateNpc(ItemIndex::NPC_MERMAID_BUBBLE_ARMOR, &progNpc, NpcId::NPC_MERMAID_BUBBLE_ARMOR, "Bubble Armor Mermaid");
    populateNpc(ItemIndex::NPC_MERMAID_MAGIC_FLARE, &progNpc, NpcId::NPC_MERMAID_MAGIC_FLARE, "Magic Flare Mermaid");
    populateNpc(ItemIndex::NPC_MERMAID_NANA, &npc, NpcId::NPC_MERMAID_NANA, "Mermaid Nana");
    populateNpc(ItemIndex::NPC_MERMAID_PEARL, &progNpc, NpcId::NPC_MERMAID_PEARL, "Mermaid guarding Lue");
    populateNpc(ItemIndex::NPC_MERMAID_RED_HOT_STICK, &progNpc, NpcId::NPC_MERMAID_RED_HOT_STICK, "Red Hot Mermaid");
    populateNpc(ItemIndex::NPC_MERMAID_TEARS, &npc, NpcId::NPC_MERMAID_TEARS, "Mermaid Tears chest Mermaid");
    populateNpc(ItemIndex::NPC_ANGELFISH, &npc, NpcId::NPC_ANGELFISH, "Angelfish");
    populateNpc(ItemIndex::NPC_ANGELFISH2, &npc, NpcId::NPC_ANGELFISH2, "Angelfish 2");
    populateNpc(ItemIndex::NPC_ANGELFISH3, &npc, NpcId::NPC_ANGELFISH3, "Angelfish 3");
    populateNpc(ItemIndex::NPC_ANGELFISH4, &npc, NpcId::NPC_ANGELFISH4, "Angelfish 4");
    populateNpc(ItemIndex::NPC_ANGELFISH_SOUL_OF_SHIELD, &npc, NpcId::NPC_ANGELFISH_SOUL_OF_SHIELD, "Soul Angelfish");
    populateNpc(ItemIndex::NPC_MERMAID_STATUE_BLESTER, &progNpc, NpcId::NPC_MERMAID_STATUE_BLESTER, "Blester Mermaid Statue");
    populateNpc(ItemIndex::NPC_MERMAID_STATUE_ROCKBIRD, &progNpc, NpcId::NPC_MERMAID_STATUE_ROCKBIRD, "Rockbird Mermaid Statue");
    populateNpc(ItemIndex::NPC_MERMAID_STATUE_DUREAN, &progNpc, NpcId::NPC_MERMAID_STATUE_DUREAN, "Durean Mermaid Statue");
    populateNpc(ItemIndex::NPC_MERMAID_STATUE_GHOST_SHIP, &progNpc, NpcId::NPC_MERMAID_STATUE_GHOST_SHIP, "Ghost Ship Mermaid Statue");
    populateNpc(ItemIndex::NPC_MERMAID_QUEEN, &reqNpc, NpcId::NPC_MERMAID_QUEEN, "Mermaid Queen");

    populateNpc(ItemIndex::NPC_GREETER_GRANDPA, &progNpc, NpcId::NPC_GREETER_GRANDPA, "Greeter Grandpa (northwest tunnel)");
    populateNpc(ItemIndex::NPC_GRANDPA2, &npc, NpcId::NPC_GRANDPA2, "Grandpa 2");
    populateNpc(ItemIndex::NPC_GRANDPA_LOGS, &reqNpc, NpcId::NPC_GRANDPA_LOGS, "Grandpa (opens door to King)");
    populateNpc(ItemIndex::NPC_GRANDPA_LAKE, &reqNpc, NpcId::NPC_GRANDPA_LAKE, "Grandpa (opens southeast lake)");
    populateNpc(ItemIndex::NPC_GRANDPA_PRISON, &reqNpc, NpcId::NPC_GRANDPA_PRISON, "Prison guard Grandpa");
    populateNpc(ItemIndex::NPC_GRANDPA_LUNE, &progNpc, NpcId::NPC_GRANDPA_LUNE, "Lune Grandpa");
    populateNpc(ItemIndex::NPC_GRANDMA, &npc, NpcId::NPC_GRANDMA, "Grandma");
    populateNpc(ItemIndex::NPC_DANCING_GRANDMA, &reqNpc, NpcId::NPC_DANCING_GRANDMA, "Dancing Grandma 1");
    populateNpc(ItemIndex::NPC_DANCING_GRANDMA2, &reqNpc, NpcId::NPC_DANCING_GRANDMA2, "Dancing Grandma 2");
    populateNpc(ItemIndex::NPC_PATHFINDER_BOY, &reqNpc, NpcId::NPC_PATHFINDER_BOY, "Boy (eastern tunnel to king)");
    populateNpc(ItemIndex::NPC_BOY2, &npc, NpcId::NPC_BOY2, "Boy 2");
    populateNpc(ItemIndex::NPC_BOY_MUSHROOM_SHOES, &progNpc, NpcId::NPC_BOY_MUSHROOM_SHOES, "Mushroom Shoes Boy");
    populateNpc(ItemIndex::NPC_GIRL, &npc, NpcId::NPC_GIRL, "Girl");
    populateNpc(ItemIndex::NPC_GIRL2, &npc, NpcId::NPC_GIRL2, "Girl 2");
    populateNpc(ItemIndex::NPC_GIRL_TUNNEL, &reqNpc, NpcId::NPC_GIRL_TUNNEL, "Girl (east side tunnel)");
    populateNpc(ItemIndex::NPC_SNAIL, &npc, NpcId::NPC_SNAIL, "Snail");
    populateNpc(ItemIndex::NPC_SNAIL2, &npc, NpcId::NPC_SNAIL2, "Snail 2");
    populateNpc(ItemIndex::NPC_SNAIL_EMBLEM_E, &progNpc, NpcId::NPC_SNAIL_EMBLEM_E, "Emblem E Secret room Snail");
    populateNpc(ItemIndex::NPC_SNAIL_JOCKEY, &npc, NpcId::NPC_SNAIL_JOCKEY, "Snail Jockey");
    populateNpc(ItemIndex::NPC_SNAIL_RACER, &npc, NpcId::NPC_SNAIL_RACER, "Snail Racer");
    populateNpc(ItemIndex::NPC_SNAIL_RACER2, &npc, NpcId::NPC_SNAIL_RACER2, "Snail Racer 2");
    populateNpc(ItemIndex::NPC_MUSHROOM, &npc, NpcId::NPC_MUSHROOM, "Mushroom");
    populateNpc(ItemIndex::NPC_MUSHROOM_TUNNEL, &reqNpc, NpcId::NPC_MUSHROOM_TUNNEL, "Mushroom (south tunnel to Nome)");
    populateNpc(ItemIndex::NPC_MUSHROOM3, &npc, NpcId::NPC_MUSHROOM3, "Mushroom 3");
    populateNpc(ItemIndex::NPC_MUSHROOM_EMBLEM_F, &progNpc, NpcId::NPC_MUSHROOM_EMBLEM_F, "Sleeping Mushroom (unlock in Lune)");
    populateNpc(ItemIndex::NPC_NOME, &reqNpc, NpcId::NPC_NOME, "Nome the snail");
    populateNpc(ItemIndex::NPC_MOUNTAIN_KING, &reqNpc, NpcId::NPC_MOUNTAIN_KING, "Mountain King");

    populateNpc(ItemIndex::NPC_PLANT, &npc, NpcId::NPC_PLANT, "Plant");
    populateNpc(ItemIndex::NPC_PLANT2, &npc, NpcId::NPC_PLANT2, "Plant 2");
    populateNpc(ItemIndex::NPC_PLANT_HERB, &progNpc, NpcId::NPC_PLANT_HERB, "Herb Plant (through mouse hole)");
    populateNpc(ItemIndex::NPC_PLANT_ACTINIDIA_LEAVES, &progNpc, NpcId::NPC_PLANT_ACTINIDIA_LEAVES, "Actinidia Plant (upstairs bedroom)");
    populateNpc(ItemIndex::NPC_CAT_MOUSEHOLE1, &progNpc, NpcId::NPC_CAT_MOUSEHOLE1, "Cat 1 in main room");
    populateNpc(ItemIndex::NPC_CAT_MOUSEHOLE2, &progNpc, NpcId::NPC_CAT_MOUSEHOLE2, "Cat 2 in main room");
    populateNpc(ItemIndex::NPC_CAT3, &npc, NpcId::NPC_CAT3, "Cat 3");
    populateNpc(ItemIndex::NPC_CAT4, &npc, NpcId::NPC_CAT4, "Cat 4");
    populateNpc(ItemIndex::NPC_CAT_DOOR_KEY, &progNpc, NpcId::NPC_CAT_DOOR_KEY, "Sleeping Cat (Door Key)");
    populateNpc(ItemIndex::NPC_MOUSE_HOLE, &progNpc, NpcId::NPC_MOUSE_HOLE, "Mouse hole entrance mouse");
    populateNpc(ItemIndex::NPC_MOUSE2, &npc, NpcId::NPC_MOUSE2, "Mouse 2");
    populateNpc(ItemIndex::NPC_MOUSE3, &npc, NpcId::NPC_MOUSE3, "Mouse 3");
    populateNpc(ItemIndex::NPC_MOUSE4, &npc, NpcId::NPC_MOUSE4, "Mouse 4");
    populateNpc(ItemIndex::NPC_MOUSE5, &npc, NpcId::NPC_MOUSE5, "Mouse 5");
    populateNpc(ItemIndex::NPC_MOUSE_SPARK_BOMB, &progNpc, NpcId::NPC_MOUSE_SPARK_BOMB, "Spark Bomb Mouse in hole");
    populateNpc(ItemIndex::NPC_GREAT_DOOR_KITCHEN, &progNpc, NpcId::NPC_GREAT_DOOR_KITCHEN, "Locked Door to Kitchen");
    populateNpc(ItemIndex::NPC_GREAT_DOOR_SOUL_OF_DETECTION, &npc, NpcId::NPC_GREAT_DOOR_SOUL_OF_DETECTION, "Door to Chapel");
    populateNpc(ItemIndex::NPC_GREAT_DOOR_MODEL_TOWNS, &reqNpc, NpcId::NPC_GREAT_DOOR_MODEL_TOWNS, "Door to Model Town room");
    populateNpc(ItemIndex::NPC_GREAT_DOOR_ZANTETSU_SWORD, &progNpc, NpcId::NPC_GREAT_DOOR_ZANTETSU_SWORD, "Door to Zantetsu chest");
    populateNpc(ItemIndex::NPC_CHEST_OF_DRAWERS, &npc, NpcId::NPC_CHEST_OF_DRAWERS, "Chest of Drawers");
    populateNpc(ItemIndex::NPC_CHEST_OF_DRAWERS_ATTIC, &progNpc, NpcId::NPC_CHEST_OF_DRAWERS_ATTIC, "Herb storage Drawers in attic");
    populateNpc(ItemIndex::NPC_CHEST_OF_DRAWERS_MYSTIC_ARMOR, &progNpc, NpcId::NPC_CHEST_OF_DRAWERS_MYSTIC_ARMOR, "Mystic Armor Drawers in Kitchen");
    populateNpc(ItemIndex::NPC_STEPS_UPSTAIRS, &reqNpc, NpcId::NPC_STEPS_UPSTAIRS, "Steps to second floor");
    populateNpc(ItemIndex::NPC_STEPS_MARIE, &reqNpc, NpcId::NPC_STEPS_MARIE, "Steps to attic");
    populateNpc(ItemIndex::NPC_STAIRS_POWER_PLANT, &progNpc, NpcId::NPC_STAIRS_POWER_PLANT, "Stairs down to Power Plant");
    populateNpc(ItemIndex::NPC_MODEL_TOWN1, &progNpc, NpcId::NPC_MODEL_TOWN1, "Model Town 1 (left)");
    populateNpc(ItemIndex::NPC_MODEL_TOWN2, &progNpc, NpcId::NPC_MODEL_TOWN2, "Model Town 2 (right)");
    populateNpc(ItemIndex::NPC_DOLL, &npc, NpcId::NPC_DOLL, "Doll in Chapel");
    populateNpc(ItemIndex::NPC_MARIE, &reqNpc, NpcId::NPC_MARIE, "Marie the Doll");

    populateNpc(ItemIndex::NPC_SOLDIER, &npc, NpcId::NPC_SOLDIER, "Soldier");
    populateNpc(ItemIndex::NPC_SOLDIER2, &npc, NpcId::NPC_SOLDIER2, "Soldier 2");
    populateNpc(ItemIndex::NPC_SOLDIER3, &npc, NpcId::NPC_SOLDIER3, "Soldier 3");
    populateNpc(ItemIndex::NPC_SOLDIER4, &npc, NpcId::NPC_SOLDIER4, "Soldier 4");
    populateNpc(ItemIndex::NPC_SOLDIER5, &npc, NpcId::NPC_SOLDIER5, "Soldier 5");
    populateNpc(ItemIndex::NPC_SOLDIER6, &npc, NpcId::NPC_SOLDIER6, "Soldier 6");
    populateNpc(ItemIndex::NPC_SOLDIER7, &npc, NpcId::NPC_SOLDIER7, "Soldier 7");
    populateNpc(ItemIndex::NPC_SOLDIER8, &npc, NpcId::NPC_SOLDIER8, "Soldier 8");
    populateNpc(ItemIndex::NPC_SOLDIER9, &npc, NpcId::NPC_SOLDIER9, "Soldier 9");
    populateNpc(ItemIndex::NPC_SOLDIER10, &npc, NpcId::NPC_SOLDIER10, "Soldier 10");
    populateNpc(ItemIndex::NPC_SOLDIER11, &npc, NpcId::NPC_SOLDIER11, "Soldier 11");
    populateNpc(ItemIndex::NPC_SOLDIER_SOUL_OF_REALITY, &npc, NpcId::NPC_SOLDIER_SOUL_OF_REALITY, "Soul of Reality Soldier");
    populateNpc(ItemIndex::NPC_SOLDIER_ELEMENTAL_MAIL, &progNpc, NpcId::NPC_SOLDIER_ELEMENTAL_MAIL, "Sleeping Soldier with Elemental Mail");
    populateNpc(ItemIndex::NPC_SOLDIER_PLATINUM_CARD, &progNpc, NpcId::NPC_SOLDIER_PLATINUM_CARD, "Concert Hall Soldier (Platinum Card)");
    populateNpc(ItemIndex::NPC_SOLDIER_DOK, &progNpc, NpcId::NPC_SOLDIER_DOK, "Dok the Soldier at Airship");
    populateNpc(ItemIndex::NPC_SOLDIER_WITH_LEO, &progNpc, NpcId::NPC_SOLDIER_WITH_LEO, "Soldier with Leo at Airship");
    populateNpc(ItemIndex::NPC_DR_LEO, &progNpc, NpcId::NPC_DR_LEO, "Doctor Leo at Airship");
    populateNpc(ItemIndex::NPC_MAID, &npc, NpcId::NPC_MAID, "Maid");
    populateNpc(ItemIndex::NPC_MAID2, &npc, NpcId::NPC_MAID2, "Maid 2");
    populateNpc(ItemIndex::NPC_MAID_HERB, &progNpc, NpcId::NPC_MAID_HERB, "Medical Herb Maid behind counter");
    populateNpc(ItemIndex::NPC_SINGER, &npc, NpcId::NPC_SINGER, "Singer standing outside");
    populateNpc(ItemIndex::NPC_SINGER_CONCERT_HALL, &progNpc, NpcId::NPC_SINGER_CONCERT_HALL, "Singer in Concert Hall");
    populateNpc(ItemIndex::NPC_SOLDIER_LEFT_TOWER, &progNpc, NpcId::NPC_SOLDIER_LEFT_TOWER, "Left Tower Guard Soldier");
    populateNpc(ItemIndex::NPC_SOLDIER_RIGHT_TOWER, &progNpc, NpcId::NPC_SOLDIER_RIGHT_TOWER, "Right Tower Guard Soldier");
    populateNpc(ItemIndex::NPC_SOLDIER_CASTLE, &reqNpc, NpcId::NPC_SOLDIER_CASTLE, "Builder Soldier (builds castle)");
    populateNpc(ItemIndex::NPC_QUEEN_MAGRIDD, &progNpc, NpcId::NPC_QUEEN_MAGRIDD, "Queen Magridd");
    populateNpc(ItemIndex::NPC_KING_MAGRIDD, &reqNpc, NpcId::NPC_KING_MAGRIDD, "King Magridd");

    allItemsCount = 1 + (int)ItemIndex::NPC_KING_MAGRIDD;
}

ItemIndex ItemPool::getItemIndexForItemId (ItemId id) {
    return itemIdMap[(int)id];
}
ItemIndex ItemPool::getItemIndexForNpcId (NpcId id) {
    return npcIdMap[(int)id];
}
ItemIndex ItemPool::getItemIndexForGemsOrExp (int expAmount) {
    switch(expAmount) {
        case 1: return ItemIndex::GEMS_EXP_1;
        case 12: return ItemIndex::GEMS_EXP_12;
        case 40: return ItemIndex::GEMS_EXP_40;
        case 50: return ItemIndex::GEMS_EXP_50;
        case 60: return ItemIndex::GEMS_EXP_60;
        case 80: return ItemIndex::GEMS_EXP_80;
        case 100: return ItemIndex::GEMS_EXP_100;
        case 150: return ItemIndex::GEMS_EXP_150;
        case 200: return ItemIndex::GEMS_EXP_200;
    }
    // Should not happen
    return ItemIndex::GEMS_EXP_1;
}

const Item& ItemPool::getItemByIndex (ItemIndex index) {
    return allItems[(int)index];
}

ItemPool* ItemPool::addItem (ItemIndex i) {
    itemList[static_cast<int>(i)]++;
    return this;
}
void ItemPool::removeItem (ItemIndex i) {
    if (itemList[static_cast<int>(i)] > 0) {
        itemList[static_cast<int>(i)] -= 1;
    };
}
bool ItemPool::hasItem (ItemIndex i) {
    return itemList[static_cast<int>(i)] > 0;
}
void ItemPool::clear () {
    for (int i = 0; i < MAX_POOL_SIZE; i++) {
        itemList[i] = 0;
    }
}
void ItemPool::copyFrom (ItemPool* source) {
    memcpy(itemList, source->itemList, sizeof(itemList));
}
