# RandoBlazer

This randomizer should be used with the US version of the ROM: 
  Soul Blazer (U) [!].smc

Both headered and non-headered ROMs can be used - the header will be automatically detected.
  
## Make a randomized ROM

This project builds two ways to randomize Soul Blazer: an executable and a web page that uses web assembly.

To use the web page, load it in a browser and follow the instructions.

For the executable, build instructions and cli options are in the development section below.

## Version 0.9.1 features

Monster Lair contents:
 - Enemy type is randomized, but will still choose from the possible enemy types in the current location. Monsters which usually don't belong to lairs can be in lairs (like blue blobs and torches in Act 1 Underground Castle).
 - Lair type is randomized: it can be one-by-one spawner, multispawner, or proximity spawner (this one is more rare). The "already there" type is not randomized though.
 - Number of enemies is randomized: between 2 and 5 for one-by-one spawners, and between 4 and 12 for multispawners.
 - Multispawner spawn rate is randomized between 3 and 20 frames.
 - The number of enemies and spawn rate is weighted so that single spawners are more likely to get fewer enemies and multispawners are more likely to spawn faster. Spawn types have been adjusted to 10% regular single spawn and 5% proximity single spawn. **(New)**
 
NPCs released from monster lairs are also shuffled in a way that still makes the game beatable. The progression through the game will probably be quite different from the original game.

Items from chests and items received from NPCs or found in special places are all shuffled. You can find all non-chest item locations in this pastebin:
https://pastebin.com/phaJZdwW

"Free" monsters are also randomized, i.e. the monsters which do not belong to a monster lair. A few of them can have four different possible orientations, and that is randomized too (like the water dragons in Greenwood, or the snow rats in Mountain of Souls).

The Gourmet Goat will give you a clue on the location of either the Soul Blade, the Soul Armor or Phoenix, provided you give it food. The crystal fairy in Magridd Castle basement gives a clue about one of the Red Hot items. Some other NPCs can give clues (the soldier with Dr. Leo, etc.).

The six Stones are required in order to progress to the World of Evil. However, you don't need each individual Stone to progress to the next area: for that you need to talk to the leader NPC of the current area (their item will also be randomized).

Finally, a lot of text has been edited in order to match the actual item NPCs now give you, but also to reduce the amount of text in most cutscenes. Most revival text has also been edited out. There is also a variety of texts for Master's text in the game introduction and on player's death. The text speed is now faster - this actually matches the speed in the Japanese version.

### Item/NPC Tracker

You can use this tracker made by Netanonima: https://eggper.com/blazer_tracker/

### Improvement ideas

 - Make an open mode where the player can travel to all regions right at the start (maybe not World of Evil though).
 - Have varying difficulty levels (changing the item pool, or changing enemy/item stats).
 - More text edits maybe?
 - Randomize the orientation of enemies in "already there" monster lairs.

### Development

The randomizer is a C++ project that is configured to build with cmake. It is recommended to create a build subdirectory for each build type. Linux is recommended - on Windows try using Windows Subsystem for Linux (WSL). The cmake tool generates a Makefile by default but the ninja build tool is recommended. Emscripten is used for web assembly compilation. All tools are widely available from Linux package management systems like apt.

For web assembly a tool called emscripten is used. There may not be an apt package easily available.
The manual install process fairly straightforward though - https://emscripten.org/docs/getting_started/downloads.html

```
# Install build toolchain
sudo apt install build-essential cmake ninja-build
# emscripten for web assembly build
sudo apt install emscripten
```

 - CLI build

```./randoblazer <original rom> <output rom (optional)> <seed (optional)> <flags (optional)>```

If the original rom filename is omitted, it is expected to be in the same directory and named `Soul Blazer (U) [!].smc`. The first three arguments are positional and required in order to set flags. Available flags are:
* `race` - No spoiler log is created and the placement will not be the same as without the race option. The randomization is still consistent with the same seed so a link can be shared in the web version **(New)**.
* `nofastrom` - The fastrom patch will not be applied. **(New - fastrom patch is applied by default)**
 ```
 mkdir build && cd build
 cmake .. -GNinja
 ninja
 ```

 - Web assembly build
 ```
 mkdir build_emscripten && cd build_emscripten
 emcmake cmake .. -GNinja -DCMAKE_BUILD_TYPE=MinSizeRel
 ninja
 ```
 On the emcmake command `-DCMAKE_BUILD_TYPE=MinSizeRel` specifies a minified production build. Omit it for a development build. This build process creates `randoblazer.js` and `randoblazer.wasm`. Serve these alongside the files in the `www` directory.
